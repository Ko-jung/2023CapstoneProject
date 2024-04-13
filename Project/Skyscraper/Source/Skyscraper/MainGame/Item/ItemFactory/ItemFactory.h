// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skyscraper/Enum/EItemEffect.h"
#include "Skyscraper/Enum/EItemRareLevel.h"

class ItemObject;

class SKYSCRAPER_API ItemFactory
{
public:
	ItemFactory();
	~ItemFactory();
	// 아이템을 생성 후 반환하는 함수
	static ItemObject* CreateItem(EItemEffect ItemEffectType, EItemRareLevel RareLevel);
};
