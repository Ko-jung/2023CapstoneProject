#pragma once
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemObject.h"
#include "Skyscraper/Enum/EItemRareLevel.h"
#include "Item_GodMode.generated.h"

/**
 *
 */
UCLASS()
class SKYSCRAPER_API UItem_GodMode : public UItemObject
{
	GENERATED_BODY()
public:
	UItem_GodMode();
	
	virtual void SetItemRare(EItemRareLevel RareLevel) override;
	virtual ~UItem_GodMode() override;

	virtual void DoItemEffect(ASkyscraperCharacter* UsedCharacter) override;
};


