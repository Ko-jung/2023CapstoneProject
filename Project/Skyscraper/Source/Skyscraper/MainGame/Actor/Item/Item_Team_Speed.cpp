// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Team_Speed.h"

#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"

void AItem_Team_Speed::DoItemEffect(ASkyscraperCharacter* ItemUsedCharacter)
{
	TargetCharacter = ItemUsedCharacter;

	TargetCharacter->SetSpeedBuffValue(ItemSpeedBuffValue, 40.0f);

	{ // TargetCharacter 의 팀에게도 적용시키기
		
	}


	Super::DoItemEffect(ItemUsedCharacter);
}

void AItem_Team_Speed::Initialize(float fSpeedBuffValue)
{
	ItemSpeedBuffValue = fSpeedBuffValue;
}
