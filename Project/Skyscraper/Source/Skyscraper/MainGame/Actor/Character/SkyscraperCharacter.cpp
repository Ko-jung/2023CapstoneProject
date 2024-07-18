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

#include "EnhancedPlayerInput.h"
#include "NiagaraComponent.h"
#include "PlayMontageCallbackProxy.h"
#include "Kismet/GameplayStatics.h"
#include "Skyscraper/MainGame/Actor/LootingItem/LootingItemActor.h"
#include "Skyscraper/MainGame/Component/Combat/CombatSystemComponent.h"
#include "Skyscraper/MainGame/Component/Health/HealthComponent.h"
#include "Skyscraper/MainGame/Component/Jetpack/JetpackComponent.h"
#include "Skyscraper/MainGame/Item/ItemFactory/ItemFactory.h"
#include "Skyscraper/MainGame/Item/ItemObject/ItemObject.h"
#include "Skyscraper/MainGame/Component/LiquidWet/LiquidWetComponent.h"

#include "../../../Network/MainGameMode.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Skyscraper/MainGame/Component/Combat/CombatSystemComponent.h"
#include "Skyscraper/MainGame/Core/SkyscraperPlayerController.h"
#include "UObject/UnrealTypePrivate.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ASkyscraperCharacter

ASkyscraperCharacter::ASkyscraperCharacter()
{
	CharacterType = ECharacterSelect::ECS_Null;

	float CapsuleHeightSize = 76.5f;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, CapsuleHeightSize);

	bIsHover = false;
	CharacterMaxWalkSpeed = 480.0f;
	CharacterBwdMaxWalkSpeed = 110.0f;
	CharacterBesideMaxWalkSpeed = 150.0f;
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
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 10.0f, 0.0f);

	{// Create a camera boom (pulls in towards the player if there is a collision)
		CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
		CameraBoom->SetupAttachment(RootComponent);
		CameraBoom->TargetArmLength = InitialCameraArmLength;// The camera follows at this distance behind the character	
		CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
		CameraBoom->SetRelativeLocation(InitialCameraBoomOffset);
	}

	// Create a follow camera
	{
		FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
		FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
		FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

		DefaultFOV = 90.0f;
		DashFOV = 120.0f;
	}

	// Dash Effect Niagara System
	{
		NS_DashEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NS_DashEffect"));
		static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_DashEffectRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/2019180031/MainGame/Fbx/DashEffect/NS_DashEffect.NS_DashEffect'"));
		NS_DashEffect->SetAsset(NS_DashEffectRef.Object);
		NS_DashEffect->SetupAttachment(FollowCamera);
		NS_DashEffect->SetRelativeLocation(FVector{ 120.0f,0.f,0.f });
		NS_DashEffect->SetRelativeRotation(FRotator{ 90.0f,0.0f,0.0f });
		NS_DashEffect->SetHiddenInGame(true);
	}

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	{ // == Set Mesh Charcter
		// == Find and set USkeletalMesh from directory
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/character/4_assassin/assassin.assassin'"));
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -CapsuleHeightSize - 0.5f));
		GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
		// == Find and set AnimBlueprint (TEMP, Refactor to c++ later)
		static ConstructorHelpers::FClassFinder<UAnimInstance> AnimBPAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/2019180031/MainGame/Animation/Assassin/ABP_Assassin.ABP_Assassin_C'"));
		GetMesh()->SetAnimClass(AnimBPAsset.Class);

	}

	{// 부스터 메쉬 추가
		BoostMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BoostSkeletalMesh"));
		BoostMesh->SetupAttachment(GetMesh(),TEXT("Bip001-Spine"));
	}

	// LiquidWet 컴퍼넌트 추가
	{
		LiquidWetComponent = CreateDefaultSubobject<ULiquidWetComponent>(TEXT("LiquidWetComponent"));
	}
	

	{ // == Set Input Asset

		static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_DefaultAsset(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/2019180031/MainGame/Core/Input/Default/IMC_Default.IMC_Default'"));
		DefaultMappingContext = IMC_DefaultAsset.Object;

		static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_OnlyMouseAsset(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/2019180016/Input/IMC_OnlyMouse.IMC_OnlyMouse'"));
		OnlyMouseMappingContext = IMC_OnlyMouseAsset.Object;

		static ConstructorHelpers::FObjectFinder<UInputAction> IA_MoveAsset(TEXT("/Script/EnhancedInput.InputAction'/Game/2019180031/MainGame/Core/Input/Default/IA_GameDefaultMove.IA_GameDefaultMove'"));
		MoveAction = IA_MoveAsset.Object;

		static ConstructorHelpers::FObjectFinder<UInputAction> IA_JumpAsset(TEXT("/Script/EnhancedInput.InputAction'/Game/2019180031/MainGame/Core/Input/Default/IA_GameDefaultJump.IA_GameDefaultJump'"));
		JumpAction = IA_JumpAsset.Object;

		static ConstructorHelpers::FObjectFinder<UInputAction> IA_LookAsset(TEXT("/Script/EnhancedInput.InputAction'/Game/2019180031/MainGame/Core/Input/Default/IA_GameDefaultLook.IA_GameDefaultLook'"));
		LookAction = IA_LookAsset.Object;

		static ConstructorHelpers::FObjectFinder<UInputAction> IA_ItemInteractionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/2019180031/MainGame/Core/Input/Default/IA_GameDefaultItemInteraction.IA_GameDefaultItemInteraction'"));
		IA_ItemInteraction = IA_ItemInteractionRef.Object;

		static ConstructorHelpers::FObjectFinder<UInputAction> IA_ItemUsingRef(TEXT("/Script/EnhancedInput.InputAction'/Game/2019180031/MainGame/Core/Input/Default/IA_GameDefault_ItemUsing.IA_GameDefault_ItemUsing'"));
		IA_ItemUsing = IA_ItemUsingRef.Object;

		static ConstructorHelpers::FObjectFinder<UInputAction> IA_ObserveModeRef(TEXT("/Script/EnhancedInput.InputAction'/Game/2019180031/MainGame/Core/Input/Default/IA_GameDefault_ObserveMode.IA_GameDefault_ObserveMode'"));
		IA_ObserveMode = IA_ObserveModeRef.Object;


		// Observe
		static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_ObserveRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/2019180031/MainGame/Core/Input/ObserveMode/IMC_Observe.IMC_Observe'"));
		IMC_Observe = IMC_ObserveRef.Object;

		static ConstructorHelpers::FObjectFinder<UInputAction> IA_CameraZoomRef(TEXT("/Script/EnhancedInput.InputAction'/Game/2019180031/MainGame/Core/Input/ObserveMode/IA_Observe_CameraZoom.IA_Observe_CameraZoom'"));
		IA_Observe_CameraZoom = IA_CameraZoomRef.Object;

		static ConstructorHelpers::FObjectFinder<UInputAction> IA_Observe_LookRef(TEXT("/Script/EnhancedInput.InputAction'/Game/2019180031/MainGame/Core/Input/ObserveMode/IA_Observe_Look.IA_Observe_Look'"));
		IA_Observe_Look = IA_Observe_LookRef.Object;
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

		// Boost
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_BoostRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Assassin/Boost/AM_Assassin_Boost.AM_Assassin_Boost'"));
		CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_Boost, AM_BoostRef.Object);
	}

	// Gravity Change Area
	{
		ConstructorHelpers::FClassFinder<AActor> BP_GravityChangerAreaRef(TEXT("/Script/Engine.Blueprint'/Game/2019180031/MainGame/Actor/GravityChanger/BP_GravityChangerArea_Low.BP_GravityChangerArea_Low_C'"));
		if (BP_GravityChangerAreaRef.Succeeded())
		{
			BP_GravityChangerAreaClass = BP_GravityChangerAreaRef.Class;
		}

		ConstructorHelpers::FClassFinder<AActor> BP_GravityChangerArea2Ref(TEXT("/Script/Engine.Blueprint'/Game/2019180031/MainGame/Actor/GravityChanger/BP_GravityChangerArea_High.BP_GravityChangerArea_High_C'"));
		if (BP_GravityChangerAreaRef.Succeeded())
		{
			BP_GravityChangerAreaHighClass = BP_GravityChangerArea2Ref.Class;
		}
	}

	// Other Value use to Skill
	{	
		DisableLockOn = false;
		CanEnemyLockOnMe = true;
	}

	// 아이템 이펙트(오버레이 머테리얼)
	{
		for(int i = 0; i < static_cast<int>(EItemEffect::EIE_COUNT); ++i)
		{
			MI_ItemOverlay.AddDefaulted();
		}

		static ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> MI_InvincibilityRef(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/2019180031/MainGame/Material/Outline/M_Overlay_Invincibility.M_Overlay_Invincibility'"));
		if(MI_InvincibilityRef.Succeeded())
		{
			MI_ItemOverlay[static_cast<int>(EItemEffect::EIE_Single_GodMode)] = MI_InvincibilityRef.Object;
		}

		static ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> MI_HPUpRef(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/2019180031/MainGame/Material/Outline/M_Overlay_HPUp.M_Overlay_HPUp'"));
		if (MI_HPUpRef.Succeeded())
		{
			MI_ItemOverlay[static_cast<int>(EItemEffect::EIE_Team_PlusHealth)] = MI_HPUpRef.Object;
		}

		static ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> MI_InfinityRef(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/2019180031/MainGame/Material/Outline/M_Overlay_Infinity.M_Overlay_Infinity'"));
		if (MI_InfinityRef.Succeeded())
		{
			MI_ItemOverlay[static_cast<int>(EItemEffect::EIE_Single_BoostBulletInfinity)] = MI_InfinityRef.Object;
		}

		static ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> MI_PowerUp(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/2019180031/MainGame/Material/Outline/M_Overlay_PowerUp.M_Overlay_PowerUp'"));
		if (MI_PowerUp.Succeeded())
		{
			MI_ItemOverlay[static_cast<int>(EItemEffect::EIE_Team_Power)] = MI_PowerUp.Object;
		}

		static ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> MI_SpeedUp(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/2019180031/MainGame/Material/Outline/M_Overlay_SpeedUp.M_Overlay_SpeedUp'"));
		if (MI_SpeedUp.Succeeded())
		{
			MI_ItemOverlay[static_cast<int>(EItemEffect::EIE_Team_Speed)] = MI_SpeedUp.Object;
		}
	}
}

void ASkyscraperCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	{ // 숙이기(crouch)중 카메라 위치 변하지 않도록 값 설정
		GetCharacterMovement()->SetCrouchedHalfHeight(GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight());
	}
	
	//Add Input Mapping Context Move To ASkyscraperCharacter::AddCharacterMappingContext()
	AddCharacterMappingContext();

	auto gamemode = UGameplayStatics::GetGameMode(this);
	MainGameMode = Cast<AMainGameMode>(gamemode);
	UE_LOG(LogClass, Warning, TEXT("ASkyscraperCharacter::BeginPlay() Cast<AMainGameMode>(gamemode) result: %d"), MainGameMode ? 1 : 0);
}

void ASkyscraperCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsUnableAct)
	{
		const auto& Montage = GetAnimMontage(ECharacterAnimMontage::ECAM_Stun);
		UPlayMontageCallbackProxy* PlayMontageCallbackProxy = UPlayMontageCallbackProxy::CreateProxyObjectForPlayMontage(GetMesh(), Montage, 1.0f, 0.16f);

	}
}

void ASkyscraperCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	 
	JetpackComponent->OnLandJetpack();
}

ASkyscraperPlayerController* ASkyscraperCharacter::GetPlayerController() const
{
	return Cast<ASkyscraperPlayerController>(GetController()); 
}

float ASkyscraperCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// https://mingyu0403.tistory.com/258 PointDamage / RadialDamage ...

	if(HealthComponent)
	{
		HealthComponent->GetDamaged(DamageAmount, DamageCauser);
	}
	
	
	return Damage;
}

