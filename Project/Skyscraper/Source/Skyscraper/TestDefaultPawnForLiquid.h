// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "TestDefaultPawnForLiquid.generated.h"

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API ATestDefaultPawnForLiquid : public ADefaultPawn
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void Fire();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
