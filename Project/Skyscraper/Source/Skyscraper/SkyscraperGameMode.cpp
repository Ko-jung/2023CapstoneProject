// Copyright Epic Games, Inc. All Rights Reserved.

#include "SkyscraperGameMode.h"
#include "MainGame/Actor/Character/SkyscraperCharacter.h"

#include "Network/NetworkManager.h"
#include "Network/SocketGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Skyscraper/SelectCharacter/Core/SelectCharacterController.h"

#include "UObject/ConstructorHelpers.h"

ASkyscraperGameMode::ASkyscraperGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	{
		//DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	PlayerSelectInfo.Init(nullptr, MAXPLAYER);

	int i = 0;
	for (auto& P : PlayerSelectInfo)
	{
		P = new PPlayerSelectInfo();
		P->ClientNum = i++; 
	}

	IsBeConnect = true;
}

void ASkyscraperGameMode::ProcessFunc()
{
	//std::pair<EFunction, Packet*> EFunc;
	Packet* packet;
	while (FuncQueue.try_pop(packet))
	{
		switch (packet->PacketType)
		{
		case (BYTE)COMP_OP::OP_PLAYERJOIN:
		{
			PPlayerJoin PPJ;
			memcpy(&PPJ, packet, sizeof(PPlayerJoin));
			Super::SetOwnSerialNum(PPJ.PlayerSerial);

			SetWidgetPlayerIDs();
		}
			break;
		case (BYTE)COMP_OP::OP_SELECTWEAPONINFO:
			ProcessSelectInfo(packet);
			break;
		case (BYTE)COMP_OP::OP_SETTIMER:
		{
			PSetTimer PST;
			memcpy(&PST, packet, sizeof(PST));

			SelectTimer = PST.SecondsUntilActivation;
		}
			break;
		case (BYTE)COMP_OP::OP_STARTGAME:
		{
			USocketGameInstance* instance = static_cast<USocketGameInstance*>(GetGameInstance());
			instance->SetSelectInfo(PlayerSelectInfo);
			instance->SetSocket(m_Socket);
			instance->SetIsConnect(GetIsConnected());
			instance->SetSerialNum(SerialNum);

			//FString Level = L"/Game/MainGame/Level/MapCreateLevel";
			//UGameplayStatics::OpenLevel(this, *Level);

			UGameplayStatics::OpenLevel(this, FName("MapCreateLevel"));
		}
			break;
		default:
			break;
		}

		delete packet;
	}
}

void ASkyscraperGameMode::BeginPlay()
{
	Super::BeginPlay();
	m_Socket->InitializeManager();
	m_Socket->SetState(ENetworkState::SelectGame);

	Controller = Cast<ASelectCharacterController>(GetWorld()->GetFirstPlayerController());
	if (!Controller)
	{
		UE_LOG(LogTemp, Warning, TEXT("ASkyscraperGameMode::BeginPlay() Controller is NULLPTR"));
	}

	if (IsBeConnect)
	{
		Connect(GAME_SERVER_IP, GAME_SERVER_PORT);


		// Move to after Recv OP_PlayerJoin Packet
		//SetWidgetPlayerIDs();
	}
	else
	{
		SerialNum = 0;
		UE_LOG(LogTemp, Warning, TEXT("ASkyscraperGameMode::BeginPlay() IsBeConnect is false"));
	}
}

void ASkyscraperGameMode::Tick(float Deltatime)
{
	Super::Tick(Deltatime);

	if (!IsBeConnect) return;

	if (SelectTimer > 0.001f)
	{
		SelectTimer -= Deltatime;
	}

	ProcessFunc();
}

void ASkyscraperGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ASkyscraperGameMode::ProcessSelectInfo(Packet* argu)
{
	PPlayerSelectInfo* PPP = static_cast<PPlayerSelectInfo*>(argu);

	int ClientNum = PPP->ClientNum;
	if (ClientNum == -1)
	{
		UE_LOG(LogClass, Warning, TEXT("PPlayerPickInfo Packet ClientNum == -1!"));
	}

	ECharacterSelect   Character   = PPP->PickedCharacter;
	EMeleeSelect MeleeWeapon = PPP->PickedMeleeWeapon;
	ERangeSelect RangeWeapon = PPP->PickedRangeWeapon;

	PlayerSelectInfo[ClientNum]->PickedCharacter	 = Character  ;
	PlayerSelectInfo[ClientNum]->PickedMeleeWeapon	 = MeleeWeapon;
	PlayerSelectInfo[ClientNum]->PickedRangeWeapon	 = RangeWeapon;
}

void ASkyscraperGameMode::SetWidgetPlayerIDs()
{
	USocketGameInstance* Inst = Cast<USocketGameInstance>(GetWorld()->GetGameInstance());
	Controller->SetPlayerIDs(Inst->PlayerIDs, SerialNum);
}

void ASkyscraperGameMode::SendSelectInfo()
{
	PPlayerSelectInfo PPS;

	PPS.ClientNum = SerialNum;
	PPS.PickedCharacter = PlayerSelectInfo[SerialNum]->PickedCharacter;
	PPS.PickedMeleeWeapon = PlayerSelectInfo[SerialNum]->PickedMeleeWeapon;
	PPS.PickedRangeWeapon = PlayerSelectInfo[SerialNum]->PickedRangeWeapon;

	Send(&PPS, sizeof(PPS));
}

void ASkyscraperGameMode::UpdateSelectInfo(ECharacterSelect Character)
{
	if (PlayerSelectInfo.IsValidIndex(SerialNum))
	{
		PlayerSelectInfo[SerialNum]->PickedCharacter = Character;
		SendSelectInfo();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerSelectInfo.IsValidIndex(SerialNum) is FALSE"));
	}
}

void ASkyscraperGameMode::UpdateSelectInfo(EMeleeSelect MeleeWeapon)
{
	if (PlayerSelectInfo.IsValidIndex(SerialNum))
	{
		PlayerSelectInfo[SerialNum]->PickedMeleeWeapon = MeleeWeapon;
		SendSelectInfo();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerSelectInfo.IsValidIndex(SerialNum) is FALSE"));
	}
}

void ASkyscraperGameMode::UpdateSelectInfo(ERangeSelect RangeWeapon)
{
	if (PlayerSelectInfo.IsValidIndex(SerialNum))
	{
		PlayerSelectInfo[SerialNum]->PickedRangeWeapon = RangeWeapon;
		SendSelectInfo();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerSelectInfo.IsValidIndex(SerialNum) is FALSE"));
	}
}