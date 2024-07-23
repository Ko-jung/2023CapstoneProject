// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyMode.h"
#include "NetworkManager.h"
#include "Skyscraper/Network/LobbyWidget.h"
#include "Skyscraper/Network/SocketGameInstance.h"
#include "Kismet/GameplayStatics.h"

ALobbyMode::ALobbyMode()
{
	// /Script/UMGEditor.WidgetBlueprint'/Game/2019180016/Blueprint/Widget/WBP_LobbyWidget.WBP_LobbyWidget'
	static ConstructorHelpers::FClassFinder<ULobbyWidget> WidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/2019180016/Blueprint/Widget/WBP_LobbyWidget.WBP_LobbyWidget_C'"));
	if (WidgetClass.Succeeded())
	{
		LobbyWidgetClass = WidgetClass.Class;
	}
}

void ALobbyMode::BeginPlay()
{
	Super::BeginPlay();

	m_Socket->InitializeProperty();
	//m_Socket->SetState(ENetworkState::SelectGame);

	IsReady = false;
	UE_LOG(LogTemp, Warning, TEXT("bIsConnected is %d"), GetIsConnected());

	if (LobbyWidgetClass)
	{
		LobbyWidget = CreateWidget<ULobbyWidget>(GetWorld(), LobbyWidgetClass);
		if (LobbyWidget)
		{
			LobbyWidget->AddToViewport();
			GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("LobbyWidget is nullptr"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("LobbyWidgetClass is nullptr"));
	}

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
		m_Socket->InitializeSocket();
		m_Socket->SetState(ENetworkState::Lobby);
		//m_Socket->InitSocket();
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

	if (LobbyWidget && LobbyWidget->IsMatching)
	{
		LobbyWidget->UpdateMatchingTimer();
	}
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
		case(BYTE)COMP_OP::OP_PLAYERID:
		{
			PPlayerID PPI;
			memcpy(&PPI, packet, sizeof(PPI));
			ProcessPlayerIDs(PPI);
			break;
		}
		default:
			break;
		}

		delete packet;
	}
}

void ALobbyMode::ProcessPlayerIDs(const PPlayerID& IDs)
{
	USocketGameInstance* Inst = Cast<USocketGameInstance>(GetWorld()->GetGameInstance());
	TArray<FString> IDStrings;
	for (int i = 0; i < MAXPLAYER; i++)
	{
		Inst->PlayerIDs.Add(FString(IDs.IDs[i]));
	}

	//Controller->SetPlayerIDs(IDStrings, SerialNum);
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

void ALobbyMode::Ready(bool bIsReady)
{
	if (!m_Socket) return;

	if (bIsReady)
	{
		PCancleMatching PCM;
		m_Socket->Send(&PCM, sizeof(PCM));
	}
	else
	{
		PStartMatching PSM;
		m_Socket->Send(&PSM, sizeof(PSM));
	}
}
