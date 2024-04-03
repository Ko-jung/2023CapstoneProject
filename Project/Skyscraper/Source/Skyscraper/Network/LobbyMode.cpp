// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyMode.h"
#include "../NetworkManager.h"
#include "Kismet/GameplayStatics.h"

void ALobbyMode::BeginPlay()
{
	if (bIsConnected)
	{
		UE_LOG(LogClass, Warning, TEXT("Server already CONEECT!"));
		return;
	}

	IsConnectToLobby = true;
	IsReady = false;

	Super::BeginPlay();
}

void ALobbyMode::Tick(float Deltatime)
{
	Super::Tick(Deltatime);

	ProcessFunc();
}

void ALobbyMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	switch (EndPlayReason)
	{
	case EEndPlayReason::Type::LevelTransition:
		UE_LOG(LogTemp, Warning, TEXT("Level Transition"));
		//break;
	case EEndPlayReason::Type::Destroyed:
	case EEndPlayReason::Type::EndPlayInEditor:
	case EEndPlayReason::Type::RemovedFromWorld:
	case EEndPlayReason::Type::Quit:
		UE_LOG(LogTemp, Warning, TEXT("Level non Transition"));
		m_Socket->StopListen();
		FuncQueue.clear();
		break;
	default:
		break;
	}
}

void ALobbyMode::ProcessFunc()
{

	std::pair<EFunction, Packet*> EFunc;
	while (FuncQueue.try_pop(EFunc))
	{
		EFunction func = EFunc.first;
		Packet* argu = EFunc.second;
		switch (func)
		{
		case ECONNECTTOGAMESERVER:
		{
			//USocketGameInstance* instance = static_cast<USocketGameInstance*>(GetGameInstance());
			//instance->SetSelectInfo(PlayerSelectInfo);
			//instance->SetSocket(m_Socket);
			//instance->SetIsConnect(bIsConnected);
			//instance->SetSerialNum(SerialNum);

			UGameplayStatics::OpenLevel(this, FName("SocketMainGameLevel"));
			break;
		}
		default:
			break;
		}

		delete argu;
	}
}

void ALobbyMode::Ready()
{
	if (IsReady)
	{
		PCancleMatching PCM;
		m_Socket->Send(&PCM, sizeof(PCM));
		IsReady = false;
	}
	else
	{
		PStartMatching PSM;
		m_Socket->Send(&PSM, sizeof(PSM));
		IsReady = true;
	}
}