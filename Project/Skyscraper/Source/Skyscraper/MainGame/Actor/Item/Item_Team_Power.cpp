// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Team_Power.h"

#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"

void AItem_Team_Power::DoItemEffect(ASkyscraperCharacter* ItemUsedCharacter)
{
	
	TargetCharacter = ItemUsedCharacter;

	TargetCharacter->SetPowerBuffValue(ItemPowerBuffValue, 30.0f);

	{ // TargetCharacter 의 팀에게도 적용시키기

	}

	Super::DoItemEffect(ItemUsedCharacter);
}

void AItem_Team_Power::Initialize(float fPowerBuffValue)
{
	ItemPowerBuffValue= fPowerBuffValue;
}
