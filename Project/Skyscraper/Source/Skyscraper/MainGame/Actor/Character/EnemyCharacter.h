// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkyscraperCharacter.h"
#include "EnemyCharacter.generated.h"

class URifleComponent;

UCLASS()
class SKYSCRAPER_API AEnemyCharacter : public ASkyscraperCharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();
	


protected:
	virtual void BeginPlay() override;

private:
	// == Timer Handle Variable And Function
	FTimerHandle EnemyFireTimerHandle;

	UFUNCTION()
		void FirePer1Sec();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
		UMainRangeComponent* RangeComponent;
};
