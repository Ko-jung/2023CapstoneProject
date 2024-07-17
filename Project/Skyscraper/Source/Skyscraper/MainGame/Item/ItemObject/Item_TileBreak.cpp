// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_TileBreak.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"

UItem_TileBreak::UItem_TileBreak()
{
}

UItem_TileBreak::~UItem_TileBreak()
{
}


void UItem_TileBreak::DoItemEffect(ASkyscraperCharacter* UsedCharacter)
{
	UItemObject::DoItemEffect(UsedCharacter);

	UE_LOG(LogTemp, Warning, TEXT("Item_boostBulletInfinity - DoItemEffect"));
	
	

}
