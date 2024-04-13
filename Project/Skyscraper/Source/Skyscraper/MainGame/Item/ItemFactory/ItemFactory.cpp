// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemFactory.h"

#include "Skyscraper/MainGame/Item/ItemObject/Item_BoostBulletInfinity.h"
#include "Skyscraper/MainGame/Item/ItemObject/Item_GodMode.h"
#include "Skyscraper/MainGame/Item/ItemObject/Item_Team_PlusHealth.h"
#include "Skyscraper/MainGame/Item/ItemObject/Item_Team_Power.h"
#include "Skyscraper/MainGame/Item/ItemObject/Item_Team_Speed.h"

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
		Object = new Item_GodMode(RareLevel);
		break;

	case EItemEffect::EIE_Team_PlusHealth:
		Object = new Item_Team_PlusHealth(RareLevel);
		break;

	case EItemEffect::EIE_Team_Power:
		Object = new Item_Team_Power(RareLevel);
		break;

	case EItemEffect::EIE_Team_Speed:
		Object = new Item_Team_Speed(RareLevel);
		break;

	default:
		break;
	}

	UE_LOG(LogTemp, Warning, TEXT("ItemFactory - Create item and return"));
	return Object;
}
