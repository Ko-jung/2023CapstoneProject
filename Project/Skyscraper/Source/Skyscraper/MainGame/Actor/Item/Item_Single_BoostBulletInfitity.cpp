// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Single_BoostBulletInfitity.h"

#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "Skyscraper/MainGame/Component/Combat/CombatSystemComponent.h"
#include "Skyscraper/MainGame/Component/Combat/Range/MainRangeComponent.h"
#include "Skyscraper/MainGame/Component/Jetpack/JetpackComponent.h"

void AItem_Single_BoostBulletInfitity::DoItemEffect(ASkyscraperCharacter* ItemUsedCharacter)
{
	TargetCharacter = ItemUsedCharacter;
	TargetCharacter->CombatSystemComponent->GetRangeComponent()->ActivateBulletInfinity(InfinityTime);
	TargetCharacter->JetpackComponent->ActivateBoostGaugeInfinity(InfinityTime);

	Super::DoItemEffect(ItemUsedCharacter);
}

void AItem_Single_BoostBulletInfitity::Initialize(float fGetInfinityTime)
{
	InfinityTime = fGetInfinityTime;
}
