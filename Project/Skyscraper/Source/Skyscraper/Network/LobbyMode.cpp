// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyMode.h"
#include "NetworkManager.h"
#include "Kismet/GameplayStatics.h"

void ALobbyMode::BeginPlay()
{
	Super::BeginPlay();

	IsReady = false;
	UE_LOG(LogTemp, Warning, TEXT("bIsConnected is %d"), GetIsConnected());

	if (GetIsConnected())
	{
		m_Socket->SetState(ENetworkState::Lobby);
		m_Socket->StartListen();
		m_Socket->SetGamemode(this);
		SerialNum = m_Socket->GetSerialNum();

		UE_LOG(LogClass, Warning, TEXT("Server already CONEECT!"));
		return;
	}
	else
	{
		m_Socket = new NetworkManager();
		m_Socket->InitSocket();
		m_Socket->Connect(LOBBY_SERVER_IP, LOBBY_SERVER_PORT);

		if (GetIsConnected())
		{
			UE_LOG(LogClass, Warning, TEXT("IOCP lobby Server connect success!"));
		}
		else
		{
			UE_LOG(LogClass, Warning, TEXT("IOCP lobby Server connect FAIL!"));
		}
	}
}

void ALobbyMode::Tick(float Deltatime)
{
	Super::Tick(Deltatime);

	ProcessFunc();
}

void ALobbyMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	//m_Socket->StopListen();
	//FuncQueue.clear();
}

void ALobbyMode::ProcessFunc()
{
	Packet* packet;
	while (FuncQueue.try_pop(packet))
	{
		switch (packet->PacketType)
		{
		case (BYTE)COMP_OP::OP_CONNECTTOGAMESERVER:
		{
			//USocketGameInstance* instance = static_cast<USocketGameInstance*>(GetGameInstance());
			//instance->SetSelectInfo(PlayerSelectInfo);
			//instance->SetSocket(m_Socket);
			//instance->SetIsConnect(bIsConnected);
			//instance->SetSerialNum(SerialNum);

			UE_LOG(LogClass, Warning, TEXT("Level Transate"));
			UGameplayStatics::OpenLevel(this, FName("SelectCharacterLevel"));
			break;
		}
		default:
			break;
		}

		delete packet;
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