// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"

#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HudScreenWidget = CreateWidget(this, HudWidget);
	if(HudScreenWidget)
	{
		HudScreenWidget->AddToViewport();
	}
}

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	
	HudScreenWidget->RemoveFromParent();
	if(bIsWinner)
	{
		TObjectPtr<UUserWidget> WinScreenWidget = CreateWidget(this, WinWidget);
		if (WinScreenWidget)
		{
			WinScreenWidget->AddToViewport();
		}
		
	}else
	{
		TObjectPtr<UUserWidget> LoseScreenWidget = CreateWidget(this, LoseWidget);
		if(LoseScreenWidget)
		{
			LoseScreenWidget->AddToViewport();
		}
		
	}
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}


