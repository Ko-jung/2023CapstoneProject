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

	// 버프 수치에 대한 변수
	// Team 버프 내에서 사용되며, 각 버프 내에 클래스에서 상세 설명 작성 (Item_Team_XXX)
	float ItemBuffValue = 0.0f;

public:
	ItemObject();
	virtual ~ItemObject();

	virtual void DoItemEffect(ASkyscraperCharacter* UsedCharacter);
};
