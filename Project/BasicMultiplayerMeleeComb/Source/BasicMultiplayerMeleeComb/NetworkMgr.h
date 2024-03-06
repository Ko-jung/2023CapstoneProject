// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HAL/Runnable.h"

// winsock2
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <map>

#include "../../Packet/Packet.h"

#define	MAX_BUFFER		512
#define SERVER_PORT		8000
#define SERVER_IP		"127.0.0.1"
#define MAX_CLIENTS		100

class ASocketController;

/**
 * 
 */
class BASICMULTIPLAYERMELEECOMB_API NetworkMgr : public FRunnable
{
public:
	NetworkMgr();
	~NetworkMgr();

	// Network Function (Packet)
public:
	void Send(int packetsize, Packet* packet);

	bool InitSocket();
	bool Connect(const char* pszIP, int nPort);
	void Disconnect();
	void SendPlayerInfo(FTransform transform, float speed);

public:

	// FRunnable virtual Variable & Function
	FRunnableThread* Thread;
	FThreadSafeCounter StopTaskCounter;

	// ������ ���� �� ����
	bool StartListen();
	void StopListen();

	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;

public:
	static NetworkMgr* Instance()
	{
		static NetworkMgr Instance;
		return &Instance;
	}

	void SetController(ASocketController* controller) { Controller = controller; }

private:
	SOCKET	m_ServerSocket;
	char 	m_sRecvBuffer[MAX_BUFFER];
	char 	m_sSendBuffer[MAX_BUFFER];

	int SerialNum;

	ASocketController* Controller;
};
