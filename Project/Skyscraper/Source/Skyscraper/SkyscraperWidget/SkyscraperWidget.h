// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkyscraperWidget.generated.h"

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API USkyscraperWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void PlayButtonOnClickSound();
};
