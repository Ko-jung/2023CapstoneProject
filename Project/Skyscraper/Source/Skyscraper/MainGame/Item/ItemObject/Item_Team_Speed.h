#pragma once
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemObject.h"
#include "Skyscraper/Enum/EItemRareLevel.h"

/**
 *
 */
class SKYSCRAPER_API Item_Team_Speed : public ItemObject
{
	// ItemObject 내 버프 ItemBuffValue
	// 1단계 - 25%증가 / 2단계 - 50%증가 / 3단계 100% 증가 로,
	// 1단계 - 1.25f / 2단계 - 1.5f / 3단계 - 2.0f의 값을 가짐

public:
	Item_Team_Speed();
	Item_Team_Speed(EItemRareLevel RareLevel);
	virtual ~Item_Team_Speed() override;

	virtual void DoItemEffect(ASkyscraperCharacter* UsedCharacter) override;
};


