// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "../../Packet/Packet.h"
#include <concurrent_queue.h>

enum EFunction
{
	ESPAWNPLAYER,
	EBPPOSSESS,
	EPLAYERTRANSFORM,
};

#include "NetworkGameMode.generated.h"
/**
 * 
 */
UCLASS()
class SKYSCRAPER_API ANetworkGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Called by NetworkManager thread
	void PushQueue(EFunction e, Packet* etc);
	// Called by Gamemode thread
	void ProcessFunc();

private:
	concurrency::concurrent_queue<std::pair<EFunction, Packet*>> FuncQueue;
	class NetworkManager* m_Socket;
};
