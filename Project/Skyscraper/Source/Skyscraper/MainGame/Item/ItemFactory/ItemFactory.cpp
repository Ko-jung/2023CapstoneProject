// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemFactory.h"

#include "Skyscraper/MainGame/Item/ItemObject/Item_BoostBulletInfinity.h"

ItemFactory::ItemFactory()
{
}

ItemFactory::~ItemFactory()
{
}

ItemObject* ItemFactory::CreateItem(EItemEffect ItemEffectType, EItemRareLevel RareLevel)
{
	ItemObject* Object = nullptr;

	// EItemEffect 에 맞는 아이템 생성
	switch (ItemEffectType)
	{
	case EItemEffect::EIE_Single_BoostBulletInfinity:
		Object = new Item_BoostBulletInfinity(RareLevel);
		break;

	case EItemEffect::EIE_Single_GodMode:
		break;
	case EItemEffect::EIE_Team_PlusHealth:
		break;
	case EItemEffect::EIE_Team_Power:
		break;
	case EItemEffect::EIE_Team_Speed:
		break;
	default:
		break;
	}

	UE_LOG(LogTemp, Warning, TEXT("ItemFactory - Create item and return"));
	return Object;
}
