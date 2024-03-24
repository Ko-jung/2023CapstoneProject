// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// winsock2 ����� ���� �Ʒ� �ڸ�Ʈ �߰�
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <map>

#include "../../Packet/Packet.h"

#define	MAX_BUFFER		256
#define SERVER_PORT		8000
#define SERVER_IP		"127.0.0.1"

class ANetworkGameMode;

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
	bool InitSocket();
	bool Connect(const char* pszIP, int nPort);
	void Disconnect();

	void ProcessRecv(int packetType);

// FRunnable Function
public:
	FRunnableThread* Thread;
	FThreadSafeCounter StopTaskCounter;

	bool StartListen();
	void StopListen();

	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;

public:
	void SetGamemode(ANetworkGameMode* gamemode) { Gamemode = gamemode; };

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

	// [0, 5]
	int SerialNum;
};
