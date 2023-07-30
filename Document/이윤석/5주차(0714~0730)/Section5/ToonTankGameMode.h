// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTankGameMode.generated.h"

class ATank;
class AToonTanksPlayerController;
/**
 * 
 */
UCLASS()
class UDEMYSECTION05_API AToonTankGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
		void GameOver(bool bWonGame);
private:
	TObjectPtr<ATank> Tank;
	TObjectPtr<AToonTanksPlayerController> ToonTanksPlayerController;

	float StartDelay = 3.0f;

	void HandleGameStart();
};
