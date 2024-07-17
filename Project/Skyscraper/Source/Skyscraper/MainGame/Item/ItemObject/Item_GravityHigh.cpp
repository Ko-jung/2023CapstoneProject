// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_GravityHigh.h"

#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"

UItem_GravityHigh::UItem_GravityHigh()
{
	bGravityLow = false;
}

UItem_GravityHigh::~UItem_GravityHigh()
{
}

void UItem_GravityHigh::DoItemEffect(ASkyscraperCharacter* UsedCharacter)
{
	UItemObject::DoItemEffect(UsedCharacter);
	UE_LOG(LogTemp, Warning, TEXT("Gravity High Item Used"));
	UsedCharacter->SpawnGravityChangerArea(bGravityLow);
}
