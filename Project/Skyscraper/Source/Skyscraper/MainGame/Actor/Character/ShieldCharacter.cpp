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
		
	}
}
