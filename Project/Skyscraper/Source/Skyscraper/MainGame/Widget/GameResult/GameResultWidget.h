// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameResultWidget.generated.h"

class ASkyscraperPlayerController;
class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class SKYSCRAPER_API UGameResultWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetWinnerText(const bool IsWin) const;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
		void GoToLobby();
	

private:

public:
protected:
	UPROPERTY(meta = (BindWidget))
		UTextBlock* WinnerText;

	UPROPERTY(meta = (BindWidget))
		UButton* ToLobbyButton;

	UPROPERTY()
		TObjectPtr<ASkyscraperPlayerController> OwnerPlayerController;
private:
};
