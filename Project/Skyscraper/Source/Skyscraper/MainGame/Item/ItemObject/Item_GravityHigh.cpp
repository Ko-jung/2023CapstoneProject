// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_GravityHigh.h"

#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"

Item_GravityHigh::Item_GravityHigh()
{
	bGravityLow = false;
}

Item_GravityHigh::~Item_GravityHigh()
{
}

void Item_GravityHigh::DoItemEffect(ASkyscraperCharacter* UsedCharacter)
{
	ItemObject::DoItemEffect(UsedCharacter);
	UE_LOG(LogTemp, Warning, TEXT("Gravity High Item Used"));
	UsedCharacter->SpawnGravityChangerArea(bGravityLow);
}
