// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMeleeComponent.h"

#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"

#include "MotionWarpingComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PlayMontageCallbackProxy.h"
#include "PlayMontageCallbackProxy.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "Skyscraper/MainGame/Actor/Damage/DamageSpawner.h"
#include "Skyscraper/MainGame/Component/Health/HealthComponent.h"
#include "Skyscraper/MainGame/Core/SkyscraperPlayerController.h"
#include "Skyscraper/Network/MainGameMode.h"

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
	bCanAttack = true;
	AttackCoolDownTime = 2.0f;

	// Set Input Asset
	{ 
		static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_MeleeInputRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/2019180031/MainGame/Core/Input/Combat/Melee/IMC_MainMeleeInput.IMC_MainMeleeInput'"));
		IMC_MeleeInput = IMC_MeleeInputRef.Object;

		static ConstructorHelpers::FObjectFinder<UInputAction> IA_AttackRef(TEXT("/Script/EnhancedInput.InputAction'/Game/2019180031/MainGame/Core/Input/Combat/Melee/IA_Attack.IA_Attack'"));
		IA_Attack = IA_AttackRef.Object;
	}

	// Hit Effect
	{
		static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_HitEffectRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/2019180031/MainGame/Fbx/HitEffect/NS_HitEffect.NS_HitEffect'"));
		if(NS_HitEffectRef.Succeeded())
		{
			NS_HitEffect = NS_HitEffectRef.Object;
		}
	}
}

// Called when the game starts
void UMainMeleeComponent::BeginPlay()
{
	Super::BeginPlay();

	bCanAttack = true;

	{ // 소유 캐릭터 정보 흭득
		OwnerCharacter = Cast<ASkyscraperCharacter>(GetOwner());
		OwnerAnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();
	}

	{ // 소유 캐릭터에게 무기 부착
		FAttachmentTransformRules AttachmentTransformRules{ EAttachmentRule::SnapToTarget,false };
		WeaponMeshComponent->AttachToComponent(OwnerCharacter->GetMesh(), AttachmentTransformRules, WeaponSocketName);
		WeaponMeshComponent->SetHiddenInGame(true);
	}
	// == TODO: Create Melee Widget

	SetInitialValue();
}


void UMainMeleeComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	//UnBind Input Mapping Context
	RemoveThisWeapon();

	// == TOOD: Unbind Melee Widget
}

void UMainMeleeComponent::AttackCoolTimeFunc()
{
	UE_LOG(LogTemp, Warning, TEXT("근접 쿨타임 종료"));
	bCanAttack = true;

	GetWorld()->GetTimerManager().ClearTimer(AttackCoolTimeTimerHandle);
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
	SetWeaponHiddenInGame(false);
}

void UMainMeleeComponent::RemoveThisWeapon()
{
	RemoveInputMappingContext();
	SetWeaponHiddenInGame(true);
}

void UMainMeleeComponent::PlayAttackAnimMontage()
{
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
		//OwnerCharacter->GetMotionWarpingComponent()->AddOrUpdateWarpTargetFromLocationAndRotation(TEXT("MeleeMovement"), ArrivePos,OwnerCharacter->GetActorRotation());

		OwnerCharacter->DisableInput(OwnerCharacter->GetPlayerController());
	}

	// == Play Montage
	{ 
		UAnimMontage* PlayMontage = OwnerCharacter->GetAnimMontage(AnimMontageKey);

		float AttackAnimPlayRate = PlayMontage->GetSectionLength(MeleeComboCount) / AttackTime[MeleeComboCount];
		FName StartingSection = FName(*(FString("Attack") + FString::FromInt(MeleeComboCount+1)));

		// 해당 몽타쥬의 Blend Out 시간 설정
		if(AttackBlendOutTime.Num())
		{
			PlayMontage->BlendOut.SetBlendTime(AttackBlendOutTime[MeleeComboCount]);
			UE_LOG(LogTemp, Warning, TEXT("attack - %d // %f"), MeleeComboCount, PlayMontage->BlendOut.GetBlendTime());
		}

		{	// Montage Sync
			OwnerCharacter->SendAnimMontageStatus(AnimMontageKey, PlayMontage->GetSectionIndex(StartingSection));
		}

		UPlayMontageCallbackProxy* PlayMontageCallbackProxy = UPlayMontageCallbackProxy::CreateProxyObjectForPlayMontage(OwnerCharacter->GetMesh(), PlayMontage,AttackAnimPlayRate,0,StartingSection);
		PlayMontageCallbackProxy->OnBlendOut.AddDynamic(this, &ThisClass::OnBlendOutMeleeAttack);
		OwnerCharacter->GetCharacterMovement()->GravityScale = 0.0f;
		OwnerCharacter->GetCharacterMovement()->Velocity.Z = 0.0f;
		
	}

	// == Add MeleeComboCount
	{ 
		//최대 콤보 공격 시 쿨타임 설정
		if(MeleeComboCount == AttackTime.Num()-1)
		{
			bCanAttack = false;
			if(!AttackCoolTimeTimerHandle.IsValid())
			{
				UE_LOG(LogTemp, Warning, TEXT("근접 마지막 타격, 쿨타임 시작"));
				GetWorld()->GetTimerManager().SetTimer(AttackCoolTimeTimerHandle, this, &ThisClass::AttackCoolTimeFunc, 0.1f, false,AttackCoolDownTime);
			}
		}
		MeleeComboCount = (MeleeComboCount + 1) % AttackTime.Num();
	}

	
}

