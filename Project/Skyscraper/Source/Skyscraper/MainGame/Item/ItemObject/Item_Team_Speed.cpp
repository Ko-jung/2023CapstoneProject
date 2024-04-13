// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Team_Speed.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"

Item_Team_Speed::Item_Team_Speed()
{
}

Item_Team_Speed::Item_Team_Speed(EItemRareLevel RareLevel)
{
	ItemBuffTime = 40.0f;
	switch (RareLevel)
	{
	case EItemRareLevel::EIRL_Normal:
		ItemBuffValue = 1.25f;
		break;
	case EItemRareLevel::EIRL_Rare:
		ItemBuffValue = 1.5f;
		break;
	case EItemRareLevel::EIRL_Legend:
		ItemBuffValue = 2.0f;
		break;
	default:
		break;
	}
}

Item_Team_Speed::~Item_Team_Speed()
{
}

void Item_Team_Speed::DoItemEffect(ASkyscraperCharacter* UsedCharacter)
{
	ItemObject::DoItemEffect(UsedCharacter);

	UE_LOG(LogTemp, Warning, TEXT("Item_Team_Speed - DoItemEffect"));
	UsedCharacter->SetSpeedBuffValue(ItemBuffValue,ItemBuffTime);

	{ // UsedCharacter 의 팀에게도 적용시키기

	}
}
