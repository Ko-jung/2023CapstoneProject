// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetworkGameMode.h"
#include "../Enum/ESkillActor.h"
#include "Skyscraper/Enum/ECharacterAnimMontage.h"
#include "../Enum/ECharacterAnimMontage.h"
#include "../Enum/ECharacterSelect.h"

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
	 TMap<ECharacterSelect, TSubclassOf<ASkyscraperCharacter>> CharacterClass;
	 
	 UPROPERTY(EditDefaultsOnly, Category = "Characters")
	 TMap<ECharacterSelect, TSubclassOf<ASkyscraperCharacter>> AiCharacterClass;

private:
	//ASkyscraperCharacter* PossessCharacter;
	TArray<ASkyscraperCharacter*> Characters;
};
