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
	m_Socket->InitSocket();

	bIsConnected = m_Socket->Connect("127.0.0.1", 9000);
	if (bIsConnected)
	{
		m_Socket->StartListen();
		m_Socket->SetGamemode(this);
		SerialNum = m_Socket->GetSerialNum();

		UE_LOG(LogClass, Log, TEXT("IOCP Server connect success!"));
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("IOCP Server connect FAIL!"));
	}
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
	m_Socket->StopListen();

	FuncQueue.clear();
}

void ANetworkGameMode::PushQueue(EFunction e, Packet* etc)
{
	FuncQueue.push(std::pair(e, etc));
}

void ANetworkGameMode::Send(const Packet* p, const int pSize)
{
	if(bIsConnected)
		m_Socket->Send(p, pSize);
}

void ANetworkGameMode::SetOwnSerialNum(int serial)
{
	SerialNum = serial;
}