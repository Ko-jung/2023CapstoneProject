// Fill out your copyright notice in the Description page of Project Settings.


#include "TrainingBot.h"

#include "NiagaraComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ATrainingBot::ATrainingBot() 
{
	bIsTrainingBot = true;

	{
		CameraBoom->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
		CameraBoom->SetVisibility(false);
		FollowCamera->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
		FollowCamera->SetVisibility(false);
		NS_DashEffect->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
		NS_DashEffect->SetVisibility(false);
		BoostMesh->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
		BoostMesh->SetVisibility(false);
		NS_BoostEffect->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
		NS_BoostEffect->SetVisibility(false);
	}

	{ // Set Mesh Character
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/character/training_bot/training_bot_skin.training_bot_skin'"));
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

		GetMesh()->SetRelativeScale3D(FVector{ 3.5f,3.5f,3.5f });

		// == Find and set AnimBlueprint (TEMP, Refactor to c++ later)
		static ConstructorHelpers::FClassFinder<UAnimInstance> AnimBPAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/2019180031/MainGame/Animation/TrainingBot/ABP_TrainingBot.ABP_TrainingBot_C'"));
		GetMesh()->SetAnimClass(AnimBPAsset.Class);
	}

	// Stun / Down
	{
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_StunRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/TrainingBot/AM_TrainingBot_Hit.AM_TrainingBot_Hit'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_Stun) = AM_StunRef.Object;

		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_DownRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/TrainingBot/AM_TrainingBot_Down.AM_TrainingBot_Down'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_Down) = AM_DownRef.Object;
	}
	
	ResetTimer = 15.f;
}

void ATrainingBot::DoStun(const AActor* Attacker, const float StunTime, const FVector StunDirection) const
{
	//Super::DoStun(Attacker, StunTime, StunDirection);
	ApplyStun(StunTime, StunDirection);
}

void ATrainingBot::DoDown(const AActor* Attacker, const FVector& DownDirection) const
{
	//Super::DoDown(Attacker, DownDirection);
	ApplyDown(DownDirection);
}

void ATrainingBot::SetTimer()
{
	DamagedTimer = ResetTimer;	// 2019180016
}

void ATrainingBot::BeginPlay()
{
	Super::BeginPlay();

	BotBeginTransform = GetActorTransform();
	DamagedTimer = ResetTimer;	// 2019180016
}

void ATrainingBot::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (DamagedTimer >= 0.f)
	{
		DamagedTimer -= DeltaSeconds;
		if (DamagedTimer < 0.f)
		{
			SetActorTransform(BotBeginTransform);
			DamagedTimer = ResetTimer;
		}
	}
}
