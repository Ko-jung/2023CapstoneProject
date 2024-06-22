// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginGameMode.h"
#include "NetworkManager.h"
#include "Skyscraper/LoginWidget/LoginWidget.h"

#include "Kismet/GameplayStatics.h"

ALoginGameMode::ALoginGameMode()
{
	///Script/CoreUObject.Class'/Script/Skyscraper.LoginWidget'
	static ConstructorHelpers::FClassFinder<ULoginWidget> WidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/2019180016/Blueprint/Widget/WBP_LoginWidget.WBP_LoginWidget_C'"));
	if (WidgetClass.Succeeded())
	{
		LoginWidgetClass = WidgetClass.Class;
	}
}

void ALoginGameMode::BeginPlay()
{
	Super::BeginPlay();
	Connect(LOBBY_SERVER_IP, LOBBY_SERVER_PORT);

	m_Socket->SetState(ENetworkState::Login);
	m_Socket->SetGamemode(this);

	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;

	if (LoginWidgetClass)
	{
		LoginWidget = CreateWidget<ULoginWidget>(GetWorld(), LoginWidgetClass);
		if (LoginWidget)
		{
			LoginWidget->AddToViewport();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("LoginWidget is nullptr"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("LoginWidgetClass is nullptr"));
	}
}

void ALoginGameMode::Tick(float Deltatime)
{
	Super::Tick(Deltatime);

	ProcessFunc();
}

void ALoginGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
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

void ALoginGameMode::ProcessFunc()
{
	Packet* packet;
	while (FuncQueue.try_pop(packet))
	{
		UE_LOG(LogTemp, Warning, TEXT("ALoginGameMode::ProcessFunc"));
		switch (packet->PacketType)
		{
		case (BYTE)COMP_OP::OP_LOGINRESULT:
		{
			PLoginResult* PLR = reinterpret_cast<PLoginResult*>(packet);
			if (PLR->LoginResult == (char)ELoginResult::Success)
			{
				UE_LOG(LogClass, Warning, TEXT("Level Transate"));
				UGameplayStatics::OpenLevel(this, FName("LobbyLevel"));
			}
			else
			{
				if (!LoginWidget)
				{
					delete packet;
					continue;
				}
				LoginWidget->SetExtraMessage(PLR->LoginResult);
			}
			break;
		}
		default:
			break;
		}
		delete packet;
	}
}
