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

	void SpawnCharacter(int TargetSerialNum);

	void SetPlayerPosition(PPlayerPosition PlayerPosition);
	void ProcessSpawnObject(PSpawnObject PSO);
	void ProcessChangedCharacterState(PChangedPlayerState* PCPS);
	void ProcessBuildingInfo(PBuildingInfo* PBI);
	void GetHexagonTileOnLevel();

	void SendPlayerLocation();
	void SendPlayerSwapWeaponInfo();
	void SendSkillActorSpawn(ESkillActor SkillActor, FVector SpawnLocation, FVector ForwardVec);
	void SendAnimMontageStatus(const AActor* Sender, ECharacterAnimMontage eAnimMontage);
	void SendTakeDamage(AActor* Sender, AActor* Target);
	void SendStunDown(const AActor* Sender, const AActor* Target, const FVector& Dirction, bool IsStun = false, float StunTime = 0.f);

	int GetIndex(const AActor* target);

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

	 UPROPERTY(EditAnywhere)
	 FVector TempSpawnLocation[5];

private:
	TArray<ASkyscraperCharacter*> Characters;
	TArray<PPlayerSelectInfo*> PlayerSelectInfo;

	class AHexagonTile* HexagonTile;

	enum class ETEAM {A, B};
	int KillCount[2] = { 0, };
	FVector SpawnLoction[2];
	FName TeamName[2];
};
