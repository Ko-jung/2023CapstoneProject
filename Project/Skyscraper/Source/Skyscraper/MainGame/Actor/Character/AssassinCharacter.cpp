// Fill out your copyright notice in the Description page of Project Settings.


#include "AssassinCharacter.h"

AAssassinCharacter::AAssassinCharacter()
{
	CharacterType = ECharacterSelect::ECS_AssassinCharacter;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/character/4_assassin/assassin_boost.assassin_boost'"));
	BoostMesh->SetSkeletalMesh(MeshAsset.Object);

	BoostMesh->SetupAttachment(GetMesh(), FName("BoostSocket"));

	static ConstructorHelpers::FClassFinder<UAnimInstance> ABP_BoostAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/2019180031/MainGame/Animation/Assassin/Boost/ABP_Assassin_Boost.ABP_Assassin_Boost_C'"));
	BoostMesh->SetAnimClass(ABP_BoostAsset.Class);

	// Skirt
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> SkirtStaticMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/2016180023/character/4_assassin/assassin_skirt.assassin_skirt'"));
		SkirtStaticMesh = SkirtStaticMeshAsset.Object;

		static ConstructorHelpers::FObjectFinder<UMaterial> SkirtMaterialAsset(TEXT("/Script/Engine.Material'/Game/2016180023/character/4_assassin/material/Material_skirt.Material_skirt'"));
		SkirtMaterial = SkirtMaterialAsset.Object;

		SkirtMaterialValue = 11;
	}


	// // ============== 2019180016 ==============
	IsStealthMode = false;
	// Process Blueprint Node
	// // SKill
	// {
	// 	const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_CommonRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Assassin/Boost/AM_Assassin_Boost.AM_Assassin_Boost'"));
	// 	CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_CommonSkill, AM_CommonRef.Object);
	// 
	// 	// const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_SpecialRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/MainGame/Animation/Assassin/Boost/AM_Assassin_Boost.AM_Assassin_Boost'"));
	// 	// CharacterAnimMontages.Add(ECharacterAnimMontage::ECAM_SpecialSkill, AM_SpecialRef.Object);
	// }
	// // ========================================

	CommonSkillCoolTime = 12.f;
	SpecialSkillCoolTime = 15.f;
}

void AAssassinCharacter::CharacterAttackEvent()
{
	IsStealthMode = false;
}

void AAssassinCharacter::BuffUsingSkill()
{
	SetSpeedBuffValue(1.2f, 10.f);
	SetPowerBuffValue(1.25f, 10.f);
}
