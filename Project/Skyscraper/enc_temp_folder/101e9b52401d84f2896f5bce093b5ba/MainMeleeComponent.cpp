// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMeleeComponent.h"

#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"

#include "MotionWarpingComponent.h"
#include "PlayMontageCallbackProxy.h"
#include "PlayMontageCallbackProxy.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "Skyscraper/MainGame/Actor/Damage/DamageSpawner.h"
#include "Skyscraper/MainGame/Component/Health/HealthComponent.h"

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
	//OwnerAnimInstance->OnMontageBlendingOut.AddDynamic(this, &ThisClass::OnBlendOutMeleeAttack);

	// == TODO: Create Melee Widget
}


void UMainMeleeComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	//UnBind Input Mapping Context
	RemoveThisWeapon();

	// == TOOD: Unbind Melee Widget
}

void UMainMeleeComponent::AddInputMappingContext()
{
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
}

void UMainMeleeComponent::RemoveInputMappingContext()
{
	if (APlayerController* PlayerController = GetOwnerPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(IMC_MeleeInput);
		}
	}
}

void UMainMeleeComponent::AddThisWeapon()
{
	AddInputMappingContext();
}

void UMainMeleeComponent::RemoveThisWeapon()
{
	RemoveInputMappingContext();
}

void UMainMeleeComponent::PlayAttackAnimMontage()
{
	CanAttack = false;

	int AnimationMovementAxis = 1;

	{ // == Set Animation movement axis by key input
		// For EnemyCharacter
		if(!GetOwnerPlayerController())	
		{
			AnimationMovementAxis = 0;
		}

		// For Player
		if (GetOwnerPlayerController() && GetOwnerPlayerController()->IsInputKeyDown(EKeys::W))
		{
			AnimationMovementAxis += 1;
		}
		if (GetOwnerPlayerController() && GetOwnerPlayerController()->IsInputKeyDown(EKeys::S))
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
		UAnimMontage* PlayMontage = OwnerCharacter->GetAnimMontage(AnimMontageKey);
			//MeleeComboAnimMontage.Find(MeleeComboCount);
		UE_LOG(LogTemp, Warning, TEXT("콤보: %d"), MeleeComboCount);
		
		float AttackAnimPlayRate = PlayMontage->GetPlayLength() / AttackTime[MeleeComboCount];
		FName StartPosition = FName(TEXT("Attack%d"), MeleeComboCount + 1);
		UPlayMontageCallbackProxy* PlayMontageCallbackProxy = UPlayMontageCallbackProxy::CreateProxyObjectForPlayMontage(OwnerCharacter->GetMesh(), PlayMontage);
		PlayMontageCallbackProxy->OnBlendOut.AddDynamic(this, &ThisClass::OnBlendOutMeleeAttack);
		//UPlayMontageCallbackProxy::PlayMontage(OwnerCharacter->GetMesh(), PlayMontage, AttackAnimPlayRate, 0, StartPosition);
		//OwnerAnimInstance->Montage_Play(PlayMontage, AttackAnimPlayRate);
	}

	{ // == Add MeleeComboCount 
		//MeleeComboCount = (MeleeComboCount + 1) % MeleeComboAnimMontage.Num();
		MeleeComboCount = (MeleeComboCount + 1) % AttackTime.Num();
	}

	
}

void UMainMeleeComponent::OnBlendOutMeleeAttack(FName Notify_Name)
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
	fBaseDamage *= OwnerCharacter->GetPowerBuffValue();
	FVector Start = OwnerCharacter->GetActorLocation();
	// == if set attack range, fix this line to variable
	FVector End = Start + OwnerCharacter->GetActorForwardVector() * 150;

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(OwnerCharacter);
	TArray<FHitResult> OutHits;

	// == TODO: Delete Debug Later
	UKismetSystemLibrary::BoxTraceMulti(GetWorld(), Start, End, vHitSize, OwnerCharacter->GetActorRotation(), UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Pawn), false, IgnoreActors,EDrawDebugTrace::ForDuration,OutHits,true);

	// 적중된 적이 있으므로 역경직
	if(OutHits.Num() != 0)
	{
		DoHitLag();
	}

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
				Cast<ASkyscraperCharacter>(HitActor)->DoStiffness(fStiffnessTime, OwnerCharacter->GetActorForwardVector());
			}
			
		}
		
		// == "This function will only execute on the server" <<= now, just client level
		UGameplayStatics::ApplyDamage(HitActor, fBaseDamage, nullptr, nullptr, nullptr);

		if(HitResult.GetActor()->FindComponentByClass(UHealthComponent::StaticClass()))
		{
			{ // 대미지 소환 액터 소환
				FTransform SpawnTransform;
				SpawnTransform.SetLocation(HitResult.Location);
				FRotator rotator = (HitResult.TraceEnd - HitResult.TraceStart).ToOrientationRotator();
				rotator.Pitch += 180.0f;
				SpawnTransform.SetRotation(rotator.Quaternion());
				ADamageSpawner* DamageSpawner = GetWorld()->SpawnActorDeferred<ADamageSpawner>(ADamageSpawner::StaticClass(), SpawnTransform);
				if (DamageSpawner)
				{
					DamageSpawner->SetActorLocation(HitResult.Location);
					DamageSpawner->Initialize(fBaseDamage, 0.6f);
					DamageSpawner->FinishSpawning(SpawnTransform);
				}
			}
		}
		
	}

}

void UMainMeleeComponent::DoHitLag()
{
	if(OwnerAnimInstance->IsAnyMontagePlaying())
	{
		// 몽타쥬 멈추고
		OwnerAnimInstance->Montage_Pause();

		float HitLagDuration = 1.0f;
		// 타이머 설정
		if(!HitLagTimerHandle.IsValid())
		{
			GetWorld()->GetTimerManager().SetTimer(HitLagTimerHandle, this, &ThisClass::StopHitLag, 1.0f, false, HitLagDuration);
		}
		else
		{
			GetWorld()->GetTimerManager().ClearTimer(HitLagTimerHandle);
			GetWorld()->GetTimerManager().SetTimer(HitLagTimerHandle, this, &ThisClass::StopHitLag, 1.0f, false, HitLagDuration);
		}
		
	}


}

void UMainMeleeComponent::StopHitLag()
{
	GetWorld()->GetTimerManager().ClearTimer(HitLagTimerHandle);
	OwnerAnimInstance->Montage_Resume(nullptr);
}

// Called every frame
void UMainMeleeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

