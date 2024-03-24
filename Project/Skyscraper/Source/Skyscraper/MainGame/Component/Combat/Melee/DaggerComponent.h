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
public:
	UDaggerComponent();

protected:
	virtual void BeginPlay() override;
};
