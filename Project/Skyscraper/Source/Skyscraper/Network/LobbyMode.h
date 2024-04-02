// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LobbyMode.generated.h"

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API ALobbyMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	class NetworkManager* m_Socket;

	bool bIsConnected;
	int SerialNum;
};
