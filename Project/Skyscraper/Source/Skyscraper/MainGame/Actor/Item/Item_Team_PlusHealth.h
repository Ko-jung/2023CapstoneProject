// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item_Root.h"
#include "Item_Team_PlusHealth.generated.h"

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API AItem_Team_PlusHealth : public AItem_Root
{
	GENERATED_BODY()

	// 아이템을 사용한 캐릭터
	UPROPERTY()
	ASkyscraperCharacter* TargetCharacter;

	UPROPERTY(EditAnywhere)
		float PlusHealthValue = 0.25f;



protected:
	// 아이템 효과 함수
	virtual void DoItemEffect(ASkyscraperCharacter* ItemUsedCharacter) override;

public:
	// SpawnActorDeferred 로 소환할 때 값 초기화 전용 함수
	void Initialize(float fPlusHealthValue);
};
