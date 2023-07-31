// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	if(APlayerController* PlayerControllerPointer = Cast<APlayerController>(GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerControllerPointer->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}

	PlayerController = Cast<APlayerController>(GetController());
	PlayerController->bShowMouseCursor = true;
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	{// Get Hit Result Under Cursor + Rotate Turret
		// Get Hit Result Under Cursor
		if (PlayerController)
		{
			FHitResult HitResult;
			PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

			FVector Location = HitResult.ImpactPoint;
			//DrawDebugSphere(GetWorld(), Location, 25.0f, 12, FColor::Cyan, false, 1.0f);
			//Rotate Turret
			RotateTurret(Location);
		}

		
		
	}
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent) )
	{
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ATank::Move);
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &ATank::Rotate);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ATank::Fire);
	}

}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}


void ATank::Move(const FInputActionValue& value)
{
	{//Move
		const FVector2D MovementVector = value.Get<FVector2D>();
		FVector DeltaLocation = FVector::ZeroVector;
		DeltaLocation.X = MovementVector.X * UGameplayStatics::GetWorldDeltaSeconds(this) * Speed;
		//DeltaLocation.Z = 0.000000001;
		AddActorLocalOffset(DeltaLocation, true);
	}

	{//Turn
		FRotator DeltaRotation = FRotator::ZeroRotator;
		DeltaRotation.Yaw = (value.Get<FVector2D>()).Y * UGameplayStatics::GetWorldDeltaSeconds(this) * TurnRate;
		AddActorLocalRotation(DeltaRotation, true);
	}
	
}
void ATank::Rotate(const FInputActionValue& value)
{
	
}
