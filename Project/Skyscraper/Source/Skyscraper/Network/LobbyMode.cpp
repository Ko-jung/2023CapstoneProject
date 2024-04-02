// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyMode.h"
#include "../NetworkManager.h"

void ALobbyMode::BeginPlay()
{
	if (bIsConnected)
	{
		UE_LOG(LogClass, Warning, TEXT("Server already CONEECT!"));
		return;
	}

	Super::BeginPlay();

	//m_Socket = NetworkManager::Instance();
	//m_Socket->InitSocket();

	//bIsConnected = m_Socket->Connect(SERVER_IP, LOBBY_SERVER_PORT);
	//if (bIsConnected)
	//{
	//	m_Socket->StartListen();
	//	m_Socket->SetGamemode(this);
	//	SerialNum = m_Socket->GetSerialNum();

	//	UE_LOG(LogClass, Log, TEXT("IOCP Server connect success!"));
	//}
	//else
	//{
	//	UE_LOG(LogClass, Warning, TEXT("IOCP Server connect FAIL!"));
	//}
}

void ALobbyMode::Tick(float)
{
}

void ALobbyMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
}
