// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainMeleeComponent.h"
#include "DaggerComponent.generated.h"

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API UDaggerComponent : public UMainMeleeComponent
{
	GENERATED_BODY()

	UPROPERTY()
		FName SubWeaponSocketName;
public:
	UDaggerComponent();

protected:
	virtual void BeginPlay() override;

	// 무기 웨폰 skeletal mesh의 visible을 변경해주는 함수
	virtual void SetWeaponHiddenInGame(bool bNewHidden) const override;

	virtual void SetInitialValue() override;
};
