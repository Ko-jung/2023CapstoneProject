// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketMode.h"

#include "ClientController.h"
#include "ClientCharacter.h"

void ASocketMode::JoinOtherPlayer(int serial)
{
	// ���� ������ �ٸ� �÷��̾ ����
	// ���� �����ϱ� ���� �����ִ� �÷��̾��?
	SpawnPlayer(serial);
}

void ASocketMode::SetOwnSerialNum(int serial)
{
	SerialNum = serial;

	BPPossess(serial);
}

void ASocketMode::SetPlayerPosition(PPlayerPosition PlayerPosition)
{
	int32 Serial = PlayerPosition.PlayerSerial;
	FVector Location{ PlayerPosition.x, PlayerPosition.y, PlayerPosition.z };
	FRotator Rotate{ PlayerPosition.rx, PlayerPosition.ry, PlayerPosition.rz };
	EPlayerState state = PlayerPosition.PlayerState;
	EnumPlayerState ArguState;

	FTransform transform{ Rotate, Location, FVector(1.f,1.f,1.f) };

	switch (state)
	{
	case EPlayerState::Stay:
		ArguState = EnumPlayerState::EStay;
		break;
	case EPlayerState::Walk:
		ArguState = EnumPlayerState::EWalk;
		break;
	case EPlayerState::Run:
		ArguState = EnumPlayerState::ERun;
		break;
	case EPlayerState::Jump:
		ArguState = EnumPlayerState::EJump;
		break;
	default:
		break;
	}

	BPSetPlayerPosition(Serial, transform);
	//BPSetPlayerPosition(Serial, Location, Rotate, ArguState);
}

void ASocketMode::Disconnect()
{
	m_Socket->Disconnect();
	m_Socket->Stop();
}

void ASocketMode::BeginPlay()
{
	// Call Blueprint BeginPlay
	Super::BeginPlay();

	m_Socket = ClientSocketMgr::Instance();
	m_Socket->InitSocket();

	//TestPrintHelloUseNative();
	//BPGetAllActorsOfThirdPerson();

	m_bIsConnected = m_Socket->Connect("127.0.0.1", 8000);
	if (m_bIsConnected)
	{
		m_Socket->StartListen();
		m_Socket->SetGamemode(this);

		UE_LOG(LogClass, Warning, TEXT("IOCP Server connect success!"));
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("IOCP Server connect FAIL!"));
	}
}

void ASocketMode::Tick(float Deltatime)
{
	Super::Tick(Deltatime);

	ProcessFunc();

	m_Socket->SendPlayerInfo(Clients[SerialNum]->GetActorTransform());
	//for (int8 i = 0; i < 6; i++)
	//{
	//	// Send 현재 위치
	//}

	//if(m_Socket && m_Socket->TempCube)
	//	CubeVec = m_Socket->TempCube->Location;
}

void ASocketMode::PushQueue(EFunction e, Packet* etc)
{
	FuncQueue.push(std::pair(e, etc));
}

void ASocketMode::ProcessFunc()
{
	std::pair<EFunction, Packet*> EFunc;
	while (FuncQueue.try_pop(EFunc))
	{
		//auto EFunc = FuncQueue.front();
		//FuncQueue.pop();
		EFunction func = EFunc.first;
		Packet* argu = EFunc.second;

		switch (func)
		{
		case EBPPOSSESS:
		{
			PPlayerJoin PPJ;
			memcpy(&PPJ, argu, sizeof(PPlayerJoin));
			SetOwnSerialNum(PPJ.PlayerSerial);

			break;
		}
		case ESPAWNPLAYER:
		{
			PPlayerJoin PPJ;
			memcpy(&PPJ, argu, sizeof(PPlayerJoin));
			JoinOtherPlayer(PPJ.PlayerSerial);
			break;
		}
		case EPLAYERTRANSFORM:
		{
			PPlayerPosition* PPP = static_cast<PPlayerPosition*>(argu);
			SetPlayerPosition(*PPP);

			delete PPP;
			break;
		}
		default:
			break;
		}
	}
}

void ASocketMode::SpawnPlayer_Implementation(int serial){}
void ASocketMode::TestPrintHelloUseNative_Implementation(){}
void ASocketMode::BPGetAllActorsOfThirdPerson_Implementation(){}
void ASocketMode::BPSetPlayerPosition_Implementation(int serial, FTransform transform){}
//void ASocketMode::BPSetPlayerPosition_Implementation(int serial, FVector location, FRotator rotate, EnumPlayerState state){}
void ASocketMode::BPPossess_Implementation(int serial){}