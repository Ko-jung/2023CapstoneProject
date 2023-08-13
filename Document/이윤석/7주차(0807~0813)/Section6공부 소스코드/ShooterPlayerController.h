// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

class UUserWidget;
/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void GameHasEnded(AActor* EndGameFocus, bool bIsWinner) override;
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere)
	float RestartDelay=1.0f;

	FTimerHandle RestartTimer;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HudWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LoseWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WinWidget;

	UPROPERTY()
	TObjectPtr<UUserWidget> HudScreenWidget;

};
