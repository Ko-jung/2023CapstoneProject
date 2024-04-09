// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMeleeComponent.h"

#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"

#include "MotionWarpingComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"

// Sets default values for this component's properties
UMainMeleeComponent::UMainMeleeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	MeleeComboCount = 0;
	LastAttackClickTime = 0;
	OwnerAnimInstance = nullptr;
	OwnerCharacter = nullptr;
	AnimationMovementDistance = 100.0f;
	CanAttack = true;

	{ // == Set Input Asset
		static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_MeleeInputRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/2019180031/MainGame/Core/Input/Combat/Melee/IMC_MainMeleeInput.IMC_MainMeleeInput'"));
		IMC_MeleeInput = IMC_MeleeInputRef.Object;

		static ConstructorHelpers::FObjectFinder<UInputAction> IA_AttackRef(TEXT("/Script/EnhancedInput.InputAction'/Game/2019180031/MainGame/Core/Input/Combat/Melee/IA_Attack.IA_Attack'"));
		IA_Attack = IA_AttackRef.Object;
	}
}


// Called when the game starts
void UMainMeleeComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ASkyscraperCharacter>(GetOwner());

	OwnerAnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();
	OwnerAnimInstance->OnMontageBlendingOut.AddDynamic(this, &ThisClass::OnBlendOutMeleeAttack);

	//Add Input Mapping Context
	if (APlayerController* PlayerController = GetOwnerPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC_MeleeInput, 0);

			if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
			{
				EnhancedInputComponent->BindAction(IA_Attack, ETriggerEvent::Started, this, &ThisClass::Attack);
			}
		}
	}

	// == TODO: Create Melee Widget
}

void UMainMeleeComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	//UnBind Input Mapping Context
	if (APlayerController* PlayerController = GetOwnerPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(IMC_MeleeInput);
		}
	}

	// == TOOD: Unbind Melee Widget
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
		//UAnimMontage** PlayMontage = MeleeComboAnimMontage.Find(MeleeComboCount);
		UAnimMontage* PlayMontage = OwnerCharacter->GetAnimMontage(AnimMontageKeys[MeleeComboCount]);
			//MeleeComboAnimMontage.Find(MeleeComboCount);
		UE_LOG(LogTemp, Warning, TEXT("콤보: %d"), MeleeComboCount);
		float AttackAnimPlayRate = PlayMontage->GetPlayLength() / AttackTime[MeleeComboCount];

		OwnerAnimInstance->Montage_Play(PlayMontage, AttackAnimPlayRate);
	}

	{ // == Add MeleeComboCount 
		//MeleeComboCount = (MeleeComboCount + 1) % MeleeComboAnimMontage.Num();
		MeleeComboCount = (MeleeComboCount + 1) % AnimMontageKeys.Num();
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
	IgnoreActors.Add(OwnerCharacter);
	TArray<FHitResult> OutHits;

	// == TODO: Delete Debug Later
	UKismetSystemLibrary::BoxTraceMulti(GetWorld(), Start, End, vHitSize, OwnerCharacter->GetActorRotation(), UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Pawn), false, IgnoreActors,EDrawDebugTrace::ForDuration,OutHits,true);

	for(FHitResult HitResult : OutHits)
	{
		AActor* HitActor = HitResult.GetActor();
		// == TODO: Stiffness And Down Later
		if(bDoDown)
		{
			if(ASkyscraperCharacter* TargetCharacter = Cast<ASkyscraperCharacter>(HitActor))
			{
				TargetCharacter->DoDown(OwnerCharacter->GetActorForwardVector());
			}
			
		}else
		{
			if (ASkyscraperCharacter* TargetCharacter = Cast<ASkyscraperCharacter>(HitActor))
			{
				Cast<ASkyscraperCharacter>(HitActor)->DoStiffness(fStiffnessTime);
			}
			
		}
		
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

