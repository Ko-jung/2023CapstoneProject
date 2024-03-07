// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketController.h"
#include "NetworkMgr.h"

void ASocketController::BeginPlay()
{
	Super::BeginPlay();

	NetworkManager = NetworkMgr::Instance();
	NetworkManager->InitSocket();

	IsConnected = NetworkManager->Connect(SERVER_IP, SERVER_PORT);

	if (IsConnected)
	{
		NetworkManager->StartListen();
		NetworkManager->SetController(this);

		UE_LOG(LogClass, Warning, TEXT("IOCP Server connect success!"));
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("IOCP Server connect FAIL!"));
	}
}

void ASocketController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UE_LOG(LogClass, Log, TEXT("Called \"ASocketController::EndPlay\""));
	if (IsConnected)
	{
		NetworkManager->Disconnect();
		NetworkManager->StopListen();
	}
}

void ASocketController::Tick(float Deltatime)
{
	Super::Tick(Deltatime);

	ProcessFunc();
}

void ASocketController::JoinOtherPlayer(int serial)
{
	//SpawnPlayer(serial);
	
	//auto a = GetComponentByClass<UPrimitiveComponent>();
	//a->SetMaterial(0, )
}

void ASocketController::SetOwnSerialNum(int serial)
{
	SerialNum = serial;

	//BPPossess(serial);
	
	//Possess();
}

void ASocketController::SetPlayerPosition(PPlayerPosition PlayerPosition)
{
	int32 Serial = PlayerPosition.PlayerSerial;
	FVector Location{ PlayerPosition.x, PlayerPosition.y, PlayerPosition.z };
	FRotator Rotate{ PlayerPosition.rx, PlayerPosition.ry, PlayerPosition.rz };
	EPlayerState state = PlayerPosition.PlayerState;
	EnumPlayerState ArguState;

	FTransform transform{ Rotate, Location, FVector(1.f,1.f,1.f) };

	float speed = PlayerPosition.PlayerSpeed;

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

	//BPSetPlayerPosition(Serial, transform, speed);
	//BPSetPlayerPosition(Serial, Location, Rotate, ArguState);
}

void ASocketController::Disconnect()
{
}

void ASocketController::PushQueue(EFunction e, Packet* etc)
{
	FuncQueue.push(std::pair(e, etc));
}

void ASocketController::ProcessFunc()
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
			//SetOwnSerialNum(PPJ.PlayerSerial);

			break;
		}
		case ESPAWNPLAYER:
		{
			PPlayerJoin PPJ;
			memcpy(&PPJ, argu, sizeof(PPlayerJoin));
			//JoinOtherPlayer(PPJ.PlayerSerial);
			break;
		}
		case EPLAYERTRANSFORM:
		{
			PPlayerPosition* PPP = static_cast<PPlayerPosition*>(argu);
			//SetPlayerPosition(*PPP);

			delete PPP;
			break;
		}
		default:
			break;
		}
	}
}
