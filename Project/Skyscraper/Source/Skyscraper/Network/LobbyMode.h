// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetworkGameMode.h"

#include "LobbyMode.generated.h"

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API ALobbyMode : public ANetworkGameMode
{
	GENERATED_BODY()
	
public:
	ALobbyMode();

	virtual void BeginPlay() override;
	virtual void Tick(float) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void ProcessFunc();

	void ProcessPlayerIDs(const PPlayerID& IDs);

	UFUNCTION(Exec)
	void Ready();

	void Ready(bool IsReady);

private:
	bool IsReady;

	UPROPERTY()
	TSubclassOf<class ULobbyWidget> LobbyWidgetClass;

	UPROPERTY()
	ULobbyWidget* LobbyWidget;
};
