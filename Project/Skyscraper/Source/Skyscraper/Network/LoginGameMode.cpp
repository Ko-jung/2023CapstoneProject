// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginGameMode.h"
#include "NetworkManager.h"

void ALoginGameMode::BeginPlay()
{
	Super::BeginPlay();
	Connect(LOBBY_SERVER_IP, LOBBY_SERVER_PORT);

	m_Socket->SetState(ENetworkState::Login);
	m_Socket->SetGamemode(this);
}

void ALoginGameMode::Tick(float)
{
}

void ALoginGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
}
