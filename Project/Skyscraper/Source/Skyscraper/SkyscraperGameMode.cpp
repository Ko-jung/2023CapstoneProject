// Copyright Epic Games, Inc. All Rights Reserved.

#include "SkyscraperGameMode.h"
#include "MainGame/Actor/Character/SkyscraperCharacter.h"

#include "UObject/ConstructorHelpers.h"

ASkyscraperGameMode::ASkyscraperGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	{
		//DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	PlayerSelectInfo.Init(new PPlayerSelectInfo(), MAXPLAYER);

	int i = 0;
	for (auto& P : PlayerSelectInfo)
	{
		P->ClientNum = i++;
	}
}

void ASkyscraperGameMode::ProcessFunc()
{
	std::pair<EFunction, Packet> EFunc;
	while (FuncQueue.try_pop(EFunc))
	{
		EFunction func = EFunc.first;
		Packet argu = EFunc.second;

		switch (func)
		{
		case EBPPOSSESS:
		{
			PPlayerJoin PPJ;
			memcpy(&PPJ, &argu, sizeof(PPlayerJoin));
			SetOwnSerialNum(PPJ.PlayerSerial);
		}
			break;
		case EPLAYERSELECTINFO:
			ProcessSelectInfo(&argu);
			break;
		default:
			break;
		}
	}
}

void ASkyscraperGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ASkyscraperGameMode::Tick(float Deltatime)
{
	Super::Tick(Deltatime);
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

	ECharacter   Character   = PPP->PickedCharacter;
	EMeleeWeapon MeleeWeapon = PPP->PickedMeleeWeapon;
	ERangeWeapon RangeWeapon = PPP->PickedRangeWeapon;

	PlayerSelectInfo[ClientNum]->PickedCharacter	 = Character  ;
	PlayerSelectInfo[ClientNum]->PickedMeleeWeapon	 = MeleeWeapon;
	PlayerSelectInfo[ClientNum]->PickedRangeWeapon	 = RangeWeapon;
}

void ASkyscraperGameMode::UpdateSelectInfo(ECharacter Character)
{
	PlayerSelectInfo[m_SerialNum]->PickedCharacter = Character;
}

void ASkyscraperGameMode::UpdateSelectInfo(EMeleeWeapon MeleeWeapon)
{
	PlayerSelectInfo[m_SerialNum]->PickedMeleeWeapon = MeleeWeapon;
}

void ASkyscraperGameMode::UpdateSelectInfo(ERangeWeapon RangeWeapon)
{
	PlayerSelectInfo[m_SerialNum]->PickedRangeWeapon = RangeWeapon;
}