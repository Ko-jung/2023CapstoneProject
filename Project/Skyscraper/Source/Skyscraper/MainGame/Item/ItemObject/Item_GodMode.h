#pragma once
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemObject.h"
#include "Skyscraper/Enum/EItemRareLevel.h"

/**
 *
 */
class SKYSCRAPER_API Item_GodMode : public ItemObject
{
public:
	Item_GodMode();
	Item_GodMode(EItemRareLevel RareLevel);
	virtual ~Item_GodMode() override;

	virtual void DoItemEffect(ASkyscraperCharacter* UsedCharacter) override;
};


