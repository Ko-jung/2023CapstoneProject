// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skyscraper/Enum/EItemEffect.h"
#include "Skyscraper/Enum/EItemRareLevel.h"

class ItemObject;

class SKYSCRAPER_API ItemFactory
{
public:
	ItemFactory();
	~ItemFactory();
	// �������� ���� �� ��ȯ�ϴ� �Լ�
	static ItemObject* CreateItem(EItemEffect ItemEffectType, EItemRareLevel RareLevel);
};
