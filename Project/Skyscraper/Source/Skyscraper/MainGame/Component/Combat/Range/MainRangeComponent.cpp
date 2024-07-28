// Fill out your copyright notice in the Description page of Project Settings.


#include "MainRangeComponent.h"

#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PlayMontageCallbackProxy.h"
#include "Components/InputComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "Skyscraper/MainGame/Actor/Damage/DamageSpawner.h"
#include "Skyscraper/MainGame/Component/Damage/DamageComponent.h"
#include "Skyscraper/MainGame/Component/Health/HealthComponent.h"
#include "Skyscraper/MainGame/Core/SkyscraperPlayerController.h"
#include "Skyscraper/MainGame/Widget/Ammo/MyAmmoWidget.h"

#include "Skyscraper/Network/MainGameMode.h"
#include "Skyscraper/Subsystem/SkyscraperEngineSubsystem.h"

#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Skyscraper/MainGame/Actor/SkillActor/Shield.h"

// Sets default values for this component's properties
UMainRangeComponent::UMainRangeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	OwnerCharacter = nullptr;
	CurrentFireCoolTime = -1.0f;
	FireMaxCoolTime = 0.5f;

	CurrentReloadCoolTime = -1.0f;
	ReloadMaxCoolTime = 5.0f;
	ReloadSpeedTime = 1.0f;

	BulletMaxCount = 20;
	CurrentBulletCount = BulletMaxCount;

	RecoilAboveAmount = 1.0f;
	RecoilBesideAmount = 1.0f;
	RecoilTime = 0.1f;
	RecoilSpeed = 10.0f;

	OwnerAnimInstance = nullptr;
	//const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_FireRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Rifle/AM_FireRifle.AM_FireRifle'"));
	//AM_Fire = AM_FireRef.Object;
	//const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_ReloadRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Rifle/AM_ReloadRifle.AM_ReloadRifle'"));
	//AM_Reload = AM_ReloadRef.Object;
	AnimMontageKey = ECharacterAnimMontage::ECAM_Default;

	RangeWeaponType = ERangeSelect::ERS_NONE;


	{ // == Set Input Asset
		static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_RangeInputRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/2019180031/MainGame/Core/Input/Combat/Range/IMC_RangeInput.IMC_RangeInput'"));
		IMC_RangeInput = IMC_RangeInputRef.Object;

		static ConstructorHelpers::FObjectFinder<UInputAction> IA_FireRef(TEXT("/Script/EnhancedInput.InputAction'/Game/2019180031/MainGame/Core/Input/Combat/Range/IA_Fire.IA_Fire'"));
		IA_Fire = IA_FireRef.Object;

		static ConstructorHelpers::FObjectFinder<UInputAction> IA_ReloadRef(TEXT("/Script/EnhancedInput.InputAction'/Game/2019180031/MainGame/Core/Input/Combat/Range/IA_Reload.IA_Reload'"));
		IA_Reload = IA_ReloadRef.Object;
	}

	{ // 탄창 위젯 클래스 로드
		static ConstructorHelpers::FClassFinder<UUserWidget> WBP_MyAmmoClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/2019180031/MainGame/Widget/Ammo/WBP_MyAmmo.WBP_MyAmmo_C'"));
		MyAmmoClass = WBP_MyAmmoClass.Class;

		static ConstructorHelpers::FClassFinder<UUserWidget> WBP_MainRangeWidgetRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/2019180031/MainGame/Widget/Combat/Range/MainRangeWidget.MainRangeWidget_C'"));
		MainRangeWidgetClass = WBP_MainRangeWidgetRef.Class;
	}

	// Muzzle Flash 이펙트 로드
	{
		static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_MuzzleFlashRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/2019180031/MainGame/Fbx/MuzzleFlash/NS_MuzzleFlash.NS_MuzzleFlash'"));
		if(NS_MuzzleFlashRef.Succeeded())
		{
			NS_MuzzleFlash = NS_MuzzleFlashRef.Object;
		}
	}

	// Hit Effect 로드
	{
		static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_HitEffectRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/2019180031/MainGame/Fbx/HitEffect/NS_HitEffect.NS_HitEffect'"));
		if (NS_HitEffectRef.Succeeded())
		{
			NS_HitEffect = NS_HitEffectRef.Object;
		}
	}

	// BloodSpawner 로드
	{
		static ConstructorHelpers::FClassFinder<AActor> BP_BloodSpawnerRef(TEXT("/Script/Engine.Blueprint'/Game/2019180031/MainGame/Actor/BloodSpawner/BP_Blood_Drops.BP_Blood_Drops_C'"));
		if(BP_BloodSpawnerRef.Succeeded())
		{
			BP_BloodSpawner = BP_BloodSpawnerRef.Class;
		}
	}

	{
		WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Main Range Weapon"));

		NS_WeaponCreate = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NS_MainWeaponCreate"));
		NS_WeaponCreate->SetupAttachment(WeaponMeshComponent);

		static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_WeaponCreateRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/2019180031/MainGame/Fbx/WeaponCreate/NS_WeaponCreate.NS_WeaponCreate'"));
		if (NS_WeaponCreateRef.Succeeded())
		{
			NS_WeaponCreate->SetAsset(NS_WeaponCreateRef.Object);
			
		}
	}
}


