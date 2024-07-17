// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemObject.h"
#include "Item_GravityLow.generated.h"


/**
 * 
 */
UCLASS()
class SKYSCRAPER_API UItem_GravityLow : public UItemObject
{
	GENERATED_BODY()
public:
	UItem_GravityLow();
	virtual ~UItem_GravityLow() override;

	virtual void DoItemEffect(ASkyscraperCharacter* UsedCharacter) override;

protected:
private:

public:
protected:
	bool bGravityLow;

private:

};
