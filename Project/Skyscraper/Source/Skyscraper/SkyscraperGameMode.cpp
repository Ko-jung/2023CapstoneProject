// Copyright Epic Games, Inc. All Rights Reserved.

#include "SkyscraperGameMode.h"
#include "SkyscraperCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASkyscraperGameMode::ASkyscraperGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	{
		//DefaultPawnClass = PlayerPawnBPClass.Class;
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
