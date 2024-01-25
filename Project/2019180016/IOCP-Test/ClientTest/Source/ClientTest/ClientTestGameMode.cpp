// Copyright Epic Games, Inc. All Rights Reserved.

#include "ClientTestGameMode.h"
#include "ClientTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AClientTestGameMode::AClientTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
