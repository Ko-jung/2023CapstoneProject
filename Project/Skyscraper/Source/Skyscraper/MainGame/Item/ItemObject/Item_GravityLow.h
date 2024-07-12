// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemObject.h"
#include "Skyscraper/Enum/EItemRareLevel.h"

/**
 * 
 */
class SKYSCRAPER_API Item_GravityLow : public ItemObject
{
public:
	Item_GravityLow();
	virtual ~Item_GravityLow() override;

	virtual void DoItemEffect(ASkyscraperCharacter* UsedCharacter) override;

protected:
private:

public:
protected:
	bool bGravityLow;

private:

};
