// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item_GravityLow.h"

/**
 * 
 */
class SKYSCRAPER_API Item_GravityHigh : public ItemObject
{
public:
	Item_GravityHigh();
	virtual ~Item_GravityHigh() override;

	virtual void DoItemEffect(ASkyscraperCharacter* UsedCharacter) override;

protected:
private:

public:
protected:
	bool bGravityLow;

private:
};
