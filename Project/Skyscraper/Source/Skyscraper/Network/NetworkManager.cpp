// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkManager.h"
#include "NetworkGameMode.h"

NetworkManager::NetworkManager() : 
	Gamemode(nullptr),
	Thread(nullptr),
	bIsConnected(false),
	SerialNum(0),
	State(NetworkState::SelectGame)
{
}

NetworkManager::~NetworkManager()
{
	closesocket(m_ServerSocket);
}

bool NetworkManager::InitSocket()
{
	if (bIsConnected)
	{
		UE_LOG(LogTemp, Warning, TEXT("Socket Early Init"));
		return false;
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
	if (bIsConnected)
	{
		UE_LOG(LogTemp, Warning, TEXT("Socket Early Connect"));
		return false;
	}

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

	SerialNum = -1;
	bIsConnected = true;
	return true;
}

void NetworkManager::Disconnect()
{
	bIsConnected = false;
	//PDisconnect disconnect(SerialNum);
	//Send(sizeof(PDisconnect), &disconnect);
}

void NetworkManager::ProcessRecv(int packetType)
{
	if (not IsValid(Gamemode))
	{
		return;
	}

	switch (State)
	{
	case NetworkState::Lobby:
		ProcessRecvFromLobby(packetType);
		break;
	case NetworkState::SelectGame:
		ProcessRecvFromSelectGame(packetType);
		break;
	case NetworkState::MainGame:
		ProcessRecvFromMainGame(packetType);
		break;
	default:
		break;
	}
}

void NetworkManager::ProcessRecvFromLobby(int packetType)
{
	switch (packetType)
	{
	case(int)COMP_OP::OP_CONNECTTOGAMESERVER:
	{
		PConnectToGameserver* PCTG= new PConnectToGameserver();
		memcpy(PCTG, m_sRecvBuffer, sizeof(*PCTG));

		Gamemode->PushQueue(EFunction::ECONNECTTOGAMESERVER, PCTG);
		StopListen();
		State = NetworkState::Lobby;
	}
	break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Recv FromLobby OP Error!"));
		break;
	}
}

void NetworkManager::ProcessRecvFromSelectGame(int packetType)
{
	// Select Game Mode
	switch (packetType)
	{
	case(int)COMP_OP::OP_SELECTWEAPONINFO:
	{
		PPlayerSelectInfo* PPP = new PPlayerSelectInfo();
		memcpy(PPP, m_sRecvBuffer, sizeof(PPlayerSelectInfo));
		Gamemode->PushQueue(EFunction::EPLAYERSELECTINFO, PPP);
	}
	break;
	case (int)COMP_OP::OP_PLAYERJOIN:
	{
		PPlayerJoin* PPJ = new PPlayerJoin();
		memcpy(PPJ, m_sRecvBuffer, sizeof(*PPJ));

		if (SerialNum == -1)
		{
			SerialNum = PPJ->PlayerSerial;
			Gamemode->PushQueue(EFunction::EBPPOSSESS, PPJ);
			UE_LOG(LogTemp, Warning, TEXT("Server Join Success!"));
		}
		else
		{
			// Join New Other Player
			//Gamemode->PushQueue(EFunction::ESPAWNPLAYER, &PPJ);
			//UE_LOG(LogTemp, Warning, TEXT("Server Join Success!"));
		}
	}
	break;
	case (int)COMP_OP::OP_SETTIMER:
	{
		PSetTimer* PST = new PSetTimer();
		memcpy(PST, m_sRecvBuffer, sizeof(*PST));

		Gamemode->PushQueue(EFunction::ESETTIMER, PST);
		UE_LOG(LogTemp, Warning, TEXT("New Timer Push, Time is %f s"), PST->SecondsUntilActivation);
	}
	break;
	case(int)COMP_OP::OP_STARTGAME:
	{
		PStartGame* PSG = new PStartGame();
		Gamemode->PushQueue(EFunction::ESTARTGAME, PSG);

		State = NetworkState::MainGame;
	}
	break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Recv SelectGame OP Error!"));
		break;
	}
}

void NetworkManager::ProcessRecvFromMainGame(int packetType)
{
	// Main Game Mode
	switch (packetType)
	{
	case (int)COMP_OP::OP_PLAYERPOSITION:
	{
		PPlayerPosition* PlayerPosition = new PPlayerPosition();
		memcpy(PlayerPosition, m_sRecvBuffer, sizeof(PPlayerPosition));
		Gamemode->PushQueue(EFunction::EPLAYERTRANSFORM, PlayerPosition);
	}
	break;
	case (int)COMP_OP::OP_CHANGEDPLAYERHP:
	{
		PChangedPlayerHP* PCPHP = new PChangedPlayerHP();
		memcpy(PCPHP, m_sRecvBuffer, sizeof(*PCPHP));
		Gamemode->PushQueue(EFunction::ECHANGEDPLAYERHP, PCPHP);
	}
	break; 
	case (int)COMP_OP::OP_CHANGEDPLAYERSTATE:
	{
		PChangedPlayerState* PCPS = new PChangedPlayerState();
		memcpy(PCPS, m_sRecvBuffer, sizeof(*PCPS));
		Gamemode->PushQueue(EFunction::ECHANGEDPLAYERSTATE, PCPS);
	}
	break;
	case (int)COMP_OP::OP_SPAWNOBJECT:
	{
		PSpawnObject* PSO = new PSpawnObject();
		memcpy(PSO, m_sRecvBuffer, sizeof(*PSO));
		Gamemode->PushQueue(EFunction::ESPAWNOBJECT, PSO);
		break;
	}
	default:
		UE_LOG(LogTemp, Warning, TEXT("Recv MainGame OP Error!"));
		break;
	}
}

void NetworkManager::Send(const Packet* packet, int packetsize)
{
	memcpy(m_sSendBuffer, packet, packetsize);
	int nSendLen = send(m_ServerSocket, m_sSendBuffer, packetsize, 0);
	if (nSendLen == -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("send Error PacketType is %d"), packet->PacketType);
	}
}

