// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyBasePawn.h"
#include "Tower.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class UDEMYSECTION05_API ATower : public AMyBasePawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	UPROPERTY(EditAnywhere,Category="Combat")
	float FireRange= 500.0f;

	ATank* Tank;

private:
	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.0f;
	void CheckFireCondition();

	bool InFireRange();
	
};
