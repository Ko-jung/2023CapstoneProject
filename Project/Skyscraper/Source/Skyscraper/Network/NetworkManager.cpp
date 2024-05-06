// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkManager.h"
#include "NetworkGameMode.h"

NetworkManager::NetworkManager() : 
	Thread(nullptr),
	Gamemode(nullptr),
	bIsConnected(false),
	State(ENetworkState::SelectGame),
	IsChangingGameMode(false),
	SerialNum(0),
	RemainDataLen(0)
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
		UE_LOG(LogTemp, Warning, TEXT("Socket Connect Fail Error code: %d"), WSAGetLastError());
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

void NetworkManager::ProcessRecv(Packet* p)
{
	if (IsChangingGameMode || not IsValid(Gamemode))
	{
		return;
	}

	switch (State)
	{
	case ENetworkState::Lobby:
		ProcessRecvFromLobby(p);
		break;
	case ENetworkState::SelectGame:
		ProcessRecvFromSelectGame(p);
		break;
	case ENetworkState::MainGame:
		ProcessRecvFromMainGame(p);
		break;
	default:
		break;
	}
}

void NetworkManager::ProcessRecvFromLobby(Packet* p)
{
	switch (p->PacketType)
	{
	case(int)COMP_OP::OP_CONNECTTOGAMESERVER:
	{
		PConnectToGameserver* PCTG= new PConnectToGameserver();
		memcpy(PCTG, p, sizeof(*PCTG));

		Gamemode->PushQueue(PCTG);
		StopListen();

		State = ENetworkState::SelectGame;
		IsChangingGameMode = true;
	}
	break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Recv FromLobby OP Error!"));
		break;
	}
}

void NetworkManager::ProcessRecvFromSelectGame(Packet* p)
{
	// Select Game Mode
	switch (p->PacketType)
	{
	case(int)COMP_OP::OP_SELECTWEAPONINFO:
	{
		PPlayerSelectInfo* PPP = new PPlayerSelectInfo();
		memcpy(PPP, p, sizeof(PPlayerSelectInfo));
		Gamemode->PushQueue(PPP);
	}
	break;
	case (int)COMP_OP::OP_PLAYERJOIN:
	{
		PPlayerJoin* PPJ = new PPlayerJoin();
		memcpy(PPJ, p, sizeof(*PPJ));

		if (SerialNum == -1)
		{
			SerialNum = PPJ->PlayerSerial;
			Gamemode->PushQueue(PPJ);
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
		memcpy(PST, p, sizeof(*PST));

		Gamemode->PushQueue(PST);
		UE_LOG(LogTemp, Warning, TEXT("New Timer Push, Time is %f s"), PST->SecondsUntilActivation);
	}
	break;
	case(int)COMP_OP::OP_STARTGAME:
	{
		PStartGame* PSG = new PStartGame();
		Gamemode->PushQueue(PSG);
		IsChangingGameMode = true;

		State = ENetworkState::MainGame;
	}
	break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Recv SelectGame OP Error!"));
		break;
	}
}

void NetworkManager::ProcessRecvFromMainGame(Packet* p)
{
	// Main Game Mode
	
	// p는 RecvBuf의 포인터. Packet의 변수를 만들어야한다.
	//Gamemode->PushQueue(p);

	switch (p->PacketType)
	{
	case (int)COMP_OP::OP_BUILDINGINFO:
	{
		PBuildingInfo* PBI = new PBuildingInfo();
		memcpy(PBI, p, sizeof(*PBI));
		Gamemode->PushQueue(PBI);
		break;
	}
	case (int)COMP_OP::OP_PLAYERPOSITION:
	{
		PPlayerPosition* PlayerPosition = new PPlayerPosition();
		memcpy(PlayerPosition, p, sizeof(PPlayerPosition));
		//TryPush(PlayerPosition);
		Gamemode->PushQueue(PlayerPosition);
		break;
	}
	case (int)COMP_OP::OP_CHANGEDPLAYERHP:
	{
		PChangedPlayerHP* PCPHP = new PChangedPlayerHP();
		memcpy(PCPHP, p, sizeof(*PCPHP));
		// TryPush(PCPHP);
		Gamemode->PushQueue(PCPHP);
		break;
	}
	case (int)COMP_OP::OP_CHANGEDPLAYERSTATE:
	{
		PChangedPlayerState* PCPS = new PChangedPlayerState();
		memcpy(PCPS, p, sizeof(*PCPS));
		// TryPush(PCPS);
		Gamemode->PushQueue(PCPS);
		break;
	}
	case (int)COMP_OP::OP_SPAWNOBJECT:
	{
		PSpawnObject* PSO = new PSpawnObject();
		memcpy(PSO, p, sizeof(*PSO));
		// TryPush(PSO);
		Gamemode->PushQueue(PSO);
		break;
	}
	case (int)COMP_OP::OP_CHANGEANIMMONTAGE:
	{
		PChangeAnimMontage* PCAM = new PChangeAnimMontage();
		memcpy(PCAM, p, sizeof(*PCAM));
		// TryPush(PCAM);
		Gamemode->PushQueue(PCAM);
		break;
	}
	case (int)COMP_OP::OP_SWAPWEAPON:
	{
		PSwapWeapon* PSW = new PSwapWeapon();
		memcpy(PSW, p, sizeof(*PSW));
		// TryPush(PSW);
		Gamemode->PushQueue(PSW);
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
		// 재조립을 위해 recv 인자 수정
		int nRecvLen = recv(m_ServerSocket, (CHAR*)(m_sRecvBuffer + RemainDataLen), MAX_BUFFER - RemainDataLen, 0);

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

		// 패킷 재조립
		int RemainLen = nRecvLen + RemainDataLen;
		char* ReciveData = m_sRecvBuffer;
		while (RemainLen > 0)
		{
			Packet* p = reinterpret_cast<Packet*>(ReciveData);

			if (RemainLen >= p->PacketSize)
			{
				ProcessRecv(p);
				ReciveData += p->PacketSize;
				RemainLen -= p->PacketSize;
			}
			else break;
		}
		RemainDataLen = RemainLen;
		if (RemainLen > 0)
		{
			memmove(m_sRecvBuffer, ReciveData, RemainLen);
			UE_LOG(LogTemp, Warning, TEXT("Called Memmove"));
		}
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

//void NetworkManager::SetGamemode(ANetworkGameMode* gamemode, ENetworkState state)
//{
//	Gamemode = gamemode;
//	State = state;
//	IsChangingGameMode = false;
//	UE_LOG(LogTemp, Warning, TEXT("Change Gamemode State is %d"), state);
//}

void NetworkManager::SetGamemode(ANetworkGameMode* gamemode)
{ 
	Gamemode = gamemode; 
	IsChangingGameMode = false;
}

bool NetworkManager::TryPush(Packet* p)
{
	if(IsValid(Gamemode))
	{
		Gamemode->PushQueue(p);
		return true;
	}
	return false;
}
