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
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
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
	if (!GetOwnerPlayerController()) return;

	{ // == Line Trace
		FVector Start = OwnerCharacter->GetCameraBoom()->GetComponentLocation();
		FVector End = Start +
			GetOwnerPlayerController()->GetControlRotation().Vector() * 10000.0f;
		TArray<AActor*> IgnoreActors;
		FHitResult OutHit;
		static bool HitResult = UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End, ETraceTypeQuery::TraceTypeQuery1,
			false, IgnoreActors, EDrawDebugTrace::ForDuration, OutHit, true);
		if (HitResult)
		{
			AActor* HitActor = OutHit.GetActor();
			UGameplayStatics::ApplyDamage(HitActor, fBaseDamage, nullptr, nullptr, nullptr);
		}
	}

	// == Recoil

	// == TODO: if have blood component, spawn blood

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

	// ...
}

