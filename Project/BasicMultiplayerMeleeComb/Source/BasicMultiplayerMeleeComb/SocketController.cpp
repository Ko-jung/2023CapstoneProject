// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketController.h"
#include "NetworkMgr.h"

void ASocketController::BeginPlay()
{
	Super::BeginPlay();

	NetworkManager = NetworkMgr::Instance();
	NetworkManager->InitSocket();

	if (NetworkManager->Connect(SERVER_IP, SERVER_PORT))
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
	NetworkManager->StopListen();
}

void ASocketController::Tick(float Deltatime)
{
	Super::Tick(Deltatime);

	ProcessFunc();
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
