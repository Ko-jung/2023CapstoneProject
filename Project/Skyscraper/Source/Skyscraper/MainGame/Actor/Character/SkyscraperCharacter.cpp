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

#include "MyBlueprintItemDragDropAction.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Skyscraper/MainGame/Actor/LootingItem/LootingItemActor.h"
#include "Skyscraper/MainGame/Component/Combat/CombatSystemComponent.h"
#include "Skyscraper/MainGame/Component/Combat/Melee/MainMeleeComponent.h"
#include "Skyscraper/MainGame/Component/Combat/Range/MainRangeComponent.h"
#include "Skyscraper/MainGame/Component/Health/HealthComponent.h"
#include "Skyscraper/MainGame/Component/Jetpack/JetpackComponent.h"
#include "Skyscraper/MainGame/Item/ItemFactory/ItemFactory.h"
#include "Skyscraper/MainGame/Item/ItemObject/ItemObject.h"

#include "../../../Network/MainGameMode.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ASkyscraperCharacter

ASkyscraperCharacter::ASkyscraperCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bIsHover = false;
	CharacterMaxWalkSpeed = 600.0f;
	SpeedBuffValue = 1.0f;
	PowerBuffValue = 1.0f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->MaxStepHeight = 100.0f;	// 계단에서 올라갈 수 있도록 높이 조정
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = CharacterMaxWalkSpeed;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

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
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/character/4_assassin/assassin.assassin'"));
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
		GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
		// == Find and set AnimBlueprint (TEMP, Refactor to c++ later)
		static ConstructorHelpers::FClassFinder<UAnimInstance> AnimBPAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/2019180031/MainGame/Animation/Assassin/ABP_Assassin.ABP_Assassin_C'"));
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


		static ConstructorHelpers::FObjectFinder<UInputAction> IA_ItemInteractionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/2019180031/MainGame/Core/Input/Default/IA_GameDefaultItemInteraction.IA_GameDefaultItemInteraction'"));
		IA_ItemInteraction = IA_ItemInteractionRef.Object;

		static ConstructorHelpers::FObjectFinder<UInputAction> IA_ItemUsingRef(TEXT("/Script/EnhancedInput.InputAction'/Game/2019180031/MainGame/Core/Input/Default/IA_GameDefault_ItemUsing.IA_GameDefault_ItemUsing'"));
		IA_ItemUsing = IA_ItemUsingRef.Object;
	}		 

	{ // == Set components
		CombatSystemComponent = CreateDefaultSubobject<UCombatSystemComponent>(TEXT("CombatSystemComponent"));
		MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
		HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
		JetpackComponent = CreateDefaultSubobject<UJetpackComponent>(TEXT("JetpackComponent"));
	}

	{ // == Set Anim Montages
		// Dagger
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_DaggerRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Assassin/Combat/Melee/Dagger/AM_Assassin_DaggerAttack.AM_Assassin_DaggerAttack'"));
		CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_DaggerAttack, AM_DaggerRef.Object);

		// Katana
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_KatanaRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Assassin/Combat/Melee/Katana/AM_Assassin_KatanaAttack.AM_Assassin_KatanaAttack'"));
		CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_KatanaAttack, AM_KatanaRef.Object);

		// GreatSword
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_GreatSwordRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Assassin/Combat/Melee/Sword/AM_Assassin_SwordAttack.AM_Assassin_SwordAttack'"));
		CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_GreatSwordAttack, AM_GreatSwordRef.Object);
		

		//SMG
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_SMGRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Assassin/Combat/Range/SMG/AM_Assassin_SMG.AM_Assassin_SMG'"));
		CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_SMG, AM_SMGRef.Object);

		//Rifle
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_RifleRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Assassin/Combat/Range/Rifle/AM_Assassin_Rifle.AM_Assassin_Rifle'"));
		CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_Rifle, AM_RifleRef.Object);

		//RPG
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_RPGFireRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Assassin/Combat/Range/RPG/AM_Assassin_RPG.AM_Assassin_RPG'"));
		CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_RPG, AM_RPGFireRef.Object);

		// Stun / Down
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_StunRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Assassin/Combat/Damaged/AM_Assassin_Hit.AM_Assassin_Hit'"));
		CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_Stun, AM_StunRef.Object);

		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_DownRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Assassin/Combat/Damaged/AM_Assassin_Down.AM_Assassin_Down'"));
		CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_Down, AM_DownRef.Object);

		// Death
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_DeathRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Assassin/Combat/Death/AM_Assassin_Death.AM_Assassin_Death'"));
		CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_Death, AM_DeathRef.Object);


	}
}

void ASkyscraperCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	{ // 숙이기(crouch)중 카메라 위치 변하지 않도록 값 설정
		GetCharacterMovement()->SetCrouchedHalfHeight(GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight());
	}
	
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	auto gamemode = UGameplayStatics::GetGameMode(this);
	MainGameMode = Cast<AMainGameMode>(gamemode);
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

void ASkyscraperCharacter::DoStun(const float StunTime, const FVector StunDirection) const
{
	if(CombatSystemComponent)
	{
		CombatSystemComponent->Stun(StunTime, StunDirection);
	}
	
}

void ASkyscraperCharacter::DoDown(const FVector& DownDirection) const
{
	if(CombatSystemComponent)
	{
		CombatSystemComponent->Down(DownDirection);
	}
	
}

UAnimMontage* ASkyscraperCharacter::GetAnimMontage(ECharacterAnimMontage eCharacterAnimMontage) const
{
	if(MainGameMode)
		MainGameMode->SendAnimMontageStatus(this, eCharacterAnimMontage);

	return *CharacterAnimMontages.Find(eCharacterAnimMontage);
}

bool ASkyscraperCharacter::CheckHoldWeapon(ESwapWeapon& weaponType, uint8& equippedWeapon)
{
	// CheckHoldWeapon(ESwapWeapon&) -> CheckHoldWeapon(ESwapWeapon&, uint8&)
	//ESwapWeapon WeaponType;
	//uint8 EquippedWeapon;

	CombatSystemComponent->GetWeaponEquipStateForAnimation(weaponType, equippedWeapon);

	if (PrevWeaponType == weaponType)
	{
		return false;
	}

	PrevWeaponType = weaponType;

	return true;
}

void ASkyscraperCharacter::SwapWeapon(ESwapWeapon WeaponType)
{
	switch (WeaponType)
	{
	case ESwapWeapon::MeleeWeapon:
		CombatSystemComponent->SwapToMeleeWeapon(true);
		break;
	case ESwapWeapon::RangeWeapon:
		CombatSystemComponent->SwapToRangeWeapon(true);
		break;
	case ESwapWeapon::NullWeapon:
		break;
	default:
		break;
	}
}

void ASkyscraperCharacter::AddInputMappingContext()
{
	CombatSystemComponent->AddInputMappingContext();
	JetpackComponent->AddInputMappingContext();

	HealthComponent->AddWidget();
}

void ASkyscraperCharacter::SyncTransformAndAnim(FTransform t, float s, float r)
{
	SetActorTransform(t);
	SetSpeed(s);
	SetXRotate(r);
}

void ASkyscraperCharacter::SetMontage(ECharacterAnimMontage eAnimMontage)
{
	const auto& AnimMontage = *CharacterAnimMontages.Find(eAnimMontage);
	PlayAnimMontage(AnimMontage);
}

void ASkyscraperCharacter::SetSpeedBuffValue(float NewSpeedBuffValue, float fBuffTime)
{
	SpeedBuffValue = NewSpeedBuffValue;
	GetCharacterMovement()->MaxWalkSpeed = CharacterMaxWalkSpeed* SpeedBuffValue;

	if (!SpeedBuffTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(SpeedBuffTimerHandle, this, &ThisClass::ResetSpeedBuffValue, 0.2f, false, fBuffTime);
	}
	else      // 타이머가 기존에 실행 중이었다면 (무적 모드 중이었다면, 시간 초기화)
	{
		GetWorld()->GetTimerManager().ClearTimer(SpeedBuffTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(SpeedBuffTimerHandle, this, &ThisClass::ResetSpeedBuffValue, 0.2f, false, fBuffTime);
	}
}

void ASkyscraperCharacter::ResetSpeedBuffValue()
{
	GetWorld()->GetTimerManager().ClearTimer(SpeedBuffTimerHandle);
	SpeedBuffValue = 1.0f;
}

void ASkyscraperCharacter::SetPowerBuffValue(float NewPowerBuffValue, float fBuffTime)
{
	PowerBuffValue = NewPowerBuffValue;;

	if (!PowerBuffTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(PowerBuffTimerHandle, this, &ThisClass::ResetPowerBuffValue, 0.2f, false, fBuffTime);
	}
	else      // 타이머가 기존에 실행 중이었다면 (무적 모드 중이었다면, 시간 초기화)
	{
		GetWorld()->GetTimerManager().ClearTimer(PowerBuffTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(PowerBuffTimerHandle, this, &ThisClass::ResetPowerBuffValue, 0.2f, false, fBuffTime);
	}
}

void ASkyscraperCharacter::AddItem(EItemEffect ItemEffect, EItemRareLevel RareLevel)
{
	if(OwningItem.Key==EItemEffect::EIE_NONE)
	{
		OwningItem.Key = ItemEffect; OwningItem.Value = RareLevel;
		UE_LOG(LogTemp, Warning, TEXT("character earn item"));
	}
	
}

void ASkyscraperCharacter::SetCharacterGodMode(bool bNewGodMode)
{
	if(HealthComponent)
	{
		HealthComponent->SetGodMode(bNewGodMode);
	}
}

bool ASkyscraperCharacter::IsCharacterGodMode()
{
	if(HealthComponent)
	{
		return HealthComponent->IsGodMode();
	}

	return false;
}

void ASkyscraperCharacter::SetCameraMode(ECharacterCameraMode CameraMode)
{
	switch (CameraMode)
	{
	case ECharacterCameraMode::ECCM_FollowController:
		bUseControllerRotationYaw = true;
		break;
	case ECharacterCameraMode::ECCM_SeparateController:
		bUseControllerRotationYaw = false;
		break;
	default:
		break;
	}
}

void ASkyscraperCharacter::SendSkillActorSpawnPacket(ESkillActor SkillActor, FVector SpawnLocation, FVector ForwardVec)
{
	// bool IsTeamA;
	// (Team == "TeamA") ? IsTeamA = true : IsTeamA = false;

	if(MainGameMode)
		MainGameMode->SendSkillActorSpawn(SkillActor, SpawnLocation, ForwardVec);
}

void ASkyscraperCharacter::ResetPowerBuffValue()
{
	GetWorld()->GetTimerManager().ClearTimer(PowerBuffTimerHandle);
	PowerBuffValue = 1.0f;
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
		// 아이템 상호작용
		EnhancedInputComponent->BindAction(IA_ItemInteraction, ETriggerEvent::Triggered, this, &ASkyscraperCharacter::ItemInteraction);
		EnhancedInputComponent->BindAction(IA_ItemUsing, ETriggerEvent::Started, this, &ASkyscraperCharacter::UseItem);
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

		// 좌, 우, 뒤 이동시 이동속도를 느리게 하기 위해 crouch를 사용
		if((MovementVector.Y + 1.0f) <= FLT_EPSILON)   // 뒤로 이동 중이라면,
		{
			Crouch();
			GetCharacterMovement()->MaxWalkSpeedCrouched = 300.0f;
		}
		else if ( !(MovementVector.X <= FLT_EPSILON)  &&  (!((MovementVector.Y - 1.0f) <= FLT_EPSILON)) ) // 좌우 이동중이며, 전방이동 하지 않을 시
		{
			Crouch();
			GetCharacterMovement()->MaxWalkSpeedCrouched = 450.0f;
		}
		else
		{
			UnCrouch();
		}

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



void ASkyscraperCharacter::ItemInteraction()
{


	// 월드 내 오브젝트 중 아이템 액터 찾기
	// 다만, 월드 내 모든 오브젝트에 대해서 탐색하는 것이므로 굳이 런타임중 0~3개 만 존재하는 액터에 대해서
	// GetAllActorsOfClass 를 하는 것은 매우 비효율 적일 것으로 예상되므로
	// 다른 방법을 찾아보기 (노션 탐구)
	TArray<AActor*> ItemActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALootingItemActor::StaticClass(), ItemActors);

	// C++ 인터페이스 함수 실행
	for(AActor* ItemActor : ItemActors)
	{
		if (IItemInteraction* ItemInterface = Cast<IItemInteraction>(ItemActor))
		{
			ItemInterface->ItemInteraction(this);
		}
	}

}

void ASkyscraperCharacter::UseItem() 
{


	UE_LOG(LogTemp, Warning, TEXT("no item has"));
	if(OwningItem.Key != EItemEffect::EIE_NONE)
	{
		UE_LOG(LogTemp, Warning, TEXT("character use item"));
		if(ItemObject* Object =	ItemFactory::CreateItem(OwningItem.Key, OwningItem.Value))
		{
			Object->DoItemEffect(this);
			delete Object;
		}
		OwningItem.Key = EItemEffect::EIE_NONE;
		OwningItem.Value = EItemRareLevel::EIRL_NONE;
	}
}