void ASkyscraperCharacter::DoStun(const AActor* Attacker, const float StunTime, const FVector StunDirection) const
{
	if (IsValid(MainGameMode) && MainGameMode->GetIsConnected())
	{
		MainGameMode->SendStunDown(Attacker, this, StunDirection, true, StunTime);
	}
	else
	{
		ApplyStun(StunTime, StunDirection);
	}
}

void ASkyscraperCharacter::DoDown(const AActor* Attacker, const FVector& DownDirection) const
{
	if (IsValid(MainGameMode) && MainGameMode->GetIsConnected())
	{
		MainGameMode->SendStunDown(Attacker, this, DownDirection);
	}
	else
	{
		ApplyDown(DownDirection);
	}	
}

UAnimMontage* ASkyscraperCharacter::GetAnimMontage(ECharacterAnimMontage eCharacterAnimMontage) const
{
	return *CharacterAnimMontages.Find(eCharacterAnimMontage);
}

void ASkyscraperCharacter::SetIsHover(bool NewIsHover)
{
	bIsHover = NewIsHover;
}


void ASkyscraperCharacter::SetDashEffectHiddenInGame(bool NewHidden) const
{
	if(NS_DashEffect)
	{
		NS_DashEffect->SetHiddenInGame(NewHidden);
	}
	
}