void UMainMeleeComponent::OnBlendOutMeleeAttack(FName Notify_Name)
{
	OwnerCharacter->EnableInput(OwnerCharacter->GetPlayerController());

	{// 이동 없이 공격 마무리 모션 사용 시 무기 집어넣는 애니메이션 재생을 진행하는데, 해당 애니메이션을 움직일 경우엔 막는 코드
		if (GetOwnerPlayerController())
		{
			// 이동을 하려 한다면,
			if (GetOwnerPlayerController()->IsInputKeyDown(EKeys::W) ||
				GetOwnerPlayerController()->IsInputKeyDown(EKeys::A) ||
				GetOwnerPlayerController()->IsInputKeyDown(EKeys::S) ||
				GetOwnerPlayerController()->IsInputKeyDown(EKeys::D))
			{
				//OwnerAnimInstance->StopAllMontages(0.2f);
			}
			else
			{
				{ // == Play Montage
					UAnimMontage* PlayMontage = OwnerCharacter->GetAnimMontage(AnimMontageKey);
					// 해당 몽타쥬의 Blend Out 시간 설정
					PlayMontage->BlendOut.SetBlendTime(0.2f);
					
					{	// Montage Sync
						OwnerCharacter->SendAnimMontageStatus(AnimMontageKey, PlayMontage->GetSectionIndex("FinishAttack"));
					}

					UPlayMontageCallbackProxy* PlayMontageCallbackProxy = UPlayMontageCallbackProxy::CreateProxyObjectForPlayMontage(OwnerCharacter->GetMesh(), PlayMontage, 1.0f, 0, TEXT("FinishAttack"));
					//PlayMontageCallbackProxy->OnBlendOut.AddDynamic(this, &ThisClass::OnBlendOutMeleeAttack);
					OwnerCharacter->GetCharacterMovement()->GravityScale = 0.0f;
					OwnerCharacter->GetCharacterMovement()->Velocity.Z = 0.0f;

				}
			}

		}
	}
	

	// 선입력이 0.2초 내에 있었을 경우 바로 공격하도록
	if (UGameplayStatics::GetTimeSeconds(GetWorld()) - BufferedInput < 0.4f)
	{
		PlayAttackAnimMontage();
		return;
	}

	OwnerCharacter->GetCharacterMovement()->GravityScale = 0.5f;
	OwnerCharacter->GetCharacterMovement()->Velocity.Z = 0.0f;
	LastAttackClickTime = UGameplayStatics::GetTimeSeconds(GetWorld());

	
}


void UMainMeleeComponent::Attack()
{
	if (!bCanAttack) {
		UE_LOG(LogTemp, Warning, TEXT("근접 쿨타임 중"));
		return;
	}

	if(!OwnerAnimInstance->IsAnyMontagePlaying())
	{
		// == if attack in 0.5s after last attack, play combo attack // else play 0 attack
		if (!(UGameplayStatics::GetTimeSeconds(GetWorld()) - LastAttackClickTime < 0.5f))
		{
			MeleeComboCount = 0;
		}
		PlayAttackAnimMontage();
	}
	else
	{
		// 선입력에 대한 처리
		BufferedInput = UGameplayStatics::GetTimeSeconds(GetWorld());
	}
}

