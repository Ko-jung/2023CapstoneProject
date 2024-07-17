// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "SkyscraperEngineSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API USkyscraperEngineSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION()
	USoundBase* GetSkyscraperSound(FName RowName) const;

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

private:

public:

protected:
	UPROPERTY()
		TObjectPtr<UDataTable> SoundDataTable;

private:
};
