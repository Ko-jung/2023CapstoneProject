// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainMeleeComponent.h"
#include "GreatSwordComponent.generated.h"

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API UGreatSwordComponent : public UMainMeleeComponent
{
	GENERATED_BODY()
public:
	UGreatSwordComponent();
protected:
	virtual void BeginPlay() override;
};
