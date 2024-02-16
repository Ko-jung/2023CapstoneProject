// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketMode.h"

#include "ClientController.h"

void ASocketMode::JoinOtherPlayer(int serial)
{
	//ClientControllers.Add(serial, NewObject<AClientController>());
	//ClientControllers[serial]->SetSerialNum(serial);

	//AClientController* NewController = TSharedPtr<AClientController>().Get();

	AClientController* NewController = NewObject< AClientController>();
	NewController->SetSerialNum(serial);
	ClientControllers.Add(NewController);
}

void ASocketMode::SpawnOtherPlayer()
{

}

void ASocketMode::Disconnect()
{
	m_Socket->Stop();
}

void ASocketMode::BeginPlay()
{
	m_Socket = ClientSocketMgr::Instance();
	m_Socket->InitSocket();

	m_bIsConnected = m_Socket->Connect("127.0.0.1", 8000);
	if (m_bIsConnected)
	{
		m_Socket->StartListen();
		m_Socket->SetGamemode(this);

		UE_LOG(LogClass, Log, TEXT("IOCP Server connect success!"));
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("IOCP Server connect FAIL!"));
	}
}

void ASocketMode::Tick(float Deltatime)
{
	Super::Tick(Deltatime);

	if(m_Socket && m_Socket->TempCube)
		CubeVec = m_Socket->TempCube->Location;
}
