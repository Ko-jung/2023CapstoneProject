// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item_Root.h"
#include "Item_Team_Power.generated.h"

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API AItem_Team_Power : public AItem_Root
{
	GENERATED_BODY()
	// ������ ����� Ÿ�� ĳ����
	UPROPERTY()
	ASkyscraperCharacter* TargetCharacter;

	UPROPERTY(EditAnywhere)
		float ItemPowerBuffValue = 1.2f;



protected:
	// ������ ȿ�� �Լ�
	virtual void DoItemEffect(ASkyscraperCharacter* ItemUsedCharacter) override;

public:
	// SpawnActorDeferred �� ��ȯ�� �� �� �ʱ�ȭ ���� �Լ�
	void Initialize(float fPowerBuffValue);
};
