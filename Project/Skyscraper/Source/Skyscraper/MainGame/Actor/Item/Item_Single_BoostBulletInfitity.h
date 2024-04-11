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

	// 아이템 사용한 타겟 캐릭터
	UPROPERTY()
	ASkyscraperCharacter* TargetCharacter;

	// 탄창 / 부스터 무제한 지속 시간
	UPROPERTY(EditAnywhere)
		float InfinityTime = 10.0f;



protected:
	// 아이템 효과 함수
	virtual void DoItemEffect(ASkyscraperCharacter* ItemUsedCharacter) override;

public:
	// SpawnActorDeferred 로 소환할 때 값 초기화 전용 함수
	void Initialize(float fGetInfinityTime);
};