void ASkyscraperCharacter::SetCameraFOVToDash(bool bToDash, float Alpha)
{
	if(bToDash)
	{
		
		FollowCamera->SetFieldOfView(FMath::Lerp(DefaultFOV, DashFOV, Alpha));
	}
	else
	{
		FollowCamera->SetFieldOfView(FMath::Lerp(DashFOV, DefaultFOV, Alpha));
	}
}

void ASkyscraperCharacter::SpawnGravityChangerArea(bool bGravityLow)
{

	if(bGravityLow)
	{
		AActor* GravityActor = GetWorld()->SpawnActor<AActor>(BP_GravityChangerAreaClass);
		GravityActor->SetActorLocation(GetActorLocation());
	}
	else
	{
		AActor* GravityActor = GetWorld()->SpawnActor<AActor>(BP_GravityChangerAreaHighClass);
		GravityActor->SetActorLocation(GetActorLocation());
	}
}

void ASkyscraperCharacter::DoDisableLockOn(float Timer)
{
	GetWorld()->GetTimerManager().SetTimer(LockOnTimerHandle, this, &ThisClass::DoAbleLockOn, Timer, false);
	DisableLockOn = true;
}

void ASkyscraperCharacter::DoAbleLockOn()
{
	DisableLockOn = false;
}

void ASkyscraperCharacter::DoCantEnemyLockOnMe(float Timer)
{
	GetWorld()->GetTimerManager().SetTimer(EnemyLockOnTimerHandle, this, &ThisClass::DoCanEnemyLockOnMe, Timer, false);
	CanEnemyLockOnMe = false;
}

void ASkyscraperCharacter::DoCanEnemyLockOnMe()
{
	CanEnemyLockOnMe = true;
}

void ASkyscraperCharacter::SkillInteract(ESkillActor SkillActor, float Timer)
{
	switch (SkillActor)
	{
	case ESkillActor::BP_NULL:
		break;
	case ESkillActor::BP_BoomerangGrab:
		break;
	case ESkillActor::BP_BoomerangCenter:
		break;
	case ESkillActor::BP_DetectorMine:
		break;
	case ESkillActor::BP_DetectorEMP:
		SubtractFuelHalf();
		GetWorld()->GetTimerManager().SetTimer(LockOnTimerHandle, this, &ThisClass::DoAbleLockOn, Timer, false);
		DisableLockOn = true;
		break;
	case ESkillActor::BP_Shield:
		break;
	case ESkillActor::BP_ShieldSphere:
	{
		CanEnemyLockOnMe = bool(1 - CanEnemyLockOnMe);
		if (MainGameMode)
		{
			MainGameMode->SendSkillInteract(this, ESkillActor::BP_ShieldSphere);
		}
		break;
	}
	case ESkillActor::BP_ShieldSphereThrow:
		break;
	case ESkillActor::BP_WindTornado:
		break;
	case ESkillActor::BP_ElectSphereBoom:
		break;
	case ESkillActor::BP_ElectTrap:
		break;
	default:
		break;
	}
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

void ASkyscraperCharacter::SendAnimMontageStatus(ECharacterAnimMontage eMontage, int SectionNum)
{
	if (SectionNum == INDEX_NONE)
	{
		UE_LOG(LogClass, Warning, TEXT("Montage Cant find Enum Value is %d, SectionNum is %d"), eMontage, SectionNum);
	}

	if (MainGameMode)
		MainGameMode->SendAnimMontageStatus(this, eMontage, SectionNum);
}

void ASkyscraperCharacter::ApplyStun(const float StunTime, const FVector StunDirection) const
{
	if (CombatSystemComponent)
	{
		CombatSystemComponent->Stun(StunTime, StunDirection);
	}
}

void ASkyscraperCharacter::ApplyDown(const FVector& DownDirection) const
{
	if (CombatSystemComponent)
	{
		CombatSystemComponent->Down(DownDirection);
	}
}

void ASkyscraperCharacter::AddInputMappingContext()
{
	AddCharacterMappingContext();

	CombatSystemComponent->AddInputMappingContext();
	CombatSystemComponent->BindingInputActions();

	JetpackComponent->AddInputMappingContext();
	JetpackComponent->BindingInputActions();

	HealthComponent->AddWidget();
}

void ASkyscraperCharacter::AddCharacterMappingContext()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
			
		}
	}
}

