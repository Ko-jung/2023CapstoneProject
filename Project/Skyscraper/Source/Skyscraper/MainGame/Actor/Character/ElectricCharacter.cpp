// Fill out your copyright notice in the Description page of Project Settings.


#include "ElectricCharacter.h"

AElectricCharacter::AElectricCharacter()
{
	{ // Set Mesh Character
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/character/2_electric/elec.elec'"));
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
		GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
		// == Find and set AnimBlueprint (TEMP, Refactor to c++ later)
		static ConstructorHelpers::FClassFinder<UAnimInstance> AnimBPAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/2019180031/MainGame/Animation/Electric/ABP_Electric.ABP_Electric_C'"));
		GetMesh()->SetAnimClass(AnimBPAsset.Class);
	}

	{
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/character/2_electric/elec_boost.elec_boost'"));
		BoostMesh->SetSkeletalMesh(MeshAsset.Object);
	}


	{ // == Set Anim Montages
		// Dagger
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_DaggerRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Electric/Combat/Melee/Dagger/AM_Electric_DaggerAttack.AM_Electric_DaggerAttack'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_DaggerAttack) = AM_DaggerRef.Object;

		// Katana
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_KatanaRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Electric/Combat/Melee/Katana/AM_Electric_KatanaAttack.AM_Electric_KatanaAttack'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_KatanaAttack) = AM_KatanaRef.Object;

		// GreatSword
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_GreatSwordRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Electric/Combat/Melee/Sword/AM_Electric_SwordAttack.AM_Electric_SwordAttack'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_GreatSwordAttack) = AM_GreatSwordRef.Object;


		//SMG
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_SMGRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Electric/Combat/Range/SMG/AM_Electric_SMG.AM_Electric_SMG'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_SMG) = AM_SMGRef.Object;

		//Rifle
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_RifleRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Electric/Combat/Range/Rifle/AM_Electric_Rifle.AM_Electric_Rifle'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_Rifle) = AM_RifleRef.Object;

		//RPG
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_RPGFireRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Electric/Combat/Range/RPG/AM_Electric_RPG.AM_Electric_RPG'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_RPG) = AM_RPGFireRef.Object;

		// Stun / Down
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_StunRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Electric/Combat/Damaged/AM_Electric_Hit.AM_Electric_Hit'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_Stun) = AM_StunRef.Object;

		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_DownRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Electric/Combat/Damaged/AM_Electric_Down.AM_Electric_Down'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_Down) = AM_DownRef.Object;

		// Death
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_DeathRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Electric/Combat/Death/AM_Electric_Death.AM_Electric_Death'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_Death) = AM_DeathRef.Object;


	}

}
