#pragma once
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemObject.h"
#include "Skyscraper/Enum/EItemRareLevel.h"

/**
 *
 */
class SKYSCRAPER_API Item_Team_Speed : public ItemObject
{
	// ItemObject �� ���� ItemBuffValue
	// 1�ܰ� - 25%���� / 2�ܰ� - 50%���� / 3�ܰ� 100% ���� ��,
	// 1�ܰ� - 1.25f / 2�ܰ� - 1.5f / 3�ܰ� - 2.0f�� ���� ����

public:
	Item_Team_Speed();
	Item_Team_Speed(EItemRareLevel RareLevel);
	virtual ~Item_Team_Speed() override;

	virtual void DoItemEffect(ASkyscraperCharacter* UsedCharacter) override;
};


