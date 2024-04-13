#pragma once
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemObject.h"
#include "Skyscraper/Enum/EItemRareLevel.h"

/**
 *
 */
class SKYSCRAPER_API Item_Team_PlusHealth : public ItemObject
{
	// ItemObject �� ���� ItemBuffValue
	// 1�ܰ� - 25%���� / 2�ܰ� - 50%���� / 3�ܰ� 100% ���� ��,
	// 1�ܰ� - 0.25f / 2�ܰ� - 0.5f / 3�ܰ� - 1.0f�� ���� ����

public:
	Item_Team_PlusHealth();
	Item_Team_PlusHealth(EItemRareLevel RareLevel);
	virtual ~Item_Team_PlusHealth() override;

	virtual void DoItemEffect(ASkyscraperCharacter* UsedCharacter) override;
};