void ASkyscraperCharacter::ObserveLook(const FInputActionValue& InputActionValue)
{
	// input is a Vector2D
	FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (Controller != nullptr)
	{
		GetPlayerController()->SetControlRotation(GetPlayerController()->GetControlRotation().Add(-LookAxisVector.Y, LookAxisVector.X, 0.0f));
	}
}

void ASkyscraperCharacter::AddObserveInputMappingContext()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC_Observe, 0);
		}
	}
}

void ASkyscraperCharacter::RemoveObserveInputMappingContext()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(IMC_Observe);
		}
	}
}

void ASkyscraperCharacter::SyncTransformAndAnim(FTransform t, float s, FRotator r)
{
	SetActorTransform(t);
	SetSpeed(s);
	//SetXRotate(r);
	Controller->SetControlRotation(r);
}

void ASkyscraperCharacter::SetMontage(ECharacterAnimMontage eAnimMontage, int SectionNum)
{
	const auto AnimMontage = CharacterAnimMontages.Find(eAnimMontage);
	if (AnimMontage)
	{
		PlayAnimMontage(*AnimMontage, 1.f, (*AnimMontage)->GetSectionName(SectionNum));
	}
	else
	{	// Play Montage On Blueprint
		PlaySkillMontage(eAnimMontage == ECharacterAnimMontage::ECAM_SpecialSkill, SectionNum);
		UE_LOG(LogClass, Warning, TEXT("ASkyscraperCharacter::SetMontage() play Skill Montage"));
	}
}

