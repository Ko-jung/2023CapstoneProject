#pragma once
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemObject.h"
#include "Skyscraper/Enum/EItemRareLevel.h"

/**
 *
 */
class SKYSCRAPER_API Item_Team_Power : public ItemObject
{
	// ItemObject 내 버프 ItemBuffValue
	// 1단계 - 20%증가 / 2단계 - 40%증가 / 3단계 60% 증가 로,
	// 1단계 - 1.2f / 2단계 - 1.4f / 3단계 - 1.6f의 값을 가짐

public:
	Item_Team_Power();
	Item_Team_Power(EItemRareLevel RareLevel);
	virtual ~Item_Team_Power() override;

	virtual void DoItemEffect(ASkyscraperCharacter* UsedCharacter) override;
};


