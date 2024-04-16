// Fill out your copyright notice in the Description page of Project Settings.


#include "AssassinCharacter.h"

AAssassinCharacter::AAssassinCharacter()
{
	{ // Set Mesh Character
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/character/4_assassin/assassin.assassin'"));
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
		// == Find and set AnimBlueprint (TEMP, Refactor to c++ later)
		static ConstructorHelpers::FClassFinder<UAnimInstance> AnimBPAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/2019180031/MainGame/Animation/Assassin/ABP_Assassin.ABP_Assassin_C'"));
		GetMesh()->SetAnimClass(AnimBPAsset.Class);
	}

	{ // == Set Anim Montages
		// Dagger
		// Katana
		//const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Katana1Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Assassin/Assassin/Combat/Melee/Katana/AM_Assassin_Katana_1.AM_Assassin_Katana_1'"));
		//*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_KatanaAttack) = AM_Katana1Ref.Object;
		
		//Rifle
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_RifleFireRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Assassin/Combat/Range/Rifle/AM_Assassin_AR_Fire.AM_Assassin_AR_Fire'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_RifleFire) = AM_RifleFireRef.Object;
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_RifleReloadRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Assassin/Combat/Range/Rifle/AM_Assassin_AR_Reload.AM_Assassin_AR_Reload'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_RifleReload) = AM_RifleReloadRef.Object;

		// Stiffness / Down
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_StiffnessRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Assassin/Combat/Damaged/AM_Assassin_Hit_Fwd.AM_Assassin_Hit_Fwd'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_Stiffness) = AM_StiffnessRef.Object;
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_StiffnessBwdRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Assassin/Combat/Damaged/AM_Assassin_Hit_Bwd.AM_Assassin_Hit_Bwd'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_Stiffness_Bwd) = AM_StiffnessBwdRef.Object;
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_DownRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Assassin/Combat/Damaged/AM_Assassin_Down_Fwd.AM_Assassin_Down_Fwd'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_Down) = AM_DownRef.Object;
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_DownBwdRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Assassin/Combat/Damaged/AM_Assassin_Down_Bwd.AM_Assassin_Down_Bwd'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_Down_Bwd) =AM_DownBwdRef.Object;
	}
}
