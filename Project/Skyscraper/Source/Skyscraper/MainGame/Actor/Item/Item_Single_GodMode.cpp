// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Single_GodMode.h"

#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "Skyscraper/MainGame/Component/Health/HealthComponent.h"

void AItem_Single_GodMode::DoItemEffect(ASkyscraperCharacter* ItemUsedCharacter)
{
	TargetCharacter = ItemUsedCharacter;
	TargetCharacter->HealthComponent->ActivateGodMode(GodModeTime);

	Super::DoItemEffect(ItemUsedCharacter);
}

void AItem_Single_GodMode::Initialize(float fGetGodModeTime)
{
	GodModeTime = fGetGodModeTime;
}
