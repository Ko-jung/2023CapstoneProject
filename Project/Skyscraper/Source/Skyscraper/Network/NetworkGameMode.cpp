// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkGameMode.h"
#include "NetworkManager.h"

void ANetworkGameMode::BeginPlay()
{
	// Call Blueprint BeginPlay
	Super::BeginPlay();

	SerialNum = -1;
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
	{
		PDisconnect PD;
		m_Socket->Send(&PD, PD.PacketSize);

		UE_LOG(LogTemp, Warning, TEXT("Level non Transition"));
		//m_Socket->StopListen();
		FuncQueue.clear();
	}
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
	if (GetIsConnected())
		m_Socket->Send(p, pSize);
}

bool ANetworkGameMode::Connect(const char* ip, int port)
{
	m_Socket->Connect(ip, port);
	UE_LOG(LogTemp, Warning, TEXT("bIsConnected is %s"), GetIsConnected() ? *FString("True") : *FString("False"));
	if (GetIsConnected())
	{
		m_Socket->StartListen();
		m_Socket->SetGamemode(this);

		UE_LOG(LogTemp, Warning, TEXT("IOCP Game Server connect Success!"));
		return true;
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("IOCP Game Server connect FAIL!"));
		return false;
	}
}

void ANetworkGameMode::SetOwnSerialNum(int serial)
{
	SerialNum = serial;
	UE_LOG(LogClass, Warning, TEXT("ANetworkGameMode's SerialNum : %d"), SerialNum);
}

bool ANetworkGameMode::GetIsConnected()
{
	return m_Socket->GetIsConnected();
}
