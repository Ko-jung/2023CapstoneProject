// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skyscraper/Enum/EItemRareLevel.h"

class ASkyscraperCharacter;
/**
 * 
 */
class SKYSCRAPER_API ItemObject
{
protected:
	float ItemBuffTime = 0.0f;

public:
	ItemObject();
	virtual ~ItemObject();

	virtual void DoItemEffect(ASkyscraperCharacter* UsedCharacter);
};