void ASkyscraperCharacter::SetSpeedBuffValue(float NewSpeedBuffValue, float fBuffTime)
{
	SpeedBuffValue = NewSpeedBuffValue;
	GetCharacterMovement()->MaxWalkSpeed = CharacterMaxWalkSpeed* SpeedBuffValue;
	SetItemEffectAndOverlayMaterial(EItemEffect::EIE_Team_Speed, true);
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

void ASkyscraperCharacter::AddSpeedBuffValue(float AddSpeedBuffValue)
{
	SpeedBuffValue += AddSpeedBuffValue;
}

void ASkyscraperCharacter::ResetSpeedBuffValue()
{
	GetWorld()->GetTimerManager().ClearTimer(SpeedBuffTimerHandle);
	SpeedBuffValue = 1.0f;
	GetCharacterMovement()->MaxWalkSpeed = CharacterMaxWalkSpeed;
	SetItemEffectAndOverlayMaterial(EItemEffect::EIE_Team_Speed, false);
	UE_LOG(LogTemp, Warning, TEXT("ASkyscraperCharacter::ResetSpeedBuffValue Called. GetCharacterMovement()->MaxWalkSpeed is %f"), GetCharacterMovement()->MaxWalkSpeed);
}

void ASkyscraperCharacter::SetPowerBuffValue(float NewPowerBuffValue, float fBuffTime)
{
	PowerBuffValue = NewPowerBuffValue;;

	SetItemEffectAndOverlayMaterial(EItemEffect::EIE_Team_Power, true);

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

void ASkyscraperCharacter::AddItem(EItemEffect ItemEffect, EItemRareLevel RareLevel, AActor* Item)
{
	if(OwningItem.Key==EItemEffect::EIE_NONE)
	{
		OwningItem.Key = ItemEffect; OwningItem.Value = RareLevel;
		UE_LOG(LogTemp, Warning, TEXT("character earn item"));
	}

	if(GetPlayerController())
	{
		GetPlayerController()->SetItemImage(ItemEffect);
	}

	// 2019180031: LootingItem 외에 아이템이 흭득되는 경우가 존재하여 해당 함수를 위한 condition으로 추가
	if(MainGameMode && Item)
		MainGameMode->SendGetItem(this, Item);
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

void ASkyscraperCharacter::PlayBoostAnimation(const FString& SectionString) const
{
	
	if (BoostMesh)
	{
		FName SectionName = FName(*SectionString);
		UAnimMontage* BoostAnimMontage = GetAnimMontage(ECharacterAnimMontage::ECAM_Boost);
		if (BoostAnimMontage->IsValidSectionName(SectionName))
		{
			UPlayMontageCallbackProxy* PlayMontageCallbackProxy = UPlayMontageCallbackProxy::CreateProxyObjectForPlayMontage(BoostMesh, BoostAnimMontage, 1.0f, 0,SectionName);
		}
	}
}

void ASkyscraperCharacter::SendSkillActorSpawnPacket(const AActor* Sender, ESkillActor SkillActor, FVector SpawnLocation, FVector ForwardVec)
{
	// bool IsTeamA;
	// (Team == "TeamA") ? IsTeamA = true : IsTeamA = false;

	if (MainGameMode)
	{
		MainGameMode->SendSkillActorSpawn(Sender, SkillActor, SpawnLocation, ForwardVec);
	}
	else
	{	// Single Mode
		AActor* NewActor;
		SkillActorSpawnUsingPacket(!(SkillActor == ESkillActor::BP_ElectTrap || SkillActor == ESkillActor::BP_DetectorMine),
			SpawnLocation, ForwardVec, NewActor	);
	}
}

void ASkyscraperCharacter::ResetPowerBuffValue()
{
	GetWorld()->GetTimerManager().ClearTimer(PowerBuffTimerHandle);
	PowerBuffValue = 1.0f;
	SetItemEffectAndOverlayMaterial(EItemEffect::EIE_Team_Power, false);
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
		EnhancedInputComponent->BindAction(IA_ObserveMode, ETriggerEvent::Started, this, &ASkyscraperCharacter::StartObserveMode);

		EnhancedInputComponent->BindAction(IA_Observe_CameraZoom, ETriggerEvent::Triggered, this, &ASkyscraperCharacter::SetCameraZoomUpDown);
		EnhancedInputComponent->BindAction(IA_Observe_Look, ETriggerEvent::Triggered, this, &ASkyscraperCharacter::ObserveLook);
		EnhancedInputComponent->BindAction(IA_ObserveMode, ETriggerEvent::Completed, this, &ASkyscraperCharacter::EndObserveMode);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ASkyscraperCharacter::RemoveAllInputMappingTemporary()
{
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			//Subsystem->RemoveMappingContext(DefaultMappingContext);
			//if (CombatSystemComponent) CombatSystemComponent->RemoveAllInputMappingTemporary(Subsystem);
			//if (JetpackComponent) JetpackComponent->RemoveAllInputMappingTemporary(Subsystem);

		}
	}
}

void ASkyscraperCharacter::AddAllInputMappingContext()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
			if (CombatSystemComponent) CombatSystemComponent->AddAllInputMappingContext(Subsystem);
			if (JetpackComponent) JetpackComponent->AddInputMappingContext();
		}
	}
}

