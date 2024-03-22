// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkGameMode.h"
#include "NetworkManager.h"

void ANetworkGameMode::BeginPlay()
{
	// Call Blueprint BeginPlay
	Super::BeginPlay();

	m_Socket = NetworkManager::Instance();
	m_Socket->InitSocket();
}

void ANetworkGameMode::Tick(float Deltatime)
{
	Super::Tick(Deltatime);

	ProcessFunc();
}

void ANetworkGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	m_Socket->Disconnect();
	m_Socket->Stop();
}

void ANetworkGameMode::PushQueue(EFunction e, Packet* etc)
{
	//switch (e)
	//{
	//case ESPAWNPLAYER:
	//	break;
	//case EBPPOSSESS:
	//	break;
	//case EPLAYERTRANSFORM:
	//	break;
	//default:
	//	break;
	//}
	FuncQueue.push(std::pair(e, etc));
}

void ANetworkGameMode::ProcessFunc()
{
	std::pair<EFunction, Packet*> EFunc;
	while (FuncQueue.try_pop(EFunc))
	{
		EFunction func = EFunc.first;
		Packet* argu = EFunc.second;

		switch (func)
		{
		case ESPAWNPLAYER:
			break;
		case EBPPOSSESS:
			break;
		case EPLAYERTRANSFORM:
			break;
		default:
			break;
		}
	}
}
