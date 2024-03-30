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
	ESETTIMER,
	ESTARTGAME,

	//ESERVERCLOSE,
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
	virtual void PushQueue(EFunction e, Packet* etc);

	// Called by Gamemode thread
	virtual void ProcessFunc() {};

	void Send(const Packet* p, const int pSize);

// Network Function
public:
	void SetOwnSerialNum(int serial);
	int GetSerialNum() { return SerialNum; }

protected:
	concurrency::concurrent_queue<std::pair<EFunction, Packet*>> FuncQueue;
	class NetworkManager* m_Socket;

	bool bIsConnected;
	int SerialNum;
};
