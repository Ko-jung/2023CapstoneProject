// Fill out your copyright notice in the Description page of Project Settings.


#include "MainRangeComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Skyscraper/SkyscraperCharacter.h"

// Sets default values for this component's properties
UMainRangeComponent::UMainRangeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	OwnerCharacter = nullptr;
	CurrentFireCoolTime = -1.0f;
	FireMaxCoolTime = 0.5f;
	CurrentReloadCoolTime = -1.0f;
	ReloadMaxCoolTime = 5.0f;
	BulletMaxCount = 20;
	CurrentBulletCount = BulletMaxCount;
	RecoilAboveAmount = 1.0f;
	RecoilBesideAmount = 1.0f;
	RecoilTime = 0.1f;
	RecoilSpeed = 10.0f;
	OwnerAnimInstance = nullptr;
	const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_FireRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Rifle/AM_FireRifle.AM_FireRifle'"));
	AM_Fire = AM_FireRef.Object;
	const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_ReloadRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Rifle/AM_ReloadRifle.AM_ReloadRifle'"));
	AM_Reload = AM_ReloadRef.Object;
	
}


// Called when the game starts
void UMainRangeComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ASkyscraperCharacter>(GetOwner());
	OwnerAnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();

	CurrentBulletCount = BulletMaxCount;
	// == TODO: UI BulletCount set


	// ...
	
}


void UMainRangeComponent::PlayFireAnim()
{
	if (!CanFire()) return;
	
	UseBullet();
	CurrentFireCoolTime = FireMaxCoolTime;

	OwnerCharacter->PlayAnimMontage(AM_Fire);

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
		
		bool HitResult = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_Visibility);
			//UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End, ETraceTypeQuery::TraceTypeQuery1,false, IgnoreActors, EDrawDebugTrace::ForDuration, OutHit, true);
		if (HitResult)
		{
			AActor* HitActor = OutHit.GetActor();
			UGameplayStatics::ApplyDamage(HitActor, fBaseDamage, nullptr, nullptr, nullptr);
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

void UMainRangeComponent::PlayReloadAnim(float fReloadingTime)
{
	if (!CanReload()) return;

	float PlayRate = AM_Reload->GetPlayLength() / fReloadingTime;
	OwnerCharacter->PlayAnimMontage(AM_Reload, PlayRate);


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

