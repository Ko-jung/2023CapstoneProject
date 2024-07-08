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
#include "Skyscraper/MainGame/Component/Health/HealthComponent.h"
#include "Skyscraper/MainGame/Widget/Ammo/MyAmmoWidget.h"

#include "Skyscraper/Network/MainGameMode.h"

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

	
	{
		static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_MuzzleFlashRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/2019180031/MainGame/Fbx/MuzzleFlash/NS_MuzzleFlash.NS_MuzzleFlash'"));
		NS_MuzzleFlash = NS_MuzzleFlashRef.Object;
	}
	
}


// Called when the game starts
void UMainRangeComponent::BeginPlay()
{
	Super::BeginPlay();

	// 소유자 정보 로드
	OwnerCharacter = Cast<ASkyscraperCharacter>(GetOwner());
	OwnerAnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();

	// 소유자에게 무기 부착
	FAttachmentTransformRules AttachmentTransformRules{EAttachmentRule::SnapToTarget,false};
	WeaponMeshComponent->AttachToComponent(OwnerCharacter->GetMesh(), AttachmentTransformRules, WeaponSocketName);
	WeaponMeshComponent->SetHiddenInGame(true);

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

			if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
			{
				EnhancedInputComponent->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &ThisClass::PlayFireAnim);
				EnhancedInputComponent->BindAction(IA_Reload, ETriggerEvent::Started, this, &ThisClass::PlayReloadAnim);
			}
		}
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
	WeaponMeshComponent->SetHiddenInGame(bNewHidden);
}


void UMainRangeComponent::AddThisWeapon()
{
	AddInputMappingContext();
	SetWeaponHiddenInGame(false);
	if (MainRangeWidget) MainRangeWidget->AddToViewport();
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
	
}

void UMainRangeComponent::UseBullet()
{
	if(bIsBulletInfinity)
	{
		UE_LOG(LogTemp, Warning, TEXT("Bullet Infinity Time"));
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

	if (!GetOwnerPlayerController()) 
	{
		EnemyFire(fBaseDamage);
		return;
	};

	{ // == Line Trace
		FVector Start = OwnerCharacter->GetCameraBoom()->GetComponentLocation();
		FVector End = Start +
			GetOwnerPlayerController()->GetControlRotation().Vector() * EffectiveDistance;
		TArray<AActor*> IgnoreActors;

		FHitResult OutHit;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(OwnerCharacter);

		// DebugDrawTraceTag is not used in shipping and test builds
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
		GetWorld()->DebugDrawTraceTag = TEXT("DebugTraceTag");
#endif

		QueryParams.TraceTag = TEXT("DebugTraceTag");
		bool HitResult = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_Pawn, QueryParams);
		if (HitResult)
		{
			AActor* HitActor = OutHit.GetActor();

			// Execute on Sever
			AMainGameMode* GameMode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(this));
			if (GameMode)
			{
				GameMode->SendTakeDamage(OwnerCharacter, HitActor);
			}
			//UGameplayStatics::ApplyDamage(HitActor, fBaseDamage, nullptr, nullptr, nullptr);


			if (OutHit.GetActor()->FindComponentByClass(UHealthComponent::StaticClass()))
			{
				{ // 대미지 소환 액터 소환
					FTransform SpawnTransform;
					SpawnTransform.SetLocation(OutHit.Location);
					FRotator rotator = (OutHit.TraceEnd - OutHit.TraceStart).ToOrientationRotator();
					rotator.Pitch += 180.0f;
					SpawnTransform.SetRotation(rotator.Quaternion());
					ADamageSpawner* DamageSpawner = GetWorld()->SpawnActorDeferred<ADamageSpawner>(ADamageSpawner::StaticClass(), SpawnTransform);
					if (DamageSpawner)
					{
						DamageSpawner->SetActorLocation(OutHit.Location);
						DamageSpawner->Initialize(fBaseDamage, 0.6f);
						DamageSpawner->FinishSpawning(SpawnTransform);
					}
				}
			}
		}

		// Muzzle Flash Effect
		if (NS_MuzzleFlash)
		{
			//FVector FireLocation = WeaponMeshComponent->GetSocketLocation(TEXT("FireSocket"));
			//
			//UNiagaraComponent* FX = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NS_MuzzleFlash,, GetActorRotation(), GetActorScale() * 5);


		}
	}

	// == Recoil

	// == TODO: if have blood component, spawn blood

}

void UMainRangeComponent::EnemyFire(float fBaseDamage)
{
	// == Fore enemy fire (doesn't have player controller actor)
	{// == Line trace
		FVector Start = OwnerCharacter->GetActorLocation();
		FVector End = Start +
						OwnerCharacter->GetActorForwardVector() * 10000.0f;
		TArray<AActor*> IgnoreActors;
		FHitResult OutHit;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(OwnerCharacter);

		// DebugDrawTraceTag is not used in shipping and test builds
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
		GetWorld()->DebugDrawTraceTag = TEXT("DebugTraceTag");
#endif

		QueryParams.TraceTag = TEXT("DebugTraceTag");
		
		bool HitResult = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_Pawn,QueryParams);
		

		if (HitResult)
		{
			AActor* HitActor = OutHit.GetActor();
			UGameplayStatics::ApplyDamage(HitActor, fBaseDamage, nullptr, OwnerCharacter, nullptr);
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

	UE_LOG(LogTemp, Warning, TEXT("%d %d"), CurrentBulletCount, BulletMaxCount);
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

	UE_LOG(LogTemp, Warning, TEXT("Bullet Infinity Activate"));

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
	UE_LOG(LogTemp, Warning, TEXT("Bullet Infinity Deactivate"));
}

