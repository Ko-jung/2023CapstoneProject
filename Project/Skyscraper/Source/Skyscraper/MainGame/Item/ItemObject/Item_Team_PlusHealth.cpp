// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Team_PlusHealth.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "Skyscraper/MainGame/Component/Health/HealthComponent.h"

UItem_Team_PlusHealth::UItem_Team_PlusHealth()
{
}

void UItem_Team_PlusHealth::SetItemRare(EItemRareLevel RareLevel)
{
	UItemObject::SetItemRare(RareLevel);
	ItemBuffTime = 20.0f;
	switch (RareLevel)
	{
	case EItemRareLevel::EIRL_Normal:
		ItemBuffValue = 0.25f;
		break;
	case EItemRareLevel::EIRL_Rare:
		ItemBuffValue = 0.5f;
		break;
	case EItemRareLevel::EIRL_Legend:
		ItemBuffValue = 1.0f;
		break;
	default:
		break;
	}
}

UItem_Team_PlusHealth::~UItem_Team_PlusHealth()
{
}

void UItem_Team_PlusHealth::DoItemEffect(ASkyscraperCharacter* UsedCharacter)
{
	UItemObject::DoItemEffect(UsedCharacter);

	UE_LOG(LogTemp, Warning, TEXT("Item_Team_PlusHealth - DoItemEffect"));
	UsedCharacter->HealthComponent->ActivatePlusHealthBuff(ItemBuffValue, ItemBuffTime);

	{ // UsedCharacter 의 팀에게도 적용시키기

	}

}
