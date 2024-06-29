// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkGameMode.h"
#include "NetworkManager.h"

void ANetworkGameMode::BeginPlay()
{
	if (bIsConnected)
	{
		UE_LOG(LogClass, Warning, TEXT("Server already CONEECT!"));
		return;
	}

	// Call Blueprint BeginPlay
	Super::BeginPlay();

	m_Socket = NetworkManager::Instance();
}

void ANetworkGameMode::Tick(float Deltatime)
{
	Super::Tick(Deltatime);
}

void ANetworkGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	//m_Socket->Disconnect();
	//m_Socket->Stop();
	switch (EndPlayReason)
	{
	case EEndPlayReason::Type::LevelTransition:
		UE_LOG(LogTemp, Warning, TEXT("Level Transition"));
		break;
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

void ANetworkGameMode::PushQueue(Packet* etc)
{
	FuncQueue.push(etc);
}

void ANetworkGameMode::Send(const Packet* p, const int pSize)
{
	if (bIsConnected)
		m_Socket->Send(p, pSize);
}

bool ANetworkGameMode::Connect(const char* ip, int port)
{
	bIsConnected = m_Socket->Connect(ip, port);
	UE_LOG(LogTemp, Warning, TEXT("bIsConnected is %s"), bIsConnected ? *FString("True") : *FString("False"));
	if (bIsConnected)
	{
		m_Socket->StartListen();
		m_Socket->SetGamemode(this);
		SerialNum = m_Socket->GetSerialNum();

		UE_LOG(LogClass, Log, TEXT("IOCP Game Server connect Success!"));
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("IOCP Game Server connect FAIL!"));
	}
	return bIsConnected;
}

void ANetworkGameMode::SetOwnSerialNum(int serial)
{
	SerialNum = serial;
}