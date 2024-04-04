// Copyright Epic Games, Inc. All Rights Reserved.

#include "SkyscraperGameMode.h"
#include "MainGame/Actor/Character/SkyscraperCharacter.h"

#include "NetworkManager.h"
#include "SocketGameInstance.h"
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
	std::pair<EFunction, Packet*> EFunc;
	while (FuncQueue.try_pop(EFunc))
	{
		EFunction func = EFunc.first;
		Packet* argu = EFunc.second;

		switch (func)
		{
		case EBPPOSSESS:
		{
			PPlayerJoin PPJ;
			memcpy(&PPJ, argu, sizeof(PPlayerJoin));
			Super::SetOwnSerialNum(PPJ.PlayerSerial);
		}
			break;
		case EPLAYERSELECTINFO:
			ProcessSelectInfo(argu);
			break;
		case ESETTIMER:
		{
			PSetTimer PST;
			memcpy(&PST, argu, sizeof(PST));

			PSetTimer* PST2 = static_cast<PSetTimer*>(argu);
			memcpy(PST2, argu, sizeof(*PST2));

			SelectTimer = PST.SecondsUntilActivation;
			UE_LOG(LogTemp, Warning, TEXT("New Timer Set! Time is %d Sec"), SelectTimer);
		}
			break;
		case ESTARTGAME:
		{
			USocketGameInstance* instance = static_cast<USocketGameInstance*>(GetGameInstance());
			instance->SetSelectInfo(PlayerSelectInfo);
			instance->SetSocket(m_Socket);
			instance->SetIsConnect(bIsConnected);
			instance->SetSerialNum(SerialNum);
			UGameplayStatics::OpenLevel(this, FName("SocketMainGameLevel"));
		}
			break;
		default:
			break;
		}

		delete argu;
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

	// Why 127?
	ECharacter   Character   = PPP->PickedCharacter;
	EMeleeWeapon MeleeWeapon = PPP->PickedMeleeWeapon;
	ERangeWeapon RangeWeapon = PPP->PickedRangeWeapon;

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

void ASkyscraperGameMode::UpdateSelectInfo(ECharacter Character)
{
	PlayerSelectInfo[SerialNum]->PickedCharacter = Character;
	SendSelectInfo();
}

void ASkyscraperGameMode::UpdateSelectInfo(EMeleeWeapon MeleeWeapon)
{
	PlayerSelectInfo[SerialNum]->PickedMeleeWeapon = MeleeWeapon;
	SendSelectInfo();
}

void ASkyscraperGameMode::UpdateSelectInfo(ERangeWeapon RangeWeapon)
{
	PlayerSelectInfo[SerialNum]->PickedRangeWeapon = RangeWeapon;
	SendSelectInfo();
}