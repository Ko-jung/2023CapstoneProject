// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Team_PlusHealth.h"

#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "Skyscraper/MainGame/Component/Health/HealthComponent.h"

void AItem_Team_PlusHealth::DoItemEffect(ASkyscraperCharacter* ItemUsedCharacter)
{
	TargetCharacter = ItemUsedCharacter;

	TargetCharacter->HealthComponent->ActivatePlusHealthBuff(PlusHealthValue, 20.0f);

	{ // TargetCharacter 의 팀에게도 적용시키기

	}

	Super::DoItemEffect(ItemUsedCharacter);
}

void AItem_Team_PlusHealth::Initialize(float fPlusHealthValue)
{
	PlusHealthValue = fPlusHealthValue;
}
