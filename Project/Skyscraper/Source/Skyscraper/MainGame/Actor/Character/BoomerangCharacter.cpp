// Fill out your copyright notice in the Description page of Project Settings.


#include "BoomerangCharacter.h"

#include "NiagaraComponent.h"
#include "NiagaraSystem.h"

ABoomerangCharacter::ABoomerangCharacter()
{
	CharacterType = ECharacterSelect::ECS_BoomerangCharacter;

	{ // Set Mesh Character
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/character/3_boomerang/boomerang.boomerang'"));
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

		// == Find and set AnimBlueprint (TEMP, Refactor to c++ later)
		//static ConstructorHelpers::FClassFinder<UAnimInstance> AnimBPAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/2019180031/MainGame/Animation/Boomerang/ABP_Boomerang.ABP_Boomerang_C'"));
		//GetMesh()->SetAnimClass(AnimBPAsset.Class);
	}

	{
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/character/3_boomerang/boom_boost.boom_boost'"));
		BoostMesh->SetSkeletalMesh(MeshAsset.Object);

		//static ConstructorHelpers::FClassFinder<UAnimInstance> ABP_BoostAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/2019180031/MainGame/Animation/Boomerang/Boost/ABP_Assassin_Boost.ABP_Assassin_Boost_C'"));
		//BoostMesh->SetAnimClass(ABP_BoostAsset.Class);
	}


	{ // == Set Anim Montages
		// Dagger
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_DaggerRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Boomerang/Combat/Melee/Dagger/AM_Boomerang_DaggerAttack.AM_Boomerang_DaggerAttack'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_DaggerAttack) = AM_DaggerRef.Object;

		// Katana
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_KatanaRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Boomerang/Combat/Melee/Katana/AM_Boomerang_KatanaAttack.AM_Boomerang_KatanaAttack'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_KatanaAttack) = AM_KatanaRef.Object;

		// GreatSword
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_GreatSwordRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Boomerang/Combat/Melee/Sword/AM_Boomerang_SwordAttack.AM_Boomerang_SwordAttack'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_GreatSwordAttack) = AM_GreatSwordRef.Object;


		//SMG
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_SMGRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Boomerang/Combat/Range/SMG/AM_Boomerang_SMG.AM_Boomerang_SMG'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_SMG) = AM_SMGRef.Object;

		//Rifle
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_RifleRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Boomerang/Combat/Range/Rifle/AM_Boomerang_Rifle.AM_Boomerang_Rifle'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_Rifle) = AM_RifleRef.Object;

		//RPG
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_RPGFireRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Boomerang/Combat/Range/RPG/AM_Boomerang_RPG.AM_Boomerang_RPG'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_RPG) = AM_RPGFireRef.Object;

		// Stun / Down
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_StunRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Boomerang/Combat/Damaged/AM_Boomerang_Hit.AM_Boomerang_Hit'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_Stun) = AM_StunRef.Object;

		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_DownRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Boomerang/Combat/Damaged/AM_Boomerang_Down.AM_Boomerang_Down'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_Down) = AM_DownRef.Object;

		// Death
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_DeathRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Boomerang/Combat/Death/AM_Boomerang_Death.AM_Boomerang_Death'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_Death) = AM_DeathRef.Object;

		// Boost
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_BoostRef(TEXT("/Script/Engine.AnimBlueprint'/Game/2019180031/MainGame/Animation/Boomerang/Boost/AM_Boom_Boost.AM_Boom_Boost'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_Boost) = AM_BoostRef.Object;

		// Interaction
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_InteractionRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Boomerang/Interaction/AM_Boomerang_Interaction.AM_Boomerang_Interaction'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_Interaction) = AM_InteractionRef.Object;
	}

	// 부메랑 로드 및 생성
	{
		BoostMesh->SetupAttachment(GetMesh(), FName("BoostSocket"));

		FAttachmentTransformRules AttachmentTransformRules{ EAttachmentRule::SnapToTarget,true };

		ConstructorHelpers::FObjectFinder<UStaticMesh> BigBoomerangRef(TEXT("/Script/Engine.StaticMesh'/Game/2016180023/character/3_boomerang/boom_BOOMERANG_big.boom_BOOMERANG_big'"));
		Boomerang_R = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Boomerang_R"));
		Boomerang_R->SetStaticMesh(BigBoomerangRef.Object);
		Boomerang_R->SetupAttachment(BoostMesh, TEXT("DriverRSocket"));

		ConstructorHelpers::FObjectFinder<UStaticMesh> SmallBoomerangRef(TEXT("/Script/Engine.StaticMesh'/Game/2016180023/character/3_boomerang/boom_BOOMERANG_small.boom_BOOMERANG_small'"));
		Boomerang_L = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Boomerang_L"));
		Boomerang_L->SetStaticMesh(SmallBoomerangRef.Object);
		Boomerang_L->SetupAttachment(BoostMesh, TEXT("DriverLSocket"));
	}

	CommonSkillCoolTime = 10.f;
	SpecialSkillCoolTime = 25.f;

	{
		static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_BoostEffectRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/2019180031/MainGame/Fbx/Boost/NS_BoostSpawn.NS_BoostSpawn'"));
		if (NS_BoostEffectRef.Succeeded())
		{
			NS_BoostEffect->SetAsset(NS_BoostEffectRef.Object);
		}

		NS_BoostEffect->SetupAttachment(BoostMesh, TEXT("BoostStartSocket"));
		NS_BoostEffect->SetRelativeLocation(FVector(-0.788, 7.19, -0.019f));
		NS_BoostEffect->SetRelativeRotation(FRotator{ 0.0f,0.0f,-90.0f });
		NS_BoostEffect->SetRelativeScale3D(FVector{ 0.1f,0.1f,0.25f });
		NS_DashEffect->SetHiddenInGame(true);
	}
}

void ABoomerangCharacter::SetMeshCustomDepth(bool IsEnemy)
{
	Super::SetMeshCustomDepth(IsEnemy);

	Boomerang_R->CustomDepthStencilValue = IsEnemy;
	Boomerang_R->bRenderCustomDepth = !IsEnemy;
	Boomerang_R->MarkRenderStateDirty();

	Boomerang_L->CustomDepthStencilValue = IsEnemy;
	Boomerang_L->bRenderCustomDepth = !IsEnemy;
	Boomerang_L->MarkRenderStateDirty();
}
