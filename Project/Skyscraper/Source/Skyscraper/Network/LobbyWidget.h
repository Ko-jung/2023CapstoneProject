// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidget.generated.h"

class UButton;
class UTextBlock;

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual bool Initialize();

	UFUNCTION()
	void OnMatchingButtonClick();

	void UpdateMatchingTimer();

	bool IsMatching;
private:
	class ALobbyMode* LobbyGameMode;

	FDateTime MatchingStartTime;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MatchingTimer;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MatchingText;

	UPROPERTY(meta = (BindWidget))
	UButton* MatchingBtn;
};