// Called when the game starts
void UMainRangeComponent::BeginPlay()
{
	Super::BeginPlay();


	// 소유자 정보 로드
	OwnerCharacter = Cast<ASkyscraperCharacter>(GetOwner());
	BindingInputActions();
	OwnerAnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();

	// 소유자에게 무기 부착
	FAttachmentTransformRules AttachmentTransformRules{EAttachmentRule::SnapToTarget,false};
	WeaponMeshComponent->AttachToComponent(OwnerCharacter->GetMesh(), AttachmentTransformRules, WeaponSocketName);
	SetWeaponHiddenInGame(true);

	// 총알 탄수 초기화
	CurrentBulletCount = BulletMaxCount;

	

	
	{// == UI 연결하기 // UI BulletCount set
		if (GetOwnerPlayerController())
		{
			UUserWidget* Widget = CreateWidget(GetOwnerPlayerController(), MyAmmoClass);
			if (Widget)
			{
				MyAmmoWidget = Cast<UMyAmmoWidget>(Widget);
				MyAmmoWidget->AddToViewport();
				MyAmmoWidget->SetRangeWeapon(RangeWeaponType);
			}

			MainRangeWidget = CreateWidget(GetOwnerPlayerController(), MainRangeWidgetClass);
			if(MainRangeWidget)
			{
				MainRangeWidget->AddToViewport();
			}
		}

	}

	SetInitialValue();

}


void UMainRangeComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	//Unbind Input Mapping Context
	RemoveThisWeapon();

	// Unbind Melee Widget
	if (MainRangeWidget)
	{
		MainRangeWidget->RemoveFromParent();
	}

	if(MyAmmoWidget)
	{
		MyAmmoWidget->RemoveFromParent();
	}
}

void UMainRangeComponent::SetInitialValue()
{
}

void UMainRangeComponent::AddInputMappingContext()
{
	if (APlayerController* PlayerController = GetOwnerPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC_RangeInput, 0);

			
		}
	}
}

void UMainRangeComponent::BindingInputActions()
{
	if (!OwnerCharacter->GetPlayerController()) return;

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(OwnerCharacter->GetPlayerController()->InputComponent))
	{
		EnhancedInputComponent->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &ThisClass::PlayFireAnim);
		EnhancedInputComponent->BindAction(IA_Reload, ETriggerEvent::Started, this, &ThisClass::PlayReloadAnim);
	}
}

void UMainRangeComponent::RemoveInputMappingContext()
{
	if (APlayerController* PlayerController = GetOwnerPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(IMC_RangeInput);

		}
	}
}

void UMainRangeComponent::SetWeaponHiddenInGame(bool bNewHidden) const
{
	if(WeaponMeshComponent)
	{
		WeaponMeshComponent->SetHiddenInGame(bNewHidden);
	}
	if(NS_WeaponCreate)
	{
		NS_WeaponCreate->SetVisibility(!bNewHidden);
	}
	
	
}


void UMainRangeComponent::AddThisWeapon()
{
	AddInputMappingContext();
	SetWeaponHiddenInGame(false);
	if (MainRangeWidget) MainRangeWidget->AddToViewport();
	if (NS_WeaponCreate)
	{
		NS_WeaponCreate->Activate(true);
	}
}

void UMainRangeComponent::RemoveThisWeapon()
{
	RemoveInputMappingContext();
	SetWeaponHiddenInGame(true);
	if (MainRangeWidget) MainRangeWidget->RemoveFromParent();
}


