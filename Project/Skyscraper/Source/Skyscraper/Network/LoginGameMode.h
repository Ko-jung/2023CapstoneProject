// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetworkGameMode.h"
#include "LoginGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API ALoginGameMode : public ANetworkGameMode
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
