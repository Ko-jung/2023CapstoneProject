// Fill out your copyright notice in the Description page of Project Settings.


#include "Skyscraper/MainGame/Actor/Character/ShieldCharacter.h"

AShieldCharacter::AShieldCharacter()
{
	{ // Set Mesh Character
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/2019180031/Character/ShieldCharacter/ShieldCharacter.ShieldCharacter'"));
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
		GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
		// == Find and set AnimBlueprint (TEMP, Refactor to c++ later)
		static ConstructorHelpers::FClassFinder<UAnimInstance> AnimBPAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/2019180031/Character/ShieldCharacter/ABP_Shield.ABP_Shield_C'"));
		GetMesh()->SetAnimClass(AnimBPAsset.Class);
	}

	if(CharacterAnimMontages.IsEmpty())
	{
		{ // == Set Anim Montages
		// Dagger
			const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Dagger1Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/Dagger/AM_Dagger1.AM_Dagger1'"));
			CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_DaggerAttack1, AM_Dagger1Ref.Object);
			const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Dagger2Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/Dagger/AM_Dagger2.AM_Dagger2'"));
			CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_DaggerAttack2, AM_Dagger2Ref.Object);
			const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Dagger3Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/Dagger/AM_Dagger3.AM_Dagger3'"));
			CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_DaggerAttack3, AM_Dagger3Ref.Object);
			const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Dagger4Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/Dagger/AM_Dagger4.AM_Dagger4'"));
			CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_DaggerAttack4, AM_Dagger4Ref.Object);
			const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Dagger5Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/Dagger/AM_Dagger5.AM_Dagger5'"));
			CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_DaggerAttack5, AM_Dagger5Ref.Object);
			// Katana
			const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Katana1Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/Katana/AM_Katana1.AM_Katana1'"));
			CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_KatanaAttack1, AM_Katana1Ref.Object);
			const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Katana2Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/Katana/AM_Katana2.AM_Katana2'"));
			CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_KatanaAttack2, AM_Katana2Ref.Object);
			const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Katana3Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/Katana/AM_Katana3.AM_Katana3'"));
			CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_KatanaAttack3, AM_Katana3Ref.Object);
			const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Katana4Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/Katana/AM_Katana4.AM_Katana4'"));
			CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_KatanaAttack4, AM_Katana4Ref.Object);
			// GreatSword
			const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_GreatSword1Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/GreatSword/GreatSwordSlash1_Montage.GreatSwordSlash1_Montage'"));
			CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_GreatSwordAttack1, AM_GreatSword1Ref.Object);
			const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_GreatSword2Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/GreatSword/GreatSwordSlash2_Montage.GreatSwordSlash2_Montage'"));
			CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_GreatSwordAttack2, AM_GreatSword2Ref.Object);
			const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_GreatSword3Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/GreatSword/GreatSwordSlash3_Montage.GreatSwordSlash3_Montage'"));
			CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_GreatSwordAttack3, AM_GreatSword3Ref.Object);

			//SMG
			const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_SMGFireRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Rifle/AM_FireRifle.AM_FireRifle'"));
			CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_SMGFire, AM_SMGFireRef.Object);
			const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_SMGReloadRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Rifle/AM_ReloadRifle.AM_ReloadRifle'"));
			CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_SMGReload, AM_SMGReloadRef.Object);

			//Rifle
			const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_RifleFireRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Rifle/AM_FireRifle.AM_FireRifle'"));
			CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_RifleFire, AM_RifleFireRef.Object);
			const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_RifleReloadRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Rifle/AM_ReloadRifle.AM_ReloadRifle'"));
			CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_RifleReload, AM_RifleReloadRef.Object);
			//RPG
			const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_RPGFireRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Rifle/AM_FireRifle.AM_FireRifle'"));
			CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_RPGFire, AM_RPGFireRef.Object);
			const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_RPGReloadRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Rifle/AM_ReloadRifle.AM_ReloadRifle'"));
			CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_RPGReload, AM_RPGReloadRef.Object);

			// Stiffness / Down
			const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_StiffnessRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Damaged/AM_GetDamaged.AM_GetDamaged'"));
			CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_Stiffness, AM_StiffnessRef.Object);
			const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_DownRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Damaged/AM_KnockedDown.AM_KnockedDown'"));
			CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_Down, AM_DownRef.Object);

		}
	}
}