void UMainRangeComponent::PlayFireAnim()
{
	if (!OwnerCharacter->InputEnabled()) return;
	if (!CanFire()) return;
	 
	CurrentFireCoolTime = FireMaxCoolTime;

	//OwnerCharacter->PlayAnimMontage(OwnerCharacter->GetAnimMontage(FireAnimMontageKey));
	{ // == Play Montage
		UAnimMontage* PlayMontage = OwnerCharacter->GetAnimMontage(AnimMontageKey);
		FName StartingSection = FName(*(FString("Fire")));
		
		{	// Montage Sync
			OwnerCharacter->SendAnimMontageStatus(AnimMontageKey, PlayMontage->GetSectionIndex(StartingSection));
		}

		UPlayMontageCallbackProxy* PlayMontageCallbackProxy = UPlayMontageCallbackProxy::CreateProxyObjectForPlayMontage(OwnerCharacter->GetMesh(), PlayMontage, 1.0f, 0, StartingSection);
	}
	

	if(!FireCoolTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(FireCoolTimerHandle, this, &ThisClass::FireCoolDownTimerFunc, 0.1f, true);		
	}
	OwnerCharacter->CharacterAttackEvent();
}

void UMainRangeComponent::UseBullet()
{
	if(bIsBulletInfinity)
	{
		return;
	}

	CurrentBulletCount -= 1;
	
	if(MyAmmoWidget)
	{
		MyAmmoWidget->SetAmmoPercent(CurrentBulletCount, BulletMaxCount);
	}
	
}

void UMainRangeComponent::Fire(float fBaseDamage)
{
	fBaseDamage *= OwnerCharacter->GetPowerBuffValue();

	UseBullet();

	// Play Sound
	{
		if(USkyscraperEngineSubsystem* Subsystem = GEngine->GetEngineSubsystem<USkyscraperEngineSubsystem>())
		{
			if (USoundBase* FireSound = Subsystem->GetSkyscraperSound(FireSoundName))
			{
				if (USoundAttenuation* SoundAttenuation = Subsystem->GetSkyscraperSoundAttenuation())
				{
					UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, OwnerCharacter->GetActorLocation(), FRotator{}, 1, 1, 0, SoundAttenuation);
				}
			}
		}
		

	}


	if (!GetOwnerPlayerController()) 
	{
		EnemyFire(fBaseDamage);
		return;
	};

	{ // == Line Trace
		FVector Start = OwnerCharacter->GetCameraBoom()->GetComponentLocation();
		FVector End = Start +
			GetOwnerPlayerController()->GetControlRotation().Vector() * EffectiveDistance;
		FVector TargetLocation = End;
		TArray<AActor*> IgnoreActors;

		FHitResult OutHit;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(OwnerCharacter);
		//QueryParams.TraceTag = TEXT("DebugTraceTag");

		// ========================== 2019180016 ========================== 
		AMainGameMode* GameMode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(this));
		bool ComponentHitResult = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_WorldStatic, QueryParams);
		if (ComponentHitResult)
		{
			UPrimitiveComponent* PrimitiveComponent = OutHit.GetComponent();
			if (PrimitiveComponent->IsA(UHierarchicalInstancedStaticMeshComponent::StaticClass())
				&& PrimitiveComponent->GetName() == ("HISM_Window"))
			{
				if (GameMode)
				{
					GameMode->SendBreakObject(OwnerCharacter, PrimitiveComponent, OutHit.Item, EObjectType::Window);
				}
				else
				{
					//HISMWindow->RemoveInstance(HISMIndex[i]);
				}
			}
		}
		// ================================================================ 

		{	// SHield
			bool HitResult = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_Visibility, QueryParams);
			if (HitResult)
			{
				AActor* HitActor = OutHit.GetActor();
				TargetLocation = OutHit.Location;
				if (!OwnerCharacter->IsAlliance(HitActor) && HitActor->IsA(AShield::StaticClass()))
				{
					AShield* Shield = Cast<AShield>(HitActor);
					Shield->GetDamage(fBaseDamage);
					if (GameMode)
					{
						GameMode->SendDamagedSkillActor(OwnerCharacter, Shield->SpawnCharacter, ESkillActor::BP_Shield, HitActor);
					}

					// Hit 이펙트 생성
					if (NS_HitEffect)
					{
						UNiagaraFunctionLibrary::SpawnSystemAtLocation(
							GetWorld(), NS_HitEffect,
							OutHit.Location,
							FRotator{ 0.0f,0.0f,0.0f },
							FVector(1));
					}
				}
			}
		}

		{	// Character
			bool HitResult = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_Pawn, QueryParams);
			while (HitResult)		// if -> while to use break
			{
				AActor* HitActor = OutHit.GetActor();

				TargetLocation = OutHit.Location;

				// Execute on Sever
				if (GameMode && GameMode->GetIsConnected())
				{
					GameMode->SendTakeDamage(OwnerCharacter, HitActor);
				}
				else
				{
					UGameplayStatics::ApplyDamage(HitActor, fBaseDamage, nullptr, nullptr, nullptr);
				}


				if (OutHit.GetActor()->FindComponentByClass(UHealthComponent::StaticClass()))
				{
					{ // 대미지 컴퍼넌트 추가
						FTransform SpawnTransform;
						SpawnTransform.SetLocation(OutHit.Location);

						if (!Cast<ASkyscraperCharacter>(OutHit.GetActor())->IsCharacterGodMode())
						{
							UDamageComponent* DamageComp = Cast<UDamageComponent>(OutHit.GetActor()->AddComponentByClass(UDamageComponent::StaticClass(), true, SpawnTransform, false));
							if (DamageComp)
							{
								DamageComp->InitializeDamage(fBaseDamage);
							}
						}

					}
					// BloodSpawner 생성
					{
						FTransform Transform{ OutHit.Normal.Rotation().Quaternion(), OutHit.Location };
						AActor* BloodSpawner = GetWorld()->SpawnActorDeferred<AActor>(BP_BloodSpawner, Transform);
						if (BloodSpawner)
						{
							BloodSpawner->FinishSpawning(Transform);
						}
					}
				}



				// Hit 이펙트 생성
				if (NS_HitEffect)
				{
					UNiagaraFunctionLibrary::SpawnSystemAtLocation(
						GetWorld(), NS_HitEffect,
						OutHit.Location,
						FRotator{ 0.0f,0.0f,0.0f },
						FVector(1));
				}

				HitResult = false;
			}
		}
		

		// Muzzle Flash Effect
		if (NS_MuzzleFlash)
		{
			FVector FireLocation = WeaponMeshComponent->GetSocketLocation(TEXT("FireSocket"));
			UNiagaraComponent* FX = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NS_MuzzleFlash, FireLocation, (TargetLocation - FireLocation).Rotation(), FVector{ 1.0f,1.0f,1.0f });
			float Distance = FVector::Distance(FireLocation, TargetLocation);
			FX->SetVariableFloat(FName("Distance"), Distance);

		}


	}

	// == Recoil

	// == TODO: if have blood component, spawn blood

}

