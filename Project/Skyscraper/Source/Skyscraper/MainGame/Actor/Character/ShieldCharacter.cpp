// Fill out your copyright notice in the Description page of Project Settings.


#include "Skyscraper/MainGame/Actor/Character/ShieldCharacter.h"

AShieldCharacter::AShieldCharacter()
{
	CharacterType = ECharacterSelect::ECS_ShieldCharacter;
	{ // Set Mesh Character
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/character/0_shield/shield.shield'"));
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
		// == Find and set AnimBlueprint (TEMP, Refactor to c++ later)
		static ConstructorHelpers::FClassFinder<UAnimInstance> AnimBPAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/2019180031/MainGame/Animation/Shield/ABP_Shield.ABP_Shield_C'"));
		GetMesh()->SetAnimClass(AnimBPAsset.Class);
	}

	{
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/character/0_shield/shield_boost.shield_boost'"));
		BoostMesh->SetSkeletalMesh(MeshAsset.Object);

		BoostMesh->SetupAttachment(GetMesh(), FName("BoostSocket"));

		static ConstructorHelpers::FClassFinder<UAnimInstance> ABP_BoostAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/2019180031/MainGame/Animation/Shield/Boost/ABP_Shield_Boost.ABP_Shield_Boost_C'"));
		BoostMesh->SetAnimClass(ABP_BoostAsset.Class);
	}
	
	{ // == Set Anim Montages
		// Dagger
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_DaggerRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Shield/Combat/Melee/Dagger/AM_Shield_DaggerAttack.AM_Shield_DaggerAttack'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_DaggerAttack) = AM_DaggerRef.Object;

		// Katana
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_KatanaRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Shield/Combat/Melee/Katana/AM_Shield_KatanaAttack.AM_Shield_KatanaAttack'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_KatanaAttack)= AM_KatanaRef.Object;

		// GreatSword
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_GreatSwordRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Shield/Combat/Melee/Sword/AM_Shield_SwordAttack.AM_Shield_SwordAttack'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_GreatSwordAttack) = AM_GreatSwordRef.Object;


		//SMG
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_SMGRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Shield/Combat/Range/SMG/AM_Shield_SMG.AM_Shield_SMG'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_SMG) = AM_SMGRef.Object;

		//Rifle
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_RifleRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Shield/Combat/Range/Rifle/AM_Shield_Rifle.AM_Shield_Rifle'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_Rifle) = AM_RifleRef.Object;

		//RPG
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_RPGFireRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Shield/Combat/Range/RPG/AM_Shield_RPG.AM_Shield_RPG'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_RPG) = AM_RPGFireRef.Object;

		// Stun / Down
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_StunRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Shield/Combat/Damaged/AM_Shield_Hit.AM_Shield_Hit'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_Stun) = AM_StunRef.Object;

		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_DownRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Shield/Combat/Damaged/AM_Shield_Down.AM_Shield_Down'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_Down) = AM_DownRef.Object;

		// Death
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_DeathRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Shield/Combat/Death/AM_Shield_Death.AM_Shield_Death'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_Death) = AM_DeathRef.Object;

		// Boost
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_BoostRef(TEXT("/Script/Engine.AnimBlueprint'/Game/2019180031/MainGame/Animation/Shield/Boost/AM_Shield_Boost.AM_Shield_Boost'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_Boost) = AM_BoostRef.Object;
	}

	// Skirt
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> SkirtStaticMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/2016180023/character/0_shield/shield_skirt.shield_skirt'"));
		SkirtStaticMesh = SkirtStaticMeshAsset.Object;

		static ConstructorHelpers::FObjectFinder<UMaterial> SkirtMaterialAsset(TEXT("/Script/Engine.Material'/Game/2016180023/character/0_shield/material/Material_skirt.Material_skirt'"));
		SkirtMaterial = SkirtMaterialAsset.Object;

		SkirtMaterialValue = 13;
	}

	IsCanUseShield = true;
}

void AShieldCharacter::BreakShield()
{
	IsCanUseShield = false;

	GetWorld()->GetTimerManager().SetTimer(UnableActTimerHandle, [this]() {
		IsCanUseShield = true;
		}, 10.f, false);
}

void AShieldCharacter::SetShieldHealth_Implementation(float Damage)
{
}

void AShieldCharacter::SkillActorDamaged(float AfterHp)
{
	UE_LOG(LogTemp, Warning, TEXT("This Character is Shiled"));
	SetShieldHealth(AfterHp);
}

void AShieldCharacter::GetShieldDamage_Implementation(float Damage)
{
}