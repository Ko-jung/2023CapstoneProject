// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientSocketMgr.h"
#include <cstring>

#include "../../Packet/EnumDef.h"
#include "../../Packet/Packet.h"

#include "SocketMode.h"

ClientSocketMgr::ClientSocketMgr() :
	m_PlayerController(nullptr),
	StopTaskCounter(0),
	Thread(nullptr),
	SerialNum(-1)
{
}

ClientSocketMgr::~ClientSocketMgr()
{
	delete Thread;
	Thread = nullptr;

	closesocket(m_ServerSocket);
	WSACleanup();
}

bool ClientSocketMgr::InitSocket()
{
	WSADATA wsaData;
	// ���� ������ 2.2�� �ʱ�ȭ
	int nRet = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (nRet != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Socket Init Error"));
		return false;
	}

	// TCP ���� ����	
	m_ServerSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (m_ServerSocket == INVALID_SOCKET)
	{
		UE_LOG(LogTemp, Warning, TEXT("TCP Socket Error"));
		return false;
	}

	UE_LOG(LogTemp, Warning, TEXT("Socket Init Success"));
	return true;
}

bool ClientSocketMgr::Connect(const char* pszIP, int nPort)
{
	// ������ ���� ������ ������ ����ü
	SOCKADDR_IN stServerAddr;

	stServerAddr.sin_family = AF_INET;
	// ������ ���� ��Ʈ �� IP
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

void ClientSocketMgr::SendChat(const int& SessionId, const string& Chat)
{
}

bool ClientSocketMgr::StartListen()
{
	// ������ ����
	if (Thread != nullptr)
	{
		Thread->Kill();
		delete Thread;
		Thread = nullptr;

		delete TempCube;
		TempCube = nullptr;
	}
	Thread = FRunnableThread::Create(this, TEXT("BlockingConnectThread"), 0, TPri_BelowNormal);
	TempCube = new ObjectInfo;
	StopTaskCounter.Reset();
	return (Thread != nullptr);
}

void ClientSocketMgr::StopListen()
{
	// ������ ����
	Stop();
	Thread->WaitForCompletion();
	Thread->Kill();
	delete Thread;
	Thread = nullptr;
	StopTaskCounter.Reset();
}

bool ClientSocketMgr::Init()
{
	return true;
}

uint32 ClientSocketMgr::Run()
{
	// �ʱ� init ������ ��ٸ�
	FPlatformProcess::Sleep(0.03);

	// recv while loop ����
	// StopTaskCounter Ŭ���� ������ ����� Thread Safety�ϰ� ����
	 while (StopTaskCounter.GetValue() == 0 /*&& m_PlayerController != nullptr*/)
	//for (int i = 0; i < 50000; i++)
	{
		int nRecvLen = recv(m_ServerSocket, (CHAR*)&m_sRecvBuffer, MAX_BUFFER, 0);
		FString PrintStr(m_sRecvBuffer);
		if (nRecvLen > 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Recv Message Is: %s"), *PrintStr);
		}

		std::stringstream RecvStream(m_sRecvBuffer);
		int OP;
		RecvStream >> OP;

		memcpy(&OP, m_sRecvBuffer, sizeof(int));

		switch (OP)
		{
		case (int)COMP_OP::OP_POSITION:
		//TODO: ����
		{
			PPosition TempPosition;
			memcpy(&TempPosition, m_sRecvBuffer, sizeof(PPosition));
			//float x, y, z;
			//RecvStream >> x >> y >> z;

			TempCube->Location.X = TempPosition.x;
			TempCube->Location.Y = TempPosition.y;
			TempCube->Location.Z = TempPosition.z;

			UE_LOG(LogTemp, Warning, TEXT("Cube Position is {%f, %f, %f}"),
				TempCube->Location.X, TempCube->Location.Y, TempCube->Location.Z);
		}
			break;
		case (int)COMP_OP::OP_PLAYERJOIN:
		{
			PPlayerJoin TempJoin(-1);
			memcpy(&TempJoin, m_sRecvBuffer, sizeof(PPlayerJoin));

			if (SerialNum == -1)
			{
				SerialNum = TempJoin.PlayerSerial;
				UE_LOG(LogTemp, Warning, TEXT("Server Join Success!"));
			}
			else
			{
				// PlayerSpawn
				Gamemode->JoinOtherPlayer(TempJoin.PlayerSerial);
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue,
				//	FString::Printf(TEXT("%d Client Join!"), TempJoin.PlayerSerial));
			}
		}
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("Recv OP Error!"))
			break;
		}
		//Packet* packet = GetPacket((COMP_OP)OP);

		//FString SendStr("ASDASD");
		//int nSendLen = send(
		//	m_ServerSocket, TCHAR_TO_ANSI(*SendStr), SendStr.Len(), 0
		//);
		//
		//if (nSendLen == -1)
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("send Error"));
		//}
	}
	UE_LOG(LogTemp, Warning, TEXT("Recv Close"));
	return 0;
}

void ClientSocketMgr::Stop()
{
	// thread safety ������ ������ while loop �� ���� ���ϰ� ��
	StopTaskCounter.Increment();
}

void ClientSocketMgr::Exit()
{
}
