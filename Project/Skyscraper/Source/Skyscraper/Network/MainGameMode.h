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

	void GoToLobby();

	void SpawnCharacter(int TargetSerialNum);
	void UpdateUI(float Deltatime);

	void SetPlayerPosition(PPlayerPosition PlayerPosition);
	void ProcessSpawnObject(PSpawnObject PSO);
	void ProcessChangedCharacterState(PChangedPlayerState* PCPS);
	void ProcessBuildingInfo(PBuildingInfo* PBI);
	void ProcessTileDrop(PTileDrop PTD);
	void ProcessSpawnItem(PSpawnItem PSI);
	void ProcessUseItem(PUseItem PUI);
	void ProcessGetItem(PGetItem PGI);
	void ProcessBreakObject(PBreakObject PBO);
	void ProcessRemoveObject(PRemoveObject PRO);
	void ProcessSkillInteract(PSkillInteract PKI);
	void ProcessDetecting(const uint8 DetectedSerial);

	void GetHexagonTileOnLevel();
	void GetWindowsOnLevel();
	int GetWindowsIndex(const UPrimitiveComponent* Target);
	//UStaticMeshComponent* GetStaticMeshComponentByLocation(FVector Location, EBreakType BreakType);

	void SendPlayerLocation();
	void SendPlayerSwapWeaponInfo();
	void SendSkillActorSpawn(const AActor* Sender, ESkillActor SkillActor, FVector SpawnLocation, FVector ForwardVec);
	void SendAnimMontageStatus(const AActor* Sender, ECharacterAnimMontage eAnimMontage, int Section);
	void SendStunDown(const AActor* Sender, const AActor* Target, const FVector& Dirction, bool IsStun = false, float StunTime = 0.f);
	void SendGetItem(const AActor* Sender, const AActor* Item);
	void SendBreakObject(const AActor* Sender, const UPrimitiveComponent* BreakTarget, EObjectType BreakType);
	bool SendUseItem(const AActor* Sender, uint8 Effect, uint8 RareLevel);
	bool SendTakeDamage(AActor* Sender, AActor* Target);

	UFUNCTION(BlueprintCallable)
	void SendDetecting(AActor* Sender, AActor* Target);
	
	UFUNCTION(BlueprintCallable)
	void SendRemoveSkillActor(AActor* TargetActor);

	//UFUNCTION(BlueprintCallable)
	//void RemoveSkillActor(AActor* TargetActor);

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

	 UFUNCTION(Exec)
	 void RequestTileDrop();
	 UFUNCTION(Exec)
	 void RequestSpawnItem();
	 UFUNCTION(Exec)
	 void RequestFinishGame();

protected:
	TArray<ASkyscraperCharacter*> Characters;
	TArray<PPlayerSelectInfo*> PlayerSelectInfo;

	TMap<WORD, AActor*> SkillActors;
	WORD SkillActorSerialNum;

	class AHexagonTile* HexagonTile;

	enum class ETEAM {A, B};
	int KillCount[2] = { 0, };
	FVector SpawnLoction[2];
	FName TeamName[2];

	float TileDropTimer;
	int TileDropLevel;

	class ASkyscraperPlayerController* PlayerController;

	TArray<UStaticMeshComponent*> WindowMeshComponents;
};
