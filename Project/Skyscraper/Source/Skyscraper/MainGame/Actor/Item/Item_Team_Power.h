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
	// 아이템 사용한 타겟 캐릭터
	UPROPERTY()
	ASkyscraperCharacter* TargetCharacter;

	UPROPERTY(EditAnywhere)
		float ItemPowerBuffValue = 1.2f;



protected:
	// 아이템 효과 함수
	virtual void DoItemEffect(ASkyscraperCharacter* ItemUsedCharacter) override;

public:
	// SpawnActorDeferred 로 소환할 때 값 초기화 전용 함수
	void Initialize(float fPowerBuffValue);
};
