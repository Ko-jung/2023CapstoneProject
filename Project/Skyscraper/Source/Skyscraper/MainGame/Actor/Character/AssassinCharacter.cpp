// Fill out your copyright notice in the Description page of Project Settings.


#include "AssassinCharacter.h"

#include "NiagaraComponent.h"
#include "NiagaraSystem.h"

AAssassinCharacter::AAssassinCharacter()
{
	CharacterType = ECharacterSelect::ECS_AssassinCharacter;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/character/4_assassin/assassin_boost.assassin_boost'"));
	BoostMesh->SetSkeletalMesh(MeshAsset.Object);

	BoostMesh->SetupAttachment(GetMesh(), FName("BoostSocket"));

	//static ConstructorHelpers::FClassFinder<UAnimInstance> ABP_BoostAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/2019180031/MainGame/Animation/Assassin/Boost/ABP_Assassin_Boost.ABP_Assassin_Boost_C'"));
	//BoostMesh->SetAnimClass(ABP_BoostAsset.Class);

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

void AAssassinCharacter::CharacterAttackEvent()
{
	IsStealthMode = false;
}

void AAssassinCharacter::BuffUsingSkill()
{
	SetSpeedBuffValue(1.2f, 10.f);
	SetPowerBuffValue(1.25f, 10.f);
}