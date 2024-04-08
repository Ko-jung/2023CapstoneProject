// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetworkGameMode.h"
#include "MainGameMode.generated.h"

class ASkyscraperCharacter;

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

	virtual void ProcessFunc() override;
	void SetPlayerPosition(PPlayerPosition PlayerPosition);
	void SendPlayerLocation();

	//UFUNCTION(BlueprintNativeEvent)
	//void SpawnCharactersUsingSelectInfo(TSubclassOf<class ASkyscraperCharacter> Class, FVector location);

	UFUNCTION(BlueprintCallable)
	void Test_TakeDamage(int DamageType);
	UFUNCTION(BlueprintCallable)
	void Test_TakeDamageACharacter(ASkyscraperCharacter* character);

	UPROPERTY(EditDefaultsOnly, Category = "Characters")
	TSubclassOf<ASkyscraperCharacter> AssassinCharacter;
	UPROPERTY(EditDefaultsOnly, Category = "Characters")
	TSubclassOf<ASkyscraperCharacter> BoomerangCharacter;
	UPROPERTY(EditDefaultsOnly, Category = "Characters")
	TSubclassOf<ASkyscraperCharacter> DetectionCharacter;
	UPROPERTY(EditDefaultsOnly, Category = "Characters")
	TSubclassOf<ASkyscraperCharacter> ElectricCharacter;
	UPROPERTY(EditDefaultsOnly, Category = "Characters")
	TSubclassOf<ASkyscraperCharacter> ShieldCharacter;
	UPROPERTY(EditDefaultsOnly, Category = "Characters")
	TSubclassOf<ASkyscraperCharacter> WindCharacter;

private:
	TArray<ASkyscraperCharacter*> Characters;
};
