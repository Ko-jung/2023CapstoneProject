// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_GravityLow.h"

#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"


UItem_GravityLow::UItem_GravityLow()
{
	bGravityLow = true;
}

UItem_GravityLow::~UItem_GravityLow()
{
}

void UItem_GravityLow::DoItemEffect(ASkyscraperCharacter* UsedCharacter)
{
	UItemObject::DoItemEffect(UsedCharacter);

	UE_LOG(LogTemp, Warning, TEXT("Gravity Low Item Used"));
	UsedCharacter->SpawnGravityChangerArea(bGravityLow);
}
