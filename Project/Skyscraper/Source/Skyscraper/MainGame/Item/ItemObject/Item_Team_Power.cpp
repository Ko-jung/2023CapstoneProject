// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Team_Power.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"


UItem_Team_Power::UItem_Team_Power()
{
}

void UItem_Team_Power::SetItemRare(EItemRareLevel RareLevel)
{
	UItemObject::SetItemRare(RareLevel);
	ItemBuffTime = 30.0f;
	switch (RareLevel)
	{
	case EItemRareLevel::EIRL_Normal:
		ItemBuffValue = 1.2f;
		break;
	case EItemRareLevel::EIRL_Rare:
		ItemBuffValue = 1.4f;
		break;
	case EItemRareLevel::EIRL_Legend:
		ItemBuffValue = 1.6f;
		break;
	default:
		break;
	}
}

UItem_Team_Power::~UItem_Team_Power()
{
}

void UItem_Team_Power::DoItemEffect(ASkyscraperCharacter* UsedCharacter)
{
	UItemObject::DoItemEffect(UsedCharacter);

	UE_LOG(LogTemp, Warning, TEXT("Item_Team_Power - DoItemEffect"));
	UsedCharacter->SetPowerBuffValue(ItemBuffValue, ItemBuffTime);

	{ // UsedCharacter 의 팀에게도 적용시키기

	}
}