bool NetworkManager::StartListen()
{
	if (Thread != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Thread Is NOT NULL"));
		// Thread->Kill();
		// delete Thread;
		// Thread = nullptr;
		return true;
	}

	Thread = FRunnableThread::Create(this, TEXT("BlockingConnectThread"), 0, TPri_BelowNormal);
	//StopTaskCounter.Reset();
	bStopSwich = true;
	return (Thread != nullptr);
}

void NetworkManager::StopListen()
{
	if (not bIsConnected)
	{
		return;
	}

	bIsConnected = false;

	Stop();
}

bool NetworkManager::Init()
{
	return true;
}

uint32 NetworkManager::Run()
{
	FPlatformProcess::Sleep(0.03);

	//while (StopTaskCounter.GetValue() == 0 /*&& m_PlayerController != nullptr*/)
	while (bStopSwich)
	{
		int nRecvLen = recv(m_ServerSocket, (CHAR*)&m_sRecvBuffer, MAX_BUFFER, 0);
		//UE_LOG(LogTemp, Warning, TEXT("Something RECV"));

		if (nRecvLen == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Recv 0 Btye. break while"));
			break;
		}
		else if (nRecvLen == -1)
		{
			UE_LOG(LogTemp, Warning, TEXT("Recv -1 Btye. Server Close"));
			StopListen();
			break;
		}

		BYTE OP;
		memcpy(&OP, m_sRecvBuffer, sizeof(BYTE));

		ProcessRecv(OP);
	}
	UE_LOG(LogTemp, Warning, TEXT("Recv Close"));

	//Thread->WaitForCompletion();
	//Thread->Kill();
	delete Thread;
	Thread = nullptr;
	StopTaskCounter.Reset();

	return 0;
}

void NetworkManager::Stop()
{
	//StopTaskCounter.Increment();
	bStopSwich = false;
}

void NetworkManager::Exit()
{
}