void UMainMeleeComponent::CreateAttackArea(float Width, float Height, float Distance, FVector StartOffset, float Angle,
	float fStunTime, float fBaseDamage, bool bDoDown)
{
	fBaseDamage *= OwnerCharacter->GetPowerBuffValue();

	FVector Start = OwnerCharacter->GetActorLocation()
						+ OwnerCharacter->GetActorRotation().RotateVector(StartOffset);

	// == if set attack range, fix this line to variable
	FRotator AngleToRotator = FRotator{ 0.0f,Angle,0.0f };
	FVector End = Start + AngleToRotator.RotateVector(OwnerCharacter->GetActorForwardVector() * Distance);

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(OwnerCharacter);
	TArray<FHitResult> OutHits;

	FVector vHitSize{ 1.0f,Width,Height };

	// == TODO: Delete Debug Later
	UKismetSystemLibrary::BoxTraceMulti(GetWorld(), Start, End, vHitSize, OwnerCharacter->GetActorRotation() + AngleToRotator, UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Pawn), false, IgnoreActors, EDrawDebugTrace::ForDuration, OutHits, true);

	// 노트
	// UKismetSystemLibrary::BoxTraceMulti 를 사용했으나 OutHits 에 유일하지 않은 데이터로 리턴 됨을 확인
	// Unique한 데이터로 만드는 과정에서 '==' action이 적절히 작동하지 않음을 확인
	// 따라서 OutHit.GetActor() 으로 분리하였고, 그러기 위해 배열을 통해 저장
	TArray<FHitResult> UniqueOutHits;
	TArray<AActor*> OutHitActor;
	for(FHitResult OutHitResult : OutHits)
	{
		if (OutHitResult.GetActor()->IsA<ASkyscraperCharacter>())
		{
			if (!OutHitActor.Contains(OutHitResult.GetActor()))
			{
				OutHitActor.Add(OutHitResult.GetActor());
				UniqueOutHits.Add(OutHitResult);
			}
				
		}
	}

	AMainGameMode* GameMode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(this));

	bool bDoHitLag = false;
	for (FHitResult HitResult : UniqueOutHits)
	{
		UPrimitiveComponent* PrimitiveComponent = HitResult.GetComponent();
		if (PrimitiveComponent->IsA(UStaticMeshComponent::StaticClass())
			&& PrimitiveComponent->GetName().StartsWith("Window_"))
		{
			//PrimitiveComponent->DestroyComponent();
			if(GameMode)
			 	GameMode->SendBreakObject(OwnerCharacter, PrimitiveComponent, EBreakType::Window);
			continue;
		}

		AActor* HitActor = HitResult.GetActor();
		if (!HitActor->IsA(ACharacter::StaticClass())) continue;

		bDoHitLag = true;

		ASkyscraperCharacter* TargetCharacter = Cast<ASkyscraperCharacter>(HitActor);

		if(TargetCharacter)
		{
			if (bDoDown)
			{
				TargetCharacter->DoDown(OwnerCharacter, OwnerCharacter->GetActorForwardVector());
			}
			else
			{
				TargetCharacter->DoStun(OwnerCharacter, fStunTime, OwnerCharacter->GetActorForwardVector());
			}

			// Find near bone to spawn system effect (Hit Effect & Blood Effect)
			{
				USkeletalMeshComponent* Mesh = TargetCharacter->GetMesh();
				FTransform MeshHitTransform = Mesh->GetBoneTransform(Mesh->FindClosestBone(HitResult.Location));

				if(NS_HitEffect)
				{
					UNiagaraFunctionLibrary::SpawnSystemAtLocation(
						GetWorld(), NS_HitEffect,
						MeshHitTransform.GetLocation(),
						FRotator{ 0.0f,0.0f,0.0f },
						FVector(1));
				}
				
			}

			if (HitResult.GetActor()->FindComponentByClass(UHealthComponent::StaticClass()))
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
		

		// Execute on Sever
		if (GameMode)
		{
			if (not GameMode->SendTakeDamage(OwnerCharacter, HitActor))
			{
				// == "This function will only execute on the server" <<= now, just client level
				UGameplayStatics::ApplyDamage(HitActor, fBaseDamage, nullptr, nullptr, nullptr);
			}
		}

		

	}

	// 적중된 적이 있으므로 역경직
	if (bDoHitLag)
	{
		DoHitLag();
	}
}



void UMainMeleeComponent::DoHitLag()
{
	if(OwnerAnimInstance->IsAnyMontagePlaying())
	{
		// 몽타쥬 멈추고
		OwnerAnimInstance->Montage_Pause();

		float HitLagDuration = 0.1f;
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

void UMainMeleeComponent::SetInitialValue()
{
}

// Called every frame
void UMainMeleeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMainMeleeComponent::SetWeaponHiddenInGame(bool bNewHidden) const
{
	WeaponMeshComponent->SetHiddenInGame(bNewHidden);
}

