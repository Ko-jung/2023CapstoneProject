// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skyscraper/SkyscraperWidget/SkyscraperWidget.h"
#include "Skyscraper/Enum/ECharacterSelect.h"

#include "LobbyWidget.generated.h"

class UButton;
class UTextBlock;

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API ULobbyWidget : public USkyscraperWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual bool Initialize();

	void SpawnNewCharacter(ECharacterSelect ECharacter);

	UFUNCTION()
	void OnMatchingButtonClick();

	UFUNCTION()
	void OnDaggerButtonClick();		
	UFUNCTION()
	void OnKatanaButtonClick();		
	UFUNCTION()
	void OnGreatSwordButtonClick();	
	UFUNCTION()
	void OnSMGButtonClick();		
	UFUNCTION()
	void OnRifleButtonClick();		
	UFUNCTION()
	void OnRPGButtonClick();
									
	UFUNCTION()
	void OnAssasinButtonClick();	
	UFUNCTION()
	void OnBoomerangButtonClick();	
	UFUNCTION()
	void OnElectricButtonClick();	
	UFUNCTION()
	void OnRadarButtonClick();		
	UFUNCTION()
	void OnShieldButtonClick();		
	UFUNCTION()
	void OnWindButtonClick();

	void UpdateMatchingTimer();

	bool IsMatching;

	UPROPERTY(BlueprintReadWrite)
	TMap<ECharacterSelect, TSubclassOf<class ASkyscraperCharacter>> Characters;
private:
	class ALobbyMode* LobbyGameMode;

	FDateTime MatchingStartTime;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MatchingTimer;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MatchingText;

	UPROPERTY(meta = (BindWidget))
	UButton* MatchingBtn;

	UPROPERTY(meta = (BindWidget))
	UButton* DaggerBtn;
	UPROPERTY(meta = (BindWidget))
	UButton* KatanaBtn;
	UPROPERTY(meta = (BindWidget))
	UButton* GreatSwordBtn;

	UPROPERTY(meta = (BindWidget))
	UButton* SMGBtn;
	UPROPERTY(meta = (BindWidget))
	UButton* RifleBtn;
	UPROPERTY(meta = (BindWidget))
	UButton* RPGBtn;

	UPROPERTY(meta = (BindWidget))
	UButton* AssasinBtn;
	UPROPERTY(meta = (BindWidget))
	UButton* BoomerangBtn;
	UPROPERTY(meta = (BindWidget))
	UButton* ElectricBtn;
	UPROPERTY(meta = (BindWidget))
	UButton* RadarBtn;
	UPROPERTY(meta = (BindWidget))
	UButton* ShieldBtn;
	UPROPERTY(meta = (BindWidget))
	UButton* WindBtn;
};
