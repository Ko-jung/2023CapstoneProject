#pragma once
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemObject.h"
#include "Skyscraper/Enum/EItemRareLevel.h"
#include "Item_TileBreak.generated.h"

class UTileBreakItemWidget;
/**
 *
 */
UCLASS()
class SKYSCRAPER_API UItem_TileBreak : public UItemObject
{
	GENERATED_BODY()
public:
	UItem_TileBreak();
	
	virtual ~UItem_TileBreak() override;

	virtual void DoItemEffect(ASkyscraperCharacter* UsedCharacter) override;

protected:
	UPROPERTY()
		TSubclassOf<UUserWidget> WBP_TileBreakItemClass;
};


