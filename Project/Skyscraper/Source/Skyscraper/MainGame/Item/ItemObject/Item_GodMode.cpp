// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_GodMode.h"

#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "Skyscraper/MainGame/Component/Health/HealthComponent.h"

UItem_GodMode::UItem_GodMode()
{
	
}

void UItem_GodMode::SetItemRare(EItemRareLevel RareLevel)
{
	UItemObject::SetItemRare(RareLevel);
	switch (RareLevel)
	{
	case EItemRareLevel::EIRL_Normal:
		ItemBuffTime = 5.0f;
		break;
	case EItemRareLevel::EIRL_Rare:
		ItemBuffTime = 10.0f;
		break;
	case EItemRareLevel::EIRL_Legend:
		ItemBuffTime = 15.0f;
		break;
	default:
		break;
	}
}

UItem_GodMode::~UItem_GodMode()
{
}

void UItem_GodMode::DoItemEffect(ASkyscraperCharacter* UsedCharacter)
{
	UItemObject::DoItemEffect(UsedCharacter);

	UE_LOG(LogTemp, Warning, TEXT("Item_GodMode - DoItemEffect"));
	UsedCharacter->HealthComponent->ActivateGodMode(ItemBuffTime);
}
