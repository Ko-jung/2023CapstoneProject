// Fill out your copyright notice in the Description page of Project Settings.


#include "AssassinCharacter.h"

AAssassinCharacter::AAssassinCharacter()
{
	{ // Set Mesh Character
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/character/4_assassin/assassin.assassin'"));
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
		// == Find and set AnimBlueprint (TEMP, Refactor to c++ later)
		static ConstructorHelpers::FClassFinder<UAnimInstance> AnimBPAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/2019180031/MainGame/Animation/Assassin/ABP_Test_Assassin.ABP_Test_Assassin_C'"));
		GetMesh()->SetAnimClass(AnimBPAsset.Class);
	}
}