void ASkyscraperCharacter::CustomDepthOn()
{
	UE_LOG(LogClass, Warning, TEXT("ASkyscraperCharacter::CustomDepthOn()"));
	//GetMesh()->bRenderCustomDepth = true;
	SetCustomDepth(true);
	GetWorld()->GetTimerManager().SetTimer(DetectingTimerHandle, this, &ThisClass::CustomDepthOff, 5.f, false);
}

void ASkyscraperCharacter::CustomDepthOff()
{
	UE_LOG(LogClass, Warning, TEXT("ASkyscraperCharacter::CustomDepthOff()"));
	//GetMesh()->bRenderCustomDepth = false;
	SetCustomDepth(false);
}

void ASkyscraperCharacter::SubtractFuelHalf()
{
	JetpackComponent->SubtractFuelHalf();
}

void ASkyscraperCharacter::ChangeMappingContext(bool IsOnlyMouseMode)
{
	//if (IsOnlyMouseMode)
	//{
	//	RemoveAllInputMappingTemporary(false);
	//	AddAllInputMappingContext(true);
	//}
	//else
	//{
	//	RemoveAllInputMappingTemporary(true);
	//	AddAllInputMappingContext(false);
	//}
}

void ASkyscraperCharacter::CastingSkill(bool IsSpecialSkill)
{
	ActiveSkill(IsSpecialSkill);
}

void ASkyscraperCharacter::AbleToAct()
{
	IsUnableAct = false;
}

void ASkyscraperCharacter::ApplyStun(const float StunTime)
{
	//UnableToAct(StunTime);
	GetWorld()->GetTimerManager().SetTimer(UnableActTimerHandle, this, &ThisClass::AbleToAct, StunTime, false);
	IsUnableAct = true;
}

bool ASkyscraperCharacter::IsAlliance(AActor* Target)
{
	const auto& TargetTags = Target->Tags;
	const auto& MyTags = Tags;

	// Check Target Is Self
	if (this == Target) return true;

	// If has no Tag, is Enemy
	if (!TargetTags.IsValidIndex(0) || !MyTags.IsValidIndex(0)) return false;

	// Check Alliance
	if (TargetTags[0] == MyTags[0]) return true;
	return false;
}

void ASkyscraperCharacter::SetItemEffectAndOverlayMaterial(EItemEffect TargetItemEffect, bool bAdd)
{
	if(bAdd)
	{
		CurrentItemEffects.AddUnique(TargetItemEffect);

		if (MI_ItemOverlay[static_cast<int>(TargetItemEffect)])
		{
			GetMesh()->SetOverlayMaterial(MI_ItemOverlay[static_cast<int>(TargetItemEffect)]);
		}
	}
	else
	{
		if(CurrentItemEffects.Contains(TargetItemEffect))
		{
			CurrentItemEffects.Remove(TargetItemEffect);
		}

		UMaterialInterface* ChangeMaterial = nullptr;
		if(!CurrentItemEffects.IsEmpty())
		{
			ChangeMaterial = MI_ItemOverlay[static_cast<int>(CurrentItemEffects[0])];
		}
		GetMesh()->SetOverlayMaterial(ChangeMaterial);
	}
}


