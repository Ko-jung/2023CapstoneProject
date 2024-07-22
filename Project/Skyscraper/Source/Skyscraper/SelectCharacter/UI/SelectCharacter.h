// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SelectCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API USelectCharacter : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SetPlayerIDs(TArray<FString> IDs, int SerialNum);

	UPROPERTY(meta=(BindWidget))
	class UCharacterPickState* WBP_CharacterPickState;
};
