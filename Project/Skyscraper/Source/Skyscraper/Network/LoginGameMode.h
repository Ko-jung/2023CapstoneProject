// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetworkGameMode.h"

#include "LoginGameMode.generated.h"

class ULoginWidget;

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API ALoginGameMode : public ANetworkGameMode
{
	GENERATED_BODY()

public:
	ALoginGameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void ProcessFunc();

	UPROPERTY()
	TSubclassOf<ULoginWidget> LoginWidgetClass;
	UPROPERTY()
	ULoginWidget* LoginWidget;
};
