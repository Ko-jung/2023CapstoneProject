// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DeathWidget.generated.h"

class ASkyscraperPlayerController;
class UButton;

UCLASS()
class SKYSCRAPER_API UDeathWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
protected:
	UFUNCTION()
	void SetToSpectatorMode();
	UFUNCTION()
	void SetToWeaponSelectMode();
	virtual void NativeConstruct() override;

private:

public:
protected:
	// 무기 선택 모드 버튼
	UPROPERTY(meta = (BindWidget))
		TObjectPtr<UButton> WeaponSelectButton;

	// 관전 모드 버튼
	UPROPERTY(meta = (BindWidget))
		TObjectPtr<UButton> SpectatorButton;

	UPROPERTY()
		TObjectPtr<ASkyscraperPlayerController> OwnerPlayerController;

private:
};