void UMainRangeComponent::EnemyFire(float fBaseDamage)
{
	// == Fore enemy fire (doesn't have player controller actor)
	{// == Line trace
		FVector Start = OwnerCharacter->GetCameraBoom()->GetComponentLocation();
		FVector End = Start +
			OwnerCharacter->GetController()->GetControlRotation().Vector() * EffectiveDistance;
		FVector TargetLocation = End;
		// TArray<AActor*> IgnoreActors;
		// FHitResult OutHit;
		// FCollisionQueryParams QueryParams;
		// QueryParams.AddIgnoredActor(OwnerCharacter);
		// 
		// 
		// bool HitResult = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_Pawn,QueryParams);
		// 
		// 
		// if (HitResult)
		// {
		// 	AActor* HitActor = OutHit.GetActor();
		// 	TargetLocation = OutHit.Location;
		// 
		// 	UGameplayStatics::ApplyDamage(HitActor, fBaseDamage, nullptr, OwnerCharacter, nullptr);
		// 
		// 	// Muzzle Flash Effect
		// }
		if (NS_MuzzleFlash)
		{
			FVector FireLocation = WeaponMeshComponent->GetSocketLocation(TEXT("FireSocket"));

			UNiagaraComponent* FX = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NS_MuzzleFlash, FireLocation, (TargetLocation - FireLocation).Rotation(), FVector{ 1.0f,1.0f,1.0f });
			float Distance = FVector::Distance(FireLocation, TargetLocation);
			FX->SetVariableFloat(FName("Distance"), Distance);

		}
	}
}

