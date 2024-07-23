// Fill out your copyright notice in the Description page of Project Settings.


#include "WindCharacter.h"

#include "NiagaraComponent.h"

AWindCharacter::AWindCharacter() 
{
	CharacterType = ECharacterSelect::ECS_WindCharacter;
	{ // Set Mesh Character
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/character/1_wind/wind.wind'"));
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
		// == Find and set AnimBlueprint (TEMP, Refactor to c++ later)
		static ConstructorHelpers::FClassFinder<UAnimInstance> AnimBPAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/2019180031/MainGame/Animation/Wind/ABP_Wind.ABP_Wind_C'"));
		GetMesh()->SetAnimClass(AnimBPAsset.Class);
	}

	{
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/character/1_wind/wind_boost.wind_boost'"));
		BoostMesh->SetSkeletalMesh(MeshAsset.Object);

		BoostMesh->SetupAttachment(GetMesh(), FName("BoostSocket"));

		static ConstructorHelpers::FClassFinder<UAnimInstance> ABP_BoostAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/2019180031/MainGame/Animation/Wind/Boost/ABP_Wind_Boost.ABP_Wind_Boost_C'"));
		BoostMesh->SetAnimClass(ABP_BoostAsset.Class);
	}

	{ // == Set Anim Montages
		// Dagger
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_DaggerRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Wind/Combat/Melee/Dagger/AM_Wind_DaggerAttack.AM_Wind_DaggerAttack'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_DaggerAttack) = AM_DaggerRef.Object;

		// Katana
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_KatanaRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Wind/Combat/Melee/Katana/AM_Wind_KatanaAttack.AM_Wind_KatanaAttack'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_KatanaAttack) = AM_KatanaRef.Object;

		// GreatSword
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_GreatSwordRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Wind/Combat/Melee/Sword/AM_Wind_SwordAttack.AM_Wind_SwordAttack'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_GreatSwordAttack) = AM_GreatSwordRef.Object;


		//SMG
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_SMGRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Wind/Combat/Range/SMG/AM_Wind_SMG.AM_Wind_SMG'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_SMG) = AM_SMGRef.Object;

		//Rifle
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_RifleRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Wind/Combat/Range/Rifle/AM_Wind_Rifle.AM_Wind_Rifle'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_Rifle) = AM_RifleRef.Object;

		//RPG
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_RPGFireRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Wind/Combat/Range/RPG/AM_Wind_RPG.AM_Wind_RPG'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_RPG) = AM_RPGFireRef.Object;

		// Stun / Down
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_StunRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Wind/Combat/Damaged/AM_Wind_Hit.AM_Wind_Hit'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_Stun) = AM_StunRef.Object;

		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_DownRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Wind/Combat/Damaged/AM_Wind_Down.AM_Wind_Down'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_Down) = AM_DownRef.Object;

		// Death
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_DeathRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Wind/Combat/Death/AM_Wind_Death.AM_Wind_Death'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_Death) = AM_DeathRef.Object;

		// Boost
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_BoostRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Wind/Boost/AM_Wind_Boost.AM_Wind_Boost'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_Boost) = AM_BoostRef.Object;


		// Interaction
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_InteractionRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Wind/Interaction/AM_Wind_Interaction.AM_Wind_Interaction'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_Interaction) = AM_InteractionRef.Object;
	}

	{
		NS_BoostEffect->SetRelativeLocation(FVector(-0.788,0.37,0.5));
		NS_BoostEffect->SetRelativeRotation(FRotator{ 0.0f,-90.0f,-90.0f });
		

		NS_BoostEffectRight = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NS_BoostEffectRight"));
		NS_BoostEffectRight->SetAsset(NS_BoostEffect->GetAsset());
		NS_BoostEffectRight->SetupAttachment(BoostMesh, TEXT("BoostStartSocketRight"));
		NS_BoostEffectRight->SetRelativeLocation(FVector(-0.788, 7.19, -0.019f));
		NS_BoostEffectRight->SetRelativeRotation(FRotator{ 0.0f,0.0f,-90.0f });
		NS_BoostEffectRight->SetRelativeScale3D(FVector{ 0.1f,0.1f,0.25f });
		NS_BoostEffectRight->SetHiddenInGame(true);
	}
}

void AWindCharacter::SetBoostEffectVisibility(bool bVisible)
{
	Super::SetBoostEffectVisibility(bVisible);

	if (!NS_BoostEffectRight) return;

	if (bVisible)
	{
		NS_BoostEffectRight->SetHiddenInGame(false);
		NS_BoostEffectRight->Activate(true);
	}
	else
	{
		NS_BoostEffectRight->SetHiddenInGame(true);
	}
}
