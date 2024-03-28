// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetworkGameMode.h"
#include "MainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API AMainGameMode : public ANetworkGameMode
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = "Characters")
	TSubclassOf<class ASkyscraperCharacter> AssassinCharacter;
	UPROPERTY(EditDefaultsOnly, Category = "Characters")
	TSubclassOf<class ASkyscraperCharacter> BoomerangCharacter;
	UPROPERTY(EditDefaultsOnly, Category = "Characters")
	TSubclassOf<class ASkyscraperCharacter> DetectionCharacter;
	UPROPERTY(EditDefaultsOnly, Category = "Characters")
	TSubclassOf<class ASkyscraperCharacter> ElectricCharacter;
	UPROPERTY(EditDefaultsOnly, Category = "Characters")
	TSubclassOf<class ASkyscraperCharacter> ShieldCharacter;
	UPROPERTY(EditDefaultsOnly, Category = "Characters")
	TSubclassOf<class ASkyscraperCharacter> WindCharacter;

private:
	TArray<ASkyscraperCharacter*> Characters;
};