void UMainRangeComponent::BulletReloading()
{
	CurrentReloadCoolTime = ReloadMaxCoolTime;

	CurrentBulletCount = BulletMaxCount;

	// == TODO: UI Text set
	if (MyAmmoWidget)
	{
		MyAmmoWidget->SetAmmoPercent(CurrentBulletCount, BulletMaxCount);
	}

	// == TODO: Reload Cool time down
	if (!ReloadCoolTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(ReloadCoolTimerHandle, this, &ThisClass::ReloadCoolDownTimerFunc, 0.1f, true);
	}

}

void UMainRangeComponent::PlayReloadAnim()
{
	if (!CanReload()) return;
	if (OwnerAnimInstance && OwnerAnimInstance->IsAnyMontagePlaying()) return;

	//OwnerCharacter->PlayAnimMontage(OwnerCharacter->GetAnimMontage(FireAnimMontageKey));
	{ // == Play Montage
		UAnimMontage* PlayMontage = OwnerCharacter->GetAnimMontage(AnimMontageKey);
		FName StartingSection = FName(*(FString("Reload")));
		float PlayRate = PlayMontage->GetSectionLength(1) / ReloadSpeedTime;

		{	// Montage Sync
			OwnerCharacter->SendAnimMontageStatus(AnimMontageKey, PlayMontage->GetSectionIndex(StartingSection));
		}

		UPlayMontageCallbackProxy* PlayMontageCallbackProxy = UPlayMontageCallbackProxy::CreateProxyObjectForPlayMontage(OwnerCharacter->GetMesh(), PlayMontage, PlayRate, 0, StartingSection);
	}

	{
		if(WeaponReloadAnim)
		{
			WeaponMeshComponent->PlayAnimation(WeaponReloadAnim, false);
		}
	}

	if (USkyscraperEngineSubsystem* Subsystem = GEngine->GetEngineSubsystem<USkyscraperEngineSubsystem>())
	{
		// 부스트 시작 소리 실행
		if (USoundBase* Sound = Subsystem->GetSkyscraperSound(ReloadSoundName)) {
			if (USoundAttenuation* SoundAttenuation = Subsystem->GetSkyscraperSoundAttenuation())
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, WeaponMeshComponent->GetComponentLocation(), FRotator{}, 1, 1, 0, SoundAttenuation);
			}
		}
	}

}

void UMainRangeComponent::Recoil()
{
	FRotator InitRot = GetOwnerPlayerController()->GetControlRotation();
	InitRot.Pitch += RecoilAboveAmount;
	InitRot.Yaw += UKismetMathLibrary::RandomFloatInRange(RecoilBesideAmount / 1.5, RecoilBesideAmount)
					* UKismetMathLibrary::RandomBool();
	RecoilTime = 0.1;

	// == TODO Recoil Timer Event
}

void UMainRangeComponent::FireCoolDownTimerFunc()
{
	CurrentFireCoolTime = UKismetMathLibrary::FMax(CurrentFireCoolTime - 0.1f, 0.0f);
	
	if(CurrentFireCoolTime <= 0.0f)
	{
		GetWorld()->GetTimerManager().ClearTimer(FireCoolTimerHandle);
	}
}

void UMainRangeComponent::ReloadCoolDownTimerFunc()
{
	CurrentReloadCoolTime = UKismetMathLibrary::FMax(CurrentReloadCoolTime - 0.1f, 0.0f);

	if (CurrentReloadCoolTime <= 0.0f)
	{
		GetWorld()->GetTimerManager().ClearTimer(ReloadCoolTimerHandle);
	}
}

// Called every frame
void UMainRangeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

void UMainRangeComponent::ActivateBulletInfinity(float BulletInfinityTime)
{
	bIsBulletInfinity = true;

	// 현재 탄이 없을 경우 1개를 추가하여 바로 무한 모드를 적용시킬 수 있게 한다.
	if (CurrentBulletCount == 0) 
	{
		CurrentBulletCount += 1;
	}

	if (!BulletInfinityTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(BulletInfinityTimerHandle, this, &ThisClass::DeactivateBulletInfinity, 0.2f, false, BulletInfinityTime);
	}
	else      // 타이머가 기존에 실행 중이었다면 (무적 모드 중이었다면, 시간 초기화)
	{
		GetWorld()->GetTimerManager().ClearTimer(BulletInfinityTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(BulletInfinityTimerHandle, this, &ThisClass::DeactivateBulletInfinity, 0.2f, false, BulletInfinityTime);
	}
}

void UMainRangeComponent::DeactivateBulletInfinity()
{
	GetWorld()->GetTimerManager().ClearTimer(BulletInfinityTimerHandle);
	bIsBulletInfinity = false;
}

