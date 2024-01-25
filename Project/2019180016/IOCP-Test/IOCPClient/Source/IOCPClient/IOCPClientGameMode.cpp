// Copyright Epic Games, Inc. All Rights Reserved.

#include "IOCPClientGameMode.h"
#include "IOCPClientCharacter.h"
#include "UObject/ConstructorHelpers.h"

AIOCPClientGameMode::AIOCPClientGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
