// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameMode.h"
#include "SkillSyncTestGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API ASkillSyncTestGameMode : public AMainGameMode
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void ProcessFunc();

	UPROPERTY(EditAnywhere)
	ECharacterSelect PlayerCharacter;
};
