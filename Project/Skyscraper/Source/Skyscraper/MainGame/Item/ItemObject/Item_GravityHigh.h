// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item_GravityLow.h"
#include "Item_GravityHigh.generated.h"

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API UItem_GravityHigh : public UItemObject
{
	GENERATED_BODY()
public:
	UItem_GravityHigh();
	virtual ~UItem_GravityHigh() override;

	virtual void DoItemEffect(ASkyscraperCharacter* UsedCharacter) override;

protected:
private:

public:
protected:
	bool bGravityLow;

private:
};
