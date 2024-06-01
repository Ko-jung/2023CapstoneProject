// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainRangeComponent.h"
#include "RPGComponent.generated.h"

class ARPGBullet;
/**
 * 
 */
UCLASS()
class SKYSCRAPER_API URPGComponent : public UMainRangeComponent
{
	GENERATED_BODY()

	TSubclassOf<ARPGBullet> RPGBulletBPClass;
public:
	URPGComponent();

	virtual void Fire(float fBaseDamage) override;
	virtual void SetInitialValue() override;
};
