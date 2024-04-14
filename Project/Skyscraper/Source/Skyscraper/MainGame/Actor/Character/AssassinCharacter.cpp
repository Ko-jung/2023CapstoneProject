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
		//*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_KatanaAttack1) = AM_Katana1Ref.Object;
		//const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Katana2Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Assassin/Assassin/Combat/Melee/Katana/AM_Assassin_Katana_2.AM_Assassin_Katana_2'"));
		//*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_KatanaAttack2) = AM_Katana2Ref.Object;
		//const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Katana3Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Assassin/Assassin/Combat/Melee/Katana/AM_Assassin_Katana_3.AM_Assassin_Katana_3'"));
		//*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_KatanaAttack3) =  AM_Katana3Ref.Object;
		//const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Katana4Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Assassin/Assassin/Combat/Melee/Katana/AM_Assassin_Katana_4.AM_Assassin_Katana_4'"));
		//*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_KatanaAttack4) = AM_Katana4Ref.Object;
		
		//Rifle
		//const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_RifleFireRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Assassin/Assassin/Combat/Range/Rifle/AM_Assassin_AR_Fire.AM_Assassin_AR_Fire'"));
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_RifleFireRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Assassin/Assassin/Combat/Range/Rifle/AM_Assassin_AR_Fire.AM_Assassin_AR_Fire'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_RifleFire) = AM_RifleFireRef.Object;
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_RifleReadyFireRef(TEXT(""));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_RifleReadyFire) = AM_RifleReadyFireRef.Object;
		const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_RifleReloadRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Assassin/Assassin/Combat/Range/Rifle/AM_Assassin_AR_Reload.AM_Assassin_AR_Reload'"));
		*CharacterAnimMontages.Find(ECharacterAnimMontage::ECAM_RifleReload) = AM_RifleReloadRef.Object;
	}
}
