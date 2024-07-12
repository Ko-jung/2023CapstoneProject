// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_GravityLow.h"

#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"


Item_GravityLow::Item_GravityLow()
{
	bGravityLow = true;
}

Item_GravityLow::~Item_GravityLow()
{
}

void Item_GravityLow::DoItemEffect(ASkyscraperCharacter* UsedCharacter)
{
	ItemObject::DoItemEffect(UsedCharacter);

	UE_LOG(LogTemp, Warning, TEXT("Gravity Low Item Used"));
	UsedCharacter->SpawnGravityChangerArea(bGravityLow);
}
