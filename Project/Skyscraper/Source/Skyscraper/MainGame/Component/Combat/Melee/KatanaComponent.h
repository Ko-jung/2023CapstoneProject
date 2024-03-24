// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainMeleeComponent.h"
#include "KatanaComponent.generated.h"

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API UKatanaComponent : public UMainMeleeComponent
{
	GENERATED_BODY()
public:
	UKatanaComponent();
protected:
	virtual void BeginPlay() override;
};
