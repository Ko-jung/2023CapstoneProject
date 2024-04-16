// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkyscraperCharacter.h"
#include "MeleeEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API AMeleeEnemyCharacter : public ASkyscraperCharacter
{
	GENERATED_BODY()

public:
	AMeleeEnemyCharacter();

	UPROPERTY(EditAnywhere)
		float DoAttackDelay;
	UPROPERTY(EditAnywhere)
		EMeleeSelect MeleeSelect;

	UPROPERTY(EditAnywhere)
		float EnemyMaxHealth;
	
protected:
	virtual void BeginPlay() override;

private:
	// == Timer Handle Variable And Function
	FTimerHandle EnemyAttackTimerHandle;

	UFUNCTION()
		void MeleeEnemyAttack();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
		UMainMeleeComponent* MeleeComponent;
};
