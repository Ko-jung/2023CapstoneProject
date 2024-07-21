// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectCharacter.h"
#include "Skyscraper/SelectCharacter/UI/CharacterPickState.h"

void USelectCharacter::SetPlayerIDs(TArray<FString> IDs, int SerialNum)
{
	if (WBP_CharacterPickState)
	{
		WBP_CharacterPickState->SetPlayerIDs(IDs, SerialNum);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("USelectCharacter::SetPlayerIDs WBP_CharacterPickState is nullptr"));
	}
}
