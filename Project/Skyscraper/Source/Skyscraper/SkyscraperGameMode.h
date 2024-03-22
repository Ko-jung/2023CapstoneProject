// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NetworkGameMode.h"
#include "SkyscraperGameMode.generated.h"

UCLASS(minimalapi)
class ASkyscraperGameMode : public ANetworkGameMode
{
	GENERATED_BODY()

public:
	ASkyscraperGameMode();


	virtual void BeginPlay() override;
	virtual void Tick(float) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};



