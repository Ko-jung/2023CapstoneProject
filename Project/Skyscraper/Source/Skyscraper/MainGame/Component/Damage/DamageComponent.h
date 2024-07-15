// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DamageComponent.generated.h"

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API UDamageComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UDamageComponent();

	UFUNCTION(BlueprintCallable)
		void InitializeDamage(int Damage);
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:

public:

protected:
	UPROPERTY()
		FTimerHandle DamageLifeTimerHandle;
	int Damage;
	int LengthOfDamage;

	float MaxLifeTime;
	double StartTime;


private:

};
