// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Packet.h"
#include <concurrent_queue.h>
#include <atomic>

#define MAXPLAYER 6

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
	virtual void PushQueue(Packet* etc);

	// Called by Gamemode thread
	virtual void ProcessFunc() {};

	void Send(const Packet* p, const int pSize);

// Network Function
public:
	bool Connect(const char* ip, int port);
	void SetOwnSerialNum(int serial);
	int GetSerialNum() { return SerialNum; }
	bool GetIsConnected();

protected:
	concurrency::concurrent_queue<Packet*> FuncQueue;
	//concurrency::concurrent_queue<Packet*> PositionQueue;
	class NetworkManager* m_Socket;

	int SerialNum;

	//bool IsConnectToLobby;
};
