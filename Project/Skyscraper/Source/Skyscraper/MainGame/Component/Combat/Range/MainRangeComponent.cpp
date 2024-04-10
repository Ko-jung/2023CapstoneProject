// Fill out your copyright notice in the Description page of Project Settings.


#include "MainRangeComponent.h"

#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "Skyscraper/MainGame/Actor/Damage/DamageSpawner.h"
#include "Skyscraper/MainGame/Component/Health/HealthComponent.h"

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
	FireAnimMontageKey = ECharacterAnimMontage::ECAM_Default;
	ReloadAnimMontageKey = ECharacterAnimMontage::ECAM_Default;



	{ // == Set Input Asset
		static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_RangeInputRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/2019180031/MainGame/Core/Input/Combat/Range/IMC_RangeInput.IMC_RangeInput'"));
		IMC_RangeInput = IMC_RangeInputRef.Object;

		static ConstructorHelpers::FObjectFinder<UInputAction> IA_FireRef(TEXT("/Script/EnhancedInput.InputAction'/Game/2019180031/MainGame/Core/Input/Combat/Range/IA_Fire.IA_Fire'"));
		IA_Fire = IA_FireRef.Object;

		static ConstructorHelpers::FObjectFinder<UInputAction> IA_ReloadRef(TEXT("/Script/EnhancedInput.InputAction'/Game/2019180031/MainGame/Core/Input/Combat/Range/IA_Reload.IA_Reload'"));
		IA_Reload = IA_ReloadRef.Object;
	}
}


// Called when the game starts
void UMainRangeComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ASkyscraperCharacter>(GetOwner());
	OwnerAnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();

	CurrentBulletCount = BulletMaxCount;
	// == TODO: UI BulletCount set



	//Add Input Mapping Context
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

	// == TODO: Create Melee Widget
	
}

void UMainRangeComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	//Unbind Input Mapping Context
	if (APlayerController* PlayerController = GetOwnerPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(IMC_RangeInput);
			
		}
	}
}


void UMainRangeComponent::PlayFireAnim()
{
	if (!CanFire()) return;
	UE_LOG(LogTemp, Warning, TEXT("총 발사"));
	UseBullet();
	CurrentFireCoolTime = FireMaxCoolTime;

	OwnerCharacter->PlayAnimMontage(OwnerCharacter->GetAnimMontage(FireAnimMontageKey));

	if(!FireCoolTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(FireCoolTimerHandle, this, &ThisClass::FireCoolDownTimerFunc, 0.1f, true);		
	}
	
}

void UMainRangeComponent::UseBullet()
{
	CurrentBulletCount -= 1;

	// == TODO: Set UI BulletCount text
}

void UMainRangeComponent::Fire(float fBaseDamage)
{
	if (!GetOwnerPlayerController()) 
	{
		EnemyFire(fBaseDamage);
		return;
	};

	{ // == Line Trace
		FVector Start = OwnerCharacter->GetCameraBoom()->GetComponentLocation();
		FVector End = Start +
			GetOwnerPlayerController()->GetControlRotation().Vector() * 10000.0f;
		TArray<AActor*> IgnoreActors;

		FHitResult OutHit;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(OwnerCharacter);
		GetWorld()->DebugDrawTraceTag = TEXT("DebugTraceTag");
		QueryParams.TraceTag = TEXT("DebugTraceTag");
		bool HitResult = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_Pawn, QueryParams);
		if (HitResult)
		{
			AActor* HitActor = OutHit.GetActor();
			UGameplayStatics::ApplyDamage(HitActor, fBaseDamage, nullptr, nullptr, nullptr);
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
		GetWorld()->DebugDrawTraceTag = TEXT("DebugTraceTag");
		QueryParams.TraceTag = TEXT("DebugTraceTag");
		
		bool HitResult = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_Pawn,QueryParams);
		

		if (HitResult)
		{
			AActor* HitActor = OutHit.GetActor();
			UGameplayStatics::ApplyDamage(HitActor, fBaseDamage, nullptr, nullptr, nullptr);
		}
	}
}

void UMainRangeComponent::BulletReloading()
{
	CurrentReloadCoolTime = ReloadMaxCoolTime;

	CurrentBulletCount = BulletMaxCount;

	// == TODO: UI Text set

	// == TODO: Reload Cool time down
	if (!ReloadCoolTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(ReloadCoolTimerHandle, this, &ThisClass::ReloadCoolDownTimerFunc, 0.1f, true);
	}

}

void UMainRangeComponent::PlayReloadAnim()
{
	if (!CanReload()) return;

	float PlayRate = OwnerCharacter->GetAnimMontage(ReloadAnimMontageKey)->GetPlayLength() / ReloadSpeedTime;
	OwnerCharacter->PlayAnimMontage(OwnerCharacter->GetAnimMontage(ReloadAnimMontageKey), PlayRate);


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

