// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainRangeComponent.h"
#include "RifleComponent.generated.h"

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API URifleComponent : public UMainRangeComponent
{
	GENERATED_BODY()

public:
	URifleComponent();
protected:
	virtual void BeginPlay() override;
};
