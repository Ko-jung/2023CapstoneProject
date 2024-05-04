// Copyright Epic Games, Inc. All Rights Reserved.

#include "SkyscraperGameMode.h"
#include "MainGame/Actor/Character/SkyscraperCharacter.h"

#include "Network/NetworkManager.h"
#include "Network/SocketGameInstance.h"
#include "Kismet/GameplayStatics.h"

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
			instance->SetIsConnect(bIsConnected);
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
}

void ASkyscraperGameMode::Tick(float Deltatime)
{
	Super::Tick(Deltatime);

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
	PlayerSelectInfo[SerialNum]->PickedCharacter = Character;
	SendSelectInfo();
}

void ASkyscraperGameMode::UpdateSelectInfo(EMeleeSelect MeleeWeapon)
{
	PlayerSelectInfo[SerialNum]->PickedMeleeWeapon = MeleeWeapon;
	SendSelectInfo();
}

void ASkyscraperGameMode::UpdateSelectInfo(ERangeSelect RangeWeapon)
{
	PlayerSelectInfo[SerialNum]->PickedRangeWeapon = RangeWeapon;
	SendSelectInfo();
}