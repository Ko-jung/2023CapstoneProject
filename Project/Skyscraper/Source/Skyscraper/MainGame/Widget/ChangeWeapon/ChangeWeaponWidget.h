// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Skyscraper/Enum/EMeleeSelect.h"
#include "Skyscraper/Enum/ERangeSelect.h"
#include "ChangeWeaponWidget.generated.h"

class UCanvasPanel;
class ASkyscraperPlayerController;
class UButton;
/**
 * 
 */
UCLASS()
class SKYSCRAPER_API UChangeWeaponWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	void InitializeWeaponState(EMeleeSelect NowMeleeSelect, ERangeSelect NowRangeSelect);

	void SetChangeWeaponWidgetVisibility(ESlateVisibility NewVisibility);

protected:
	void FindButtonData();
	void ChangeMeleeWeapon(EMeleeSelect NewMeleeSelect);
	void ChangeRangeWeapon(ERangeSelect NewRangeSelect);

	UFUNCTION()
	void OnClickMeleeToDagger();
	UFUNCTION()
	void OnClickMeleeToKatana();
	UFUNCTION()
	void OnClickMeleeToSword();
	UFUNCTION()
	void OnClickRangeToSMG();
	UFUNCTION()
	void OnClickRangeToRifle();
	UFUNCTION()
	void OnClickRangeToRPG();

	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;
private:

public:

protected:
	UPROPERTY()
		TArray<UButton*> MeleeButton;
	UPROPERTY()
		TArray<UButton*> RangeButton;

	UPROPERTY(meta = (BindWidget))
		UButton* DaggerButton;
	UPROPERTY(meta = (BindWidget))
		UButton* KatanaButton;
	UPROPERTY(meta = (BindWidget))
		UButton* SwordButton;
	UPROPERTY(meta = (BindWidget))
		UButton* SMGButton;
	UPROPERTY(meta = (BindWidget))
		UButton* RifleButton;
	UPROPERTY(meta = (BindWidget)) 
		UButton* RPGButton;

	UPROPERTY(meta = (BindWidget))
		UCanvasPanel* WeaponSelectCanvas;

	UPROPERTY()
		TObjectPtr<ASkyscraperPlayerController> OwnerPlayerController;
		
private:
	UPROPERTY()
		EMeleeSelect CurrentMeleeSelect;
	UPROPERTY()
		ERangeSelect CurrentRangeSelect;
};
