// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"

// Sets default values
ABasicCharacter::ABasicCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	{ // Skeletal Mesh 설정
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> SKMAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/2019180031/Character/SkeltalMesh/SKM_BasicCharacter.SKM_BasicCharacter'"));
		if (SKMAsset.Succeeded())
		{
			GetMesh()->SetSkeletalMesh(SKMAsset.Object);
		}
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
		GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	}
	
	{ // Spring Arm Component 설정
		SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
		SpringArmComponent->SetupAttachment(GetRootComponent());
		SpringArmComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 125.0f));
		SpringArmComponent->TargetArmLength = 400.0f;
		SpringArmComponent->bUsePawnControlRotation = true;
	}
	
	{ // Camera Component 설정
		CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
		CameraComponent->SetupAttachment(SpringArmComponent);
	}
	
	{ // 캐릭터 애니메이션 설정
		static ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimBP(TEXT("/Script/Engine.AnimBlueprint'/Game/2019180031/Character/PrototypeAnimation/ABP_PrototypeCharacter.ABP_PrototypeCharacter'"));

		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		if (AnimBP.Succeeded())
		{
			GetMesh()->SetAnimClass(AnimBP.Object->GeneratedClass);
		}
	}
	
	{ // InputAction / InputMappingContext 파일 로드
		static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCData(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/2019180031/Core/Input/Default/IMC_Default.IMC_Default'"));
		IMC_Default = IMCData.Object;
	
		static ConstructorHelpers::FObjectFinder<UInputAction> IA_MoveData(TEXT("Script/EnhancedInput.InputAction'/Game/2019180031/Core/Input/Default/IA_Move.IA_Move'"));
		IA_Move = IA_MoveData.Object;
	
		static ConstructorHelpers::FObjectFinder<UInputAction> IA_LookData(TEXT("/Script/EnhancedInput.InputAction'/Game/2019180031/Core/Input/Default/IA_Look.IA_Look'"));
		IA_Look = IA_LookData.Object;
	}
}

// Called when the game starts or when spawned
void ABasicCharacter::BeginPlay()
{
	Super::BeginPlay();

	
	if(GetPlayerController())
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetPlayerController()->GetLocalPlayer());
		if(Subsystem)
		{
			Subsystem->AddMappingContext(IMC_Default, 0);
		}
	
	}
	
}

// Called every frame
void ABasicCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasicCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDir, MovementVector.X);
	AddMovementInput(RightDir, MovementVector.Y);
}

void ABasicCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	UE_LOG(LogTemp, Warning, TEXT("%f %f"), LookAxisVector.X, LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}


// Called to bind functionality to input
void ABasicCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ABasicCharacter::Move);
	EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ABasicCharacter::Look);

}

APlayerController* ABasicCharacter::GetPlayerController() const
{
	return Cast<APlayerController>(GetController());
}

