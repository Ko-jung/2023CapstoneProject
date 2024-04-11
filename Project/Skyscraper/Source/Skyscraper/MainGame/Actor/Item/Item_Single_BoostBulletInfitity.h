// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item_Root.h"
#include "Item_Single_BoostBulletInfitity.generated.h"

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API AItem_Single_BoostBulletInfitity : public AItem_Root
{
	GENERATED_BODY()

	// ������ ����� Ÿ�� ĳ����
	UPROPERTY()
	ASkyscraperCharacter* TargetCharacter;

	// źâ / �ν��� ������ ���� �ð�
	UPROPERTY(EditAnywhere)
		float InfinityTime = 10.0f;



protected:
	// ������ ȿ�� �Լ�
	virtual void DoItemEffect(ASkyscraperCharacter* ItemUsedCharacter) override;

public:
	// SpawnActorDeferred �� ��ȯ�� �� �� �ʱ�ȭ ���� �Լ�
	void Initialize(float fGetInfinityTime);
};
