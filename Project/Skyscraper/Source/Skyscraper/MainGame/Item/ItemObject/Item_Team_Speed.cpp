// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Team_Speed.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"

UItem_Team_Speed::UItem_Team_Speed()
{
}

void UItem_Team_Speed::SetItemRare(EItemRareLevel RareLevel)
{
	UItemObject::SetItemRare(RareLevel);
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


UItem_Team_Speed::~UItem_Team_Speed()
{
}

void UItem_Team_Speed::DoItemEffect(ASkyscraperCharacter* UsedCharacter)
{
	UItemObject::DoItemEffect(UsedCharacter);

	UE_LOG(LogTemp, Warning, TEXT("Item_Team_Speed - DoItemEffect"));
	UsedCharacter->SetSpeedBuffValue(ItemBuffValue,ItemBuffTime);

	{ // UsedCharacter 의 팀에게도 적용시키기

	}
}
