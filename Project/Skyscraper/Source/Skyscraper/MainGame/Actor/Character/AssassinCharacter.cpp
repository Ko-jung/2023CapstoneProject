// Fill out your copyright notice in the Description page of Project Settings.


#include "AssassinCharacter.h"

AAssassinCharacter::AAssassinCharacter()
{
	// Skyscraper Character를 Assassin 캐릭터에 맞춰서 작업하여 생성자에서 작업해줄 필요 없음

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/character/4_assassin/assassin_boost.assassin_boost'"));
	BoostMesh->SetSkeletalMesh(MeshAsset.Object);
}
