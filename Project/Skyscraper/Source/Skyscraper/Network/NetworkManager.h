// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "CoreMinimal.h"
#include "HAL/Runnable.h"

// winsock2 ����� ���� �Ʒ� �ڸ�Ʈ �߰�
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <map>
#include <queue>

#include "Packet.h"

#define	MAX_BUFFER				255
#define GAME_SERVER_PORT		9000
#define LOBBY_SERVER_PORT		9001
#define GAME_SERVER_IP			"1.242.205.234"
#define LOBBY_SERVER_IP			"1.242.205.234"

class ANetworkGameMode;

enum class ENetworkState
{
	Login,
	Lobby,
	SelectGame,
	MainGame
};

/**
 * 
 */
class SKYSCRAPER_API NetworkManager : public FRunnable
{
public:
	NetworkManager();
	~NetworkManager();

// Socket Fuction
public:
	bool InitializeManager();
	bool InitializeProperty();
	bool InitializeSocket();
	bool InitSocket();
	bool Connect(const char* pszIP, int nPort);
	void Disconnect();

	void ProcessRecv(Packet* p);
	void ProcessRecvFromLogin(Packet* p);
	void ProcessRecvFromLobby(Packet* p);
	void ProcessRecvFromSelectGame(Packet* p);
	void ProcessRecvFromMainGame(Packet* p);
	void Send(const Packet* packet, int packetsize);

// FRunnable Function
public:
	FRunnableThread* Thread;
	FThreadSafeCounter StopTaskCounter;
	//bool bStopSwich;

	bool StartListen();
	void StopListen();

	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;

public:
	//void SetGamemode(ANetworkGameMode* gamemode, ENetworkState state);
	void SetGamemode(ANetworkGameMode* gamemode);
	void SetState(ENetworkState s) { State = s; }

	const int& GetSerialNum() { return SerialNum; }
	const bool& GetIsConnected() { return bIsConnected; };

	bool TryPush(Packet* p);

public:
	// Singleton
	static NetworkManager* Instance()
	{
		static NetworkManager Instance;
		return &Instance;
	}

private:
	SOCKET	m_ServerSocket;
	char 	m_sRecvBuffer[MAX_BUFFER];
	char 	m_sSendBuffer[MAX_BUFFER];

	ANetworkGameMode* Gamemode;
	bool bIsConnected;
	bool IsWSAInitialize;

	ENetworkState State;

	bool IsChangingGameMode;

	/// <summary>
	/// [0, 5]
	/// bIsConnected ? -1 : 0
	/// </summary>
	int SerialNum;

	// // pool Variable 고민해보기
	// std::queue<PSetTimer*> PSetTimerQueue;
	// std::queue<PPlayerSelectInfo*> PSetTimerQueue;
	// std::queue<PSetTimer*> PSetTimerQueue;

	int RemainDataLen;
};
