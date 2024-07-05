// Fill out your copyright notice in the Description page of Project Settings.


#include "RadarCharacter.h"

ARadarCharacter::ARadarCharacter() 
{
	{ // Set Mesh Character
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/character/5_radar/radar.radar'"));
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
		// == Find and set AnimBlueprint (TEMP, Refactor to c++ later)
		static ConstructorHelpers::FClassFinder<UAnimInstance> AnimBPAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/2019180031/MainGame/Animation/Radar/ABP_Radar.ABP_Radar_C'"));
		GetMesh()->SetAnimClass(AnimBPAsset.Class);
	}


	{
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/character/5_radar/radar_boost.radar_boost'"));
		BoostMesh->SetSkeletalMesh(MeshAsset.Object);

		BoostMesh->SetupAttachment(GetMesh(), FName("BoostSocket"));

		static ConstructorHelpers::FClassFinder<UAnimInstance> ABP_BoostAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/2019180031/MainGame/Animation/Radar/Boost/ABP_Radar_Boost.ABP_Radar_Boost_C'"));
		BoostMesh->SetAnimClass(ABP_BoostAsset.Class);
	}

	{ // == Set Anim Montages
		// Dagger
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_DaggerRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Radar/Combat/Melee/Dagger/AM_Radar_DaggerAttack.AM_Radar_DaggerAttack'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_DaggerAttack) = AM_DaggerRef.Object;

		// Katana
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_KatanaRef(TEXT("//Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Radar/Combat/Melee/Katana/AM_Radar_KatanaAttack.AM_Radar_KatanaAttack'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_KatanaAttack) = AM_KatanaRef.Object;

		// GreatSword
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_GreatSwordRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Radar/Combat/Melee/Sword/AM_Radar_SwordAttack.AM_Radar_SwordAttack'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_GreatSwordAttack) = AM_GreatSwordRef.Object;


		//SMG
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_SMGRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Radar/Combat/Range/SMG/AM_Radar_SMG.AM_Radar_SMG'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_SMG) = AM_SMGRef.Object;

		//Rifle
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_RifleRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Radar/Combat/Range/Rifle/AM_Radar_Rifle.AM_Radar_Rifle'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_Rifle) = AM_RifleRef.Object;

		//RPG
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_RPGFireRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Radar/Combat/Range/RPG/AM_Radar_RPG.AM_Radar_RPG'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_RPG) = AM_RPGFireRef.Object;

		// Stun / Down
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_StunRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Radar/Combat/Damaged/AM_Radar_Hit.AM_Radar_Hit'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_Stun) = AM_StunRef.Object;

		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_DownRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Radar/Combat/Damaged/AM_Radar_Down.AM_Radar_Down'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_Down) = AM_DownRef.Object;

		// Death
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_DeathRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Radar/Combat/Death/AM_Radar_Death.AM_Radar_Death'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_Death) = AM_DeathRef.Object;

		// Boost
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_BoostRef(TEXT("/Script/Engine.AnimBlueprint'/Game/2019180031/MainGame/Animation/Radar/Boost/AM_Radar_Boost.AM_Radar_Boost'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_Boost) = AM_BoostRef.Object;
	}

	// Skirt
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> SkirtStaticMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/2016180023/character/5_radar/radar_skirt.radar_skirt'"));
		SkirtStaticMesh = SkirtStaticMeshAsset.Object;

		static ConstructorHelpers::FObjectFinder<UMaterial> SkirtMaterialAsset(TEXT("/Script/Engine.Material'/Game/2016180023/character/5_radar/material/Material_skirt.Material_skirt'"));
		SkirtMaterial = SkirtMaterialAsset.Object;

		SkirtMaterialValue = 13;
	}
}
