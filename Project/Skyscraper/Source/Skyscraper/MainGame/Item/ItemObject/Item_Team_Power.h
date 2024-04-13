#pragma once
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemObject.h"
#include "Skyscraper/Enum/EItemRareLevel.h"

/**
 *
 */
class SKYSCRAPER_API Item_Team_Power : public ItemObject
{
	// ItemObject �� ���� ItemBuffValue
	// 1�ܰ� - 20%���� / 2�ܰ� - 40%���� / 3�ܰ� 60% ���� ��,
	// 1�ܰ� - 1.2f / 2�ܰ� - 1.4f / 3�ܰ� - 1.6f�� ���� ����

public:
	Item_Team_Power();
	Item_Team_Power(EItemRareLevel RareLevel);
	virtual ~Item_Team_Power() override;

	virtual void DoItemEffect(ASkyscraperCharacter* UsedCharacter) override;
};


