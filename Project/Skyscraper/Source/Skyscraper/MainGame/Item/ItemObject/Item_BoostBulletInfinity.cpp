// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_BoostBulletInfinity.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "Skyscraper/MainGame/Component/Jetpack/JetpackComponent.h"
#include "Skyscraper/MainGame/Component/Combat/CombatSystemComponent.h"

UItem_BoostBulletInfinity::UItem_BoostBulletInfinity()
{
}

void UItem_BoostBulletInfinity::SetItemRare(EItemRareLevel RareLevel)
{
	UItemObject::SetItemRare(RareLevel);
	switch (RareLevel)
	{
	case EItemRareLevel::EIRL_Normal:
		ItemBuffTime = 10.0f;
		break;
	case EItemRareLevel::EIRL_Rare:
		ItemBuffTime = 20.0f;
		break;
	case EItemRareLevel::EIRL_Legend:
		ItemBuffTime = 30.0f;
		break;
	default:
		break;
	}
}

UItem_BoostBulletInfinity::~UItem_BoostBulletInfinity()
{
}


void UItem_BoostBulletInfinity::DoItemEffect(ASkyscraperCharacter* UsedCharacter)
{
	UItemObject::DoItemEffect(UsedCharacter);

	UE_LOG(LogTemp, Warning, TEXT("Item_boostBulletInfinity - DoItemEffect"));
	
	UsedCharacter->CombatSystemComponent->GetRangeComponent()->ActivateBulletInfinity(ItemBuffTime);
	UsedCharacter->JetpackComponent->ActivateBoostGaugeInfinity(ItemBuffTime);

}
