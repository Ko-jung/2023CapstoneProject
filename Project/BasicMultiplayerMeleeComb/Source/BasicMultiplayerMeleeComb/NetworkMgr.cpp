// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkMgr.h"

NetworkMgr::NetworkMgr() :
	Controller(nullptr),
	StopTaskCounter(0),
	Thread(nullptr),
	SerialNum(-1)
{
}

NetworkMgr::~NetworkMgr()
{
	delete Thread;
	Thread = nullptr;

	closesocket(m_ServerSocket);
	WSACleanup();
}

void NetworkMgr::Send(int packetsize, Packet* packet)
{
	memcpy(m_sSendBuffer, packet, packetsize);
	int nSendLen = send(m_ServerSocket, m_sSendBuffer, packetsize, 0);
	if (nSendLen == -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("send Error PacketType is %d"), packet->PacketType);
	}
}

bool NetworkMgr::InitSocket()
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

	UE_LOG(LogTemp, Display, TEXT("Socket Init Success"));
	return true;
}

bool NetworkMgr::Connect(const char* pszIP, int nPort)
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

	UE_LOG(LogTemp, Display, TEXT("Socket Connect Success"));
	return true;
}

void NetworkMgr::Disconnect()
{
	PDisconnect disconnect(SerialNum);
	Send(sizeof(PDisconnect), &disconnect);
	SerialNum = -1;
}

void NetworkMgr::SendPlayerInfo(FTransform transform, float speed)
{
	if (SerialNum == -1)
	{
		return;
	}
	FVector location = transform.GetLocation();
	FRotator rotate = transform.GetRotation().Rotator();
	//FRotator rotate = transform.GetRotation();

	PPlayerPosition PlayerPosition;
	PlayerPosition.PlayerSerial = SerialNum;

	PlayerPosition.x = location.X;
	PlayerPosition.y = location.Y;
	PlayerPosition.z = location.Z;

	PlayerPosition.rx = rotate.Pitch;
	PlayerPosition.ry = rotate.Yaw;
	PlayerPosition.rz = rotate.Roll;

	PlayerPosition.PlayerSpeed = speed;

	memcpy(m_sSendBuffer, &PlayerPosition, sizeof(PPlayerPosition));

	int nSendLen = send(m_ServerSocket, m_sSendBuffer, sizeof(PPlayerPosition), 0);
	if (nSendLen == -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("send Error"));
	}
}

bool NetworkMgr::StartListen()
{
	Thread = FRunnableThread::Create(this, TEXT("BlockingConnectThread"), 0, TPri_BelowNormal);
	StopTaskCounter.Reset();
	return (Thread != nullptr);
}

void NetworkMgr::StopListen()
{
	Stop();
	Thread->WaitForCompletion();
	Thread->Kill();
	delete Thread;
	Thread = nullptr;
	StopTaskCounter.Reset();
}

bool NetworkMgr::Init()
{
	return false;
}

uint32 NetworkMgr::Run()
{
	// init 대기
	FPlatformProcess::Sleep(0.03);

	while (StopTaskCounter.GetValue() == 0 && Controller != nullptr)
	{
		int nRecvLen = recv(m_ServerSocket, (CHAR*)&m_sRecvBuffer, MAX_BUFFER, 0);
		//FString PrintStr(m_sRecvBuffer);
		//if (nRecvLen > 0)
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("Recv Message Is: %s"), *PrintStr);
		//}

		std::stringstream RecvStream(m_sRecvBuffer);
		int OP;
		RecvStream >> OP;

		memcpy(&OP, m_sRecvBuffer, sizeof(int));

		switch (OP)
		{
		case (int)COMP_OP::OP_POSITION:
			break;
		case (int)COMP_OP::OP_PLAYERJOIN:
			break;
		case (int)COMP_OP::OP_PLAYERPOSITION:
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("Recv OP Error!"));
			break;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Recv Close"));
	return 0;
}

void NetworkMgr::Stop()
{
	StopTaskCounter.Increment();
}

void NetworkMgr::Exit()
{
}