void ASkyscraperCharacter::ActiveSkill_Implementation(bool IsSpecialSkill)
{
}
void ASkyscraperCharacter::SetCustomDepth_Implementation(bool On)
{
}
void ASkyscraperCharacter::PlaySkillMontage_Implementation(bool IsSpecialSkill, uint8 SectionNum)
{
}
void ASkyscraperCharacter::SkillActorSpawnUsingPacket_Implementation(bool IsSpecialSkill, FVector SpawnLocation, FVector ForwardVector, AActor*& NewActor)
{
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
		if(MovementVector.Y < 0.0f)   // 뒤로 이동 중이라면,
		{
			Crouch();
			GetCharacterMovement()->MaxWalkSpeedCrouched = CharacterBwdMaxWalkSpeed;
		}
		else if ( (abs(MovementVector.X) >= FLT_EPSILON)  &&  MovementVector.Y <= FLT_EPSILON ) // 좌우 이동중이며, 전방이동 하지 않을 시
		{
			Crouch();
			GetCharacterMovement()->MaxWalkSpeedCrouched = CharacterBesideMaxWalkSpeed;
		}
		else
		{
			UnCrouch();
		}

		// 대각선 이동 체크
		bIsMoveDiagonally = !(abs(MovementVector.Y) <= KINDA_SMALL_NUMBER) && !(abs(MovementVector.X) <= KINDA_SMALL_NUMBER);
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
	TArray<AActor*> ItemActors;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALootingItemActor::StaticClass(), ItemActors);
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	
	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetActorLocation(), 100.0f, ObjectTypes, nullptr, ActorsToIgnore, ItemActors);

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
		if(TObjectPtr<UItemObject> Object = UItemFactory::CreateItem(OwningItem.Key, OwningItem.Value))
		{
			if (MainGameMode)
				MainGameMode->SendUseItem(this, (BYTE)OwningItem.Key, (BYTE)OwningItem.Value);

			Object->DoItemEffect(this);
			//delete Object;
		}
		OwningItem.Key = EItemEffect::EIE_NONE;
		OwningItem.Value = EItemRareLevel::EIRL_NONE;
		if(GetPlayerController())
		{
			GetPlayerController()->SetItemImage(EItemEffect::EIE_NONE);
		}
	}
}

void ASkyscraperCharacter::StartObserveMode()
{
	GetPlayerController()->SetObserveMode(true);
}

void ASkyscraperCharacter::EndObserveMode()
{
	GetPlayerController()->SetObserveMode(false);
}

void ASkyscraperCharacter::SetCameraZoomUpDown(const FInputActionValue& Value)
{
	float ZoomValue = Value.Get<float>();

	UE_LOG(LogTemp, Warning, TEXT("%f"), ZoomValue);

	float ZoomSpeed = 10.0f;
	float MaxArmLength = InitialCameraArmLength + 150.0f;
	float MinArmLength = InitialCameraArmLength - 300.0f;

	CameraBoom->TargetArmLength = FMath::Clamp(CameraBoom->TargetArmLength +  ZoomSpeed * -ZoomValue, MinArmLength, MaxArmLength);

	float LerpAlpha = (CameraBoom->TargetArmLength - MinArmLength) / (MaxArmLength - MinArmLength);
	CameraBoom->SetRelativeLocation(FMath::Lerp(FVector{ 0.0f,0.0f,0.0f }, InitialCameraBoomOffset, LerpAlpha));
}
