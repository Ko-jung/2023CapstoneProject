// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputTriggers.h"
#include "DoubleTab_InputTrigger.generated.h"

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API UDoubleTab_InputTrigger : public UInputTriggerTimedBase
{
	GENERATED_BODY()
protected:
	virtual ETriggerState UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime) override;

public:
	// Double Tap Limit Time
	// TODO: Make it editable in option.
	UPROPERTY(EditAnywhere, Config, BlueprintReadWrite, Category = "Trigger Settings")
		float TimeLimit = 0.3f;

	UPROPERTY()
		float LastInputTime = 0.0f;
};
