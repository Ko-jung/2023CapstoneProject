// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "../../Packet/Packet.h"
#include <concurrent_queue.h>

#define MAXPLAYER 6

enum EFunction
{
	ESPAWNPLAYER,
	EBPPOSSESS,
	EPLAYERTRANSFORM,
	EPLAYERSELECTINFO,
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
	virtual void PushQueue(EFunction e, Packet etc);

	// Called by Gamemode thread
	virtual void ProcessFunc() {};

// Network Function
public:
	void SetOwnSerialNum(int serial);

protected:
	concurrency::concurrent_queue<std::pair<EFunction, Packet>> FuncQueue;
	class NetworkManager* m_Socket;

	bool m_bIsConnected;
	int m_SerialNum;
};
