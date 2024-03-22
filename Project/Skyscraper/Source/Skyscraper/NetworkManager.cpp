// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkManager.h"

NetworkManager::NetworkManager() : 
	Gamemode(nullptr),
	bIsConnected(false)
{
}

NetworkManager::~NetworkManager()
{
}

bool NetworkManager::InitSocket()
{
	if (not bIsConnected)
	{
		UE_LOG(LogTemp, Warning, TEXT("Socket Early Init"));
		return;
	}

	WSADATA wsaData;
	int nRet = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (nRet != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Socket Init Error"));
		return false;
	}
	m_ServerSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (m_ServerSocket == INVALID_SOCKET)
	{
		UE_LOG(LogTemp, Warning, TEXT("TCP Socket Error"));
		return false;
	}

	UE_LOG(LogTemp, Warning, TEXT("Socket Init Success"));
	return true;
}

bool NetworkManager::Connect(const char* pszIP, int nPort)
{
	SOCKADDR_IN stServerAddr;

	stServerAddr.sin_family = AF_INET;
	stServerAddr.sin_port = htons(nPort);
	stServerAddr.sin_addr.s_addr = inet_addr(pszIP);

	int nRet = connect(m_ServerSocket, (sockaddr*)&stServerAddr, sizeof(sockaddr));
	if (nRet == SOCKET_ERROR)
	{
		UE_LOG(LogTemp, Warning, TEXT("Socket Connect Fail"));
		return false;
	}

	UE_LOG(LogTemp, Warning, TEXT("Socket Connect Success"));
	return true;
}

void NetworkManager::Disconnect()
{
	//PDisconnect disconnect(SerialNum);
	//Send(sizeof(PDisconnect), &disconnect);
}

void NetworkManager::ProcessRecv(int packetType)
{
	switch (packetType)
	{
	case(int)COMP_OP::OP_SETTIMER:

		break;
	case(int)COMP_OP::OP_SELECTWEAPONINFO:

		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Recv OP Error!"));
		break;
	}
}

bool NetworkManager::StartListen()
{
	if (Thread != nullptr)
	{
		Thread->Kill();
		delete Thread;
		Thread = nullptr;
	}

	Thread = FRunnableThread::Create(this, TEXT("BlockingConnectThread"), 0, TPri_BelowNormal);
	StopTaskCounter.Reset();
	return (Thread != nullptr);
}

void NetworkManager::StopListen()
{
	Stop();
	Thread->WaitForCompletion();
	Thread->Kill();
	delete Thread;
	Thread = nullptr;
	StopTaskCounter.Reset();
}

bool NetworkManager::Init()
{
	return false;
}

uint32 NetworkManager::Run()
{
	FPlatformProcess::Sleep(0.03);

	while (StopTaskCounter.GetValue() == 0 /*&& m_PlayerController != nullptr*/)
	{
		int nRecvLen = recv(m_ServerSocket, (CHAR*)&m_sRecvBuffer, MAX_BUFFER, 0);

		if (nRecvLen == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Recv 0 Btye. break while"));
			break;
		}

		BYTE OP;
		memcpy(&OP, m_sRecvBuffer, sizeof(BYTE));

		ProcessRecv(OP);
	}
	UE_LOG(LogTemp, Warning, TEXT("Recv Close"));
	return 0;
}

void NetworkManager::Stop()
{
	StopTaskCounter.Increment();
}

void NetworkManager::Exit()
{
}
