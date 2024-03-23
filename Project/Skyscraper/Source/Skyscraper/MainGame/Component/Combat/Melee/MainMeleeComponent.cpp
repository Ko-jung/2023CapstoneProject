// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMeleeComponent.h"

#include "MotionWarpingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Skyscraper/SkyscraperCharacter.h"

// Sets default values for this component's properties
UMainMeleeComponent::UMainMeleeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	AnimationMovementDistance = 100.0f;
	CanAttack = true;
	// ...
}


// Called when the game starts
void UMainMeleeComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ASkyscraperCharacter>(GetOwner());

	OwnerAnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();
	OwnerAnimInstance->OnMontageBlendingOut.AddDynamic(this, &ThisClass::OnBlendOutMeleeAttack);
	// ...
	
}

void UMainMeleeComponent::PlayAttackAnimMontage()
{
	CanAttack = false;

	int AnimationMovementAxis = 1;

	{ // == Set Animation movement axis by key input
		if (GetOwnerPlayerController()->IsInputKeyDown(EKeys::W))
		{
			AnimationMovementAxis += 1;
		}
		else if (GetOwnerPlayerController()->IsInputKeyDown(EKeys::S))
		{
			AnimationMovementAxis -= 1;
		}
	}

	{ // == set motion warping location
		const FVector ArrivePos = OwnerCharacter->GetActorLocation() +
			OwnerCharacter->GetActorForwardVector() * AnimationMovementAxis * AnimationMovementDistance;
		//== TODO: Delete later Debug
		UKismetSystemLibrary::DrawDebugLine(GetWorld(), OwnerCharacter->GetActorLocation(), ArrivePos, FLinearColor::Black, 3.0f, 10.0f);

		OwnerCharacter->GetMotionWarpingComponent()->AddOrUpdateWarpTargetFromLocation(TEXT("MeleeMovement"), ArrivePos);
	}
		
	{ // == Play Montage
		UAnimMontage** PlayMontage = MeleeComboAnimMontage.Find(MeleeComboCount);
		UE_LOG(LogTemp, Warning, TEXT("콤보: %d"), MeleeComboCount);
		float AttackAnimPlayRate = (*PlayMontage)->GetPlayLength() / AttackTime[MeleeComboCount];

		OwnerAnimInstance->Montage_Play(*PlayMontage, AttackAnimPlayRate);
	}

	{ // == Add MeleeComboCount 
		MeleeComboCount = (MeleeComboCount + 1) % MeleeComboAnimMontage.Num();
		UE_LOG(LogTemp, Warning, TEXT("콤보후: %d"), MeleeComboCount);
	}
}

void UMainMeleeComponent::OnBlendOutMeleeAttack(UAnimMontage* Montage, bool bInterrupted)
{
	CanAttack = true;
	LastAttackClickTime = UGameplayStatics::GetTimeSeconds(GetWorld());
}

void UMainMeleeComponent::Attack()
{
	if(CanAttack)
	{
		// == if attack in 0.5s after last attack, play combo attack // else play 0 attack
		if (!(UGameplayStatics::GetTimeSeconds(GetWorld()) - LastAttackClickTime < 0.5f))
		{
			UE_LOG(LogTemp, Warning, TEXT("이거가 문제같은데 %f"), UGameplayStatics::GetTimeSeconds(GetWorld()) - LastAttackClickTime);
			MeleeComboCount = 0;
		}
		PlayAttackAnimMontage();
	}
}


void UMainMeleeComponent::CreateAttackArea(FVector vHitSize, float fStiffnessTime, float fBaseDamage, bool bDoDown)
{
	FVector Start = OwnerCharacter->GetActorLocation();
	// == if set attack range, fix this line to variable
	FVector End = Start + OwnerCharacter->GetActorForwardVector() * 150;

	TArray<AActor*> IgnoreActors;
	TArray<FHitResult> OutHits;

	// == TODO: Delete Debug Later
	UKismetSystemLibrary::BoxTraceMulti(GetWorld(), Start, End, vHitSize, OwnerCharacter->GetActorRotation(), ETraceTypeQuery::TraceTypeQuery1, false, IgnoreActors,EDrawDebugTrace::ForDuration,OutHits,true);

	for(FHitResult HitResult : OutHits)
	{
		AActor* HitActor = HitResult.GetActor();
		// == TODO: Stiffness And Down Later
		//HitResult.GetActor()

		// == "This function will only execute on the server" <<= now, just client level
		UGameplayStatics::ApplyDamage(HitActor, fBaseDamage, nullptr, nullptr, nullptr);
	}

}

// Called every frame
void UMainMeleeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

