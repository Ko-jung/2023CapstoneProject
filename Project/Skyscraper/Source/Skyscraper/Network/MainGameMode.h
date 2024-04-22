// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetworkGameMode.h"
#include "../Enum/ESkillActor.h"
#include "Skyscraper/Enum/ECharacterAnimMontage.h"
#include "../Enum/ECharacterAnimMontage.h"

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
	// void ProcessPosition();

	ECharacterAnimMontage GetNonPacketAnimMontage(EAnimMontage eAnimMontage);

	void SetPlayerPosition(PPlayerPosition PlayerPosition);
	void ProcessSpawnObject(PSpawnObject PSO);

	void SendPlayerLocation();
	void SendSkillActorSpawn(ESkillActor SkillActor, FVector SpawnLocation, FVector ForwardVec);
	void SendAnimMontageStatus(ECharacterAnimMontage eAnimMontage);

	// UE5 Function Code
	float CalculateDirection(const FVector& Velocity, const FRotator& BaseRotation);

	//UFUNCTION(BlueprintNativeEvent)
	//void SpawnCharactersUsingSelectInfo(TSubclassOf<class ASkyscraperCharacter> Class, FVector location);

	UFUNCTION(BlueprintNativeEvent)
	void SpawnSkillActor(ESkillActor SkillActor, FVector SpawnLocation, FVector ForwardVec, ASkyscraperCharacter* Spawner, FName Team);

	UFUNCTION(BlueprintCallable)
	void Test_TakeDamage(int DamageType);

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

	UPROPERTY(EditDefaultsOnly, Category = "AICharacters")
	TSubclassOf<ASkyscraperCharacter> AIAssassinCharacter;
	UPROPERTY(EditDefaultsOnly, Category = "AICharacters")
	TSubclassOf<ASkyscraperCharacter> AIBoomerangCharacter;
	UPROPERTY(EditDefaultsOnly, Category = "AICharacters")
	TSubclassOf<ASkyscraperCharacter> AIDetectionCharacter;
	UPROPERTY(EditDefaultsOnly, Category = "AICharacters")
	TSubclassOf<ASkyscraperCharacter> AIElectricCharacter;
	UPROPERTY(EditDefaultsOnly, Category = "AICharacters")
	TSubclassOf<ASkyscraperCharacter> AIShieldCharacter;
	UPROPERTY(EditDefaultsOnly, Category = "AICharacters")
	TSubclassOf<ASkyscraperCharacter> AIWindCharacter;

private:
	//ASkyscraperCharacter* PossessCharacter;
	TArray<ASkyscraperCharacter*> Characters;
};
