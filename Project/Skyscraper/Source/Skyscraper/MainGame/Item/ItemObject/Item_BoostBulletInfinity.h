#pragma once
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemObject.h"
#include "Skyscraper/Enum/EItemRareLevel.h"

/**
 *
 */
class SKYSCRAPER_API Item_BoostBulletInfinity : public ItemObject
{
public:
	Item_BoostBulletInfinity();
	Item_BoostBulletInfinity(EItemRareLevel RareLevel);
	virtual ~Item_BoostBulletInfinity() override;

	virtual void DoItemEffect(ASkyscraperCharacter* UsedCharacter) override;
};


