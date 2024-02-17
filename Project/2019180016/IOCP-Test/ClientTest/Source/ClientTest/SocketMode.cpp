// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketMode.h"

#include "ClientController.h"
#include "OtherPlayerCharacter.h"

#include "Engine/Blueprint.h"
#include "Engine/World.h"


void ASocketMode::JoinOtherPlayer(int serial)
{
	// 나를 제외한 다른 플레이어가 접속
	// 내가 접속하기 전에 들어와있던 플레이어는?
	SpawnPlayer();
	
	//ClientControllers.Add(serial, NewObject<AClientController>());
	//ClientControllers[serial]->SetSerialNum(serial);

	//AClientController* NewController = TSharedPtr<AClientController>().Get();

	//C:/Github/2023CapstoneProject/Project/2019180016/IOCP-Test/ClientTest/Content/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.uasset
	//'/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter'

	//AClientController* NewController = NewObject< AClientController>();
	//NewController->SetSerialNum(serial);
	//ClientControllers.Add(NewController);

	//static ConstructorHelpers::FObjectFinder<UBlueprint> NewPlayer(TEXT("Blueprint'/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter'"));

		//auto PlayerBP = (UClass*)NewPlayer.Object->GeneratedClass;

		//FActorSpawnParameters SpawnParams;
		//FRotator Rotator;
		//FVector  SpawnLocation = FVector(470.000000, 900.000000, 88.000000);
		//GetWorld()->SpawnActor<AOtherPlayerCharacter>(OtherPlayerCharacterClass);

	//AOtherPlayerCharacter* NewCharacter = GetWorld()->SpawnActor<AOtherPlayerCharacter>(
	//	AOtherPlayerCharacter::StaticClass(), SpawnLocation, Rotator, SpawnParams);
	//NewController->Possess(NewCharacter);
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

void ASocketMode::SpawnPlayer_Implementation()
{
}
