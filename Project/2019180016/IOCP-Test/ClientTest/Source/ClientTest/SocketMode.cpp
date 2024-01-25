// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketMode.h"

void ASocketMode::BeginPlay()
{
	m_Socket = ClientSocketMgr::Instance();
	m_Socket->InitSocket();

	m_bIsConnected = m_Socket->Connect("127.0.0.1", 8000);
	if (m_bIsConnected)
	{
		m_Socket->StartListen();
		UE_LOG(LogClass, Log, TEXT("IOCP Server connect success!"));
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("IOCP Server connect FAIL!"));
	}
}
