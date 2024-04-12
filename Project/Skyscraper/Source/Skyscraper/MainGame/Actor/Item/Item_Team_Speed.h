// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item_Root.h"
#include "Item_Team_Speed.generated.h"

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API AItem_Team_Speed : public AItem_Root
{
	GENERATED_BODY()

	// ������ ����� Ÿ�� ĳ����
	UPROPERTY()
	ASkyscraperCharacter* TargetCharacter;

	UPROPERTY(EditAnywhere)
		float ItemSpeedBuffValue = 1.25f;



protected:
	// ������ ȿ�� �Լ�
	virtual void DoItemEffect(ASkyscraperCharacter* ItemUsedCharacter) override;

public:
	// SpawnActorDeferred �� ��ȯ�� �� �� �ʱ�ȭ ���� �Լ�
	void Initialize(float fSpeedBuffValue);
};
