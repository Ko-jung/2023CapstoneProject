// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skyscraper/Enum/EItemRareLevel.h"
#include "ItemObject.generated.h"

class ASkyscraperCharacter;
/**
 * 
 */
UCLASS()
class SKYSCRAPER_API UItemObject : public UObject
{
	GENERATED_BODY()


protected:
	float ItemBuffTime = 0.0f;

	// 버프 수치에 대한 변수
	// Team 버프 내에서 사용되며, 각 버프 내에 클래스에서 상세 설명 작성 (Item_Team_XXX)
	float ItemBuffValue = 0.0f;

public:
	UItemObject();

	UFUNCTION()
		virtual void SetItemRare(EItemRareLevel RareLevel);

	virtual void DoItemEffect(ASkyscraperCharacter* UsedCharacter);
};
