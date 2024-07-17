// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skyscraper/Enum/EItemEffect.h"
#include "Skyscraper/Enum/EItemRareLevel.h"
#include "ItemFactory.generated.h"

class UItemObject;

UCLASS()
class SKYSCRAPER_API UItemFactory : public UObject
{
	GENERATED_BODY()


public:
	UItemFactory();
	~UItemFactory();
	// 아이템을 생성 후 반환하는 함수
	static UItemObject* CreateItem(EItemEffect ItemEffectType, EItemRareLevel RareLevel);
};
