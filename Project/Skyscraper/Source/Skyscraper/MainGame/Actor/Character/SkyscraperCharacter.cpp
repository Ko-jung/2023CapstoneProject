// Copyright Epic Games, Inc. All Rights Reserved.

#include "SkyscraperCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include <MotionWarpingComponent.h>

#include "Engine/DamageEvents.h"
#include "Skyscraper/MainGame/Component/Combat/CombatSystemComponent.h"
#include "Skyscraper/MainGame/Component/Combat/Melee/MainMeleeComponent.h"
#include "Skyscraper/MainGame/Component/Combat/Range/MainRangeComponent.h"
#include "Skyscraper/MainGame/Component/Health/HealthComponent.h"
#include "Skyscraper/MainGame/Component/Jetpack/JetpackComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ASkyscraperCharacter

ASkyscraperCharacter::ASkyscraperCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	IsHover = false;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	bUseControllerRotationYaw = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	CameraBoom->SetRelativeLocation(FVector(0.0f, 0.0f, 125.0f));

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	{ // == Set Mesh Charcter
		// == Find and set USkeletalMesh from directory
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
		GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
		// == Find and set AnimBlueprint (TEMP, Refactor to c++ later)
		static ConstructorHelpers::FClassFinder<UAnimInstance> AnimBPAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/2019180031/Character/PrototypeAnimation/ABP_GameTestChar_Test.ABP_GameTestChar_Test_C'"));
		GetMesh()->SetAnimClass(AnimBPAsset.Class);
	}

	{ // == Set Input Asset

		static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_DefaultAsset(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/2019180031/MainGame/Core/Input/Default/IMC_Default.IMC_Default'"));
		DefaultMappingContext = IMC_DefaultAsset.Object;

		static ConstructorHelpers::FObjectFinder<UInputAction> IA_MoveAsset(TEXT("/Script/EnhancedInput.InputAction'/Game/2019180031/MainGame/Core/Input/Default/IA_GameDefaultMove.IA_GameDefaultMove'"));
		MoveAction = IA_MoveAsset.Object;

		static ConstructorHelpers::FObjectFinder<UInputAction> IA_JumpAsset(TEXT("/Script/EnhancedInput.InputAction'/Game/2019180031/MainGame/Core/Input/Default/IA_GameDefaultJump.IA_GameDefaultJump'"));
		JumpAction = IA_JumpAsset.Object;

		static ConstructorHelpers::FObjectFinder<UInputAction> IA_LookAsset(TEXT("/Script/EnhancedInput.InputAction'/Game/2019180031/MainGame/Core/Input/Default/IA_GameDefaultLook.IA_GameDefaultLook'"));
		LookAction = IA_LookAsset.Object;

		static ConstructorHelpers::FObjectFinder<UInputAction> IA_Jetpack_DodgeRef(TEXT("/Script/EnhancedInput.InputAction'/Game/2019180031/MainGame/Core/Input/Jetpack/IA_Jetpack_Dodge.IA_Jetpack_Dodge'"));
		IA_Jetpack_Dodge = IA_Jetpack_DodgeRef.Object;
	}

	{ // == Set components
		CombatSystemComponent = CreateDefaultSubobject<UCombatSystemComponent>(TEXT("CombatSystemComponent"));
		MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
		HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
		JetpackComponent = CreateDefaultSubobject<UJetpackComponent>(TEXT("JetpackComponent"));
	}

	{ // == Set Anim Montages
		// Dagger
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Dagger1Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/Dagger/AM_Dagger1.AM_Dagger1'"));
		CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_DaggerAttack1, AM_Dagger1Ref.Object);
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Dagger2Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/Dagger/AM_Dagger2.AM_Dagger2'"));
		CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_DaggerAttack2, AM_Dagger2Ref.Object);
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Dagger3Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/Dagger/AM_Dagger3.AM_Dagger3'"));
		CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_DaggerAttack3, AM_Dagger3Ref.Object);
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Dagger4Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/Dagger/AM_Dagger4.AM_Dagger4'"));
		CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_DaggerAttack4, AM_Dagger4Ref.Object);
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Dagger5Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/Dagger/AM_Dagger5.AM_Dagger5'"));
		CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_DaggerAttack5, AM_Dagger5Ref.Object);
		// Katana
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Katana1Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/Katana/AM_Katana1.AM_Katana1'"));
		CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_KatanaAttack1, AM_Katana1Ref.Object);
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Katana2Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/Katana/AM_Katana2.AM_Katana2'"));
		CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_KatanaAttack2, AM_Katana2Ref.Object);
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Katana3Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/Katana/AM_Katana3.AM_Katana3'"));
		CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_KatanaAttack3, AM_Katana3Ref.Object);
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Katana4Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/Katana/AM_Katana4.AM_Katana4'"));
		CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_KatanaAttack4, AM_Katana4Ref.Object);
		// GreatSword
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_GreatSword1Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/GreatSword/GreatSwordSlash1_Montage.GreatSwordSlash1_Montage'"));
		CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_GreatSwordAttack1, AM_GreatSword1Ref.Object);
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_GreatSword2Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/GreatSword/GreatSwordSlash2_Montage.GreatSwordSlash2_Montage'"));
		CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_GreatSwordAttack2, AM_GreatSword2Ref.Object);
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_GreatSword3Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/GreatSword/GreatSwordSlash3_Montage.GreatSwordSlash3_Montage'"));
		CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_GreatSwordAttack3, AM_GreatSword3Ref.Object);

		//SMG
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_SMGFireRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Rifle/AM_FireRifle.AM_FireRifle'"));
		CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_SMGFire, AM_SMGFireRef.Object);
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_SMGReloadRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Rifle/AM_ReloadRifle.AM_ReloadRifle'"));
		CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_SMGReload, AM_SMGReloadRef.Object);

		//Rifle
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_RifleFireRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Rifle/AM_FireRifle.AM_FireRifle'"));
		CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_RifleFire, AM_RifleFireRef.Object);
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_RifleReloadRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Rifle/AM_ReloadRifle.AM_ReloadRifle'"));
		CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_RifleReload, AM_RifleReloadRef.Object);
		//RPG
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_RPGFireRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Rifle/AM_FireRifle.AM_FireRifle'"));
		CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_RPGFire, AM_RPGFireRef.Object);
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_RPGReloadRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Rifle/AM_ReloadRifle.AM_ReloadRifle'"));
		CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_RPGReload, AM_RPGReloadRef.Object);

		// Stiffness / Down
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_StiffnessRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Damaged/AM_GetDamaged.AM_GetDamaged'"));
		CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_Stiffness, AM_StiffnessRef.Object);
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_DownRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Damaged/AM_KnockedDown.AM_KnockedDown'"));
		CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_Down, AM_DownRef.Object);

	}
}

void ASkyscraperCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ASkyscraperCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	JetpackComponent->OnLandJetpack();
}

float ASkyscraperCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// https://mingyu0403.tistory.com/258 PointDamage / RadialDamage ...

	HealthComponent->GetDamaged(DamageAmount);
	
	return Damage;
}

void ASkyscraperCharacter::DoStiffness(const float StiffnessTime) const
{
	CombatSystemComponent->Stiffness(StiffnessTime);
}

void ASkyscraperCharacter::DoDown(const FVector& DownDirection) const
{
	CombatSystemComponent->Down(DownDirection);
}

UAnimMontage* ASkyscraperCharacter::GetAnimMontage(ECharacterAnimMontage eCharacterAnimMontage) const
{
	return *CharacterAnimMontages.Find(eCharacterAnimMontage);
}

void ASkyscraperCharacter::SyncTransformAndAnim(FTransform t, float s)
{
	SetActorTransform(t);
	SetSpeed(s);
}

//////////////////////////////////////////////////////////////////////////
// Input

void ASkyscraperCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASkyscraperCharacter::Move);
		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASkyscraperCharacter::Look);
		// (Jetpack) Dodge
		EnhancedInputComponent->BindAction(IA_Jetpack_Dodge, ETriggerEvent::Triggered, this, &ASkyscraperCharacter::Dodge);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ASkyscraperCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ASkyscraperCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ASkyscraperCharacter::Dodge(const FInputActionValue& InputActionValue)
{
	if(JetpackComponent)
	{
		FVector2D value = InputActionValue.Get<FVector2D>();
		JetpackComponent->Dodge(value);
	}
}
