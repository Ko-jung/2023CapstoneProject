// Fill out your copyright notice in the Description page of Project Settings.


#include "AssassinCharacter.h"

AAssassinCharacter::AAssassinCharacter()
{
	// Skyscraper Character를 Assassin 캐릭터에 맞춰서 작업하여 생성자에서 작업해줄 필요 없음

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/character/4_assassin/assassin_boost.assassin_boost'"));
	BoostMesh->SetSkeletalMesh(MeshAsset.Object);


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
}

void AAssassinCharacter::CastingSkill(bool IsSpecialSkill)
{
}
