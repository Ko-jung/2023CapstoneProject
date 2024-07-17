// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemFactory.h"

#include "Skyscraper/MainGame/Item/ItemObject/Item_BoostBulletInfinity.h"
#include "Skyscraper/MainGame/Item/ItemObject/Item_GodMode.h"
#include "Skyscraper/MainGame/Item/ItemObject/Item_GravityLow.h"
#include "Skyscraper/MainGame/Item/ItemObject/Item_GravityHigh.h"
#include "Skyscraper/MainGame/Item/ItemObject/Item_Team_PlusHealth.h"
#include "Skyscraper/MainGame/Item/ItemObject/Item_Team_Power.h"
#include "Skyscraper/MainGame/Item/ItemObject/Item_Team_Speed.h"
#include "Skyscraper/MainGame/Item/ItemObject/Item_TileBreak.h"

UItemFactory::UItemFactory()
{
}

UItemFactory::~UItemFactory()
{
}

UItemObject* UItemFactory::CreateItem(EItemEffect ItemEffectType, EItemRareLevel RareLevel)
{
	UItemObject* Object = nullptr;

	// EItemEffect 에 맞는 아이템 생성
	switch (ItemEffectType)
	{
	case EItemEffect::EIE_Single_BoostBulletInfinity:
		Object = NewObject<UItem_BoostBulletInfinity>(); // UItem_BoostBulletInfinity(RareLevel);
		break;

	case EItemEffect::EIE_Single_GodMode:
		Object = NewObject<UItem_GodMode>();
		break;

	case EItemEffect::EIE_Team_PlusHealth:
		Object = NewObject<UItem_Team_PlusHealth>();
		break;

	case EItemEffect::EIE_Team_Power:
		Object = NewObject<UItem_Team_Power>();
		break;

	case EItemEffect::EIE_Team_Speed:
		Object = NewObject<UItem_Team_Speed>();
		break;

	case EItemEffect::EIE_Gravity_Up:
		Object = NewObject<UItem_GravityHigh>();
		break;

	case EItemEffect::EIE_Gravity_Down:
		Object = NewObject<UItem_GravityLow>();
		break;

	case EItemEffect::EIE_Tile_Break:
		Object = NewObject<UItem_TileBreak>();
		break;

	default:
		break;
	}

	if(Object)
	{
		Object->SetItemRare(RareLevel);
	}

	UE_LOG(LogTemp, Warning, TEXT("ItemFactory - Create item and return"));
	return Object;
}
