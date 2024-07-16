// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Skyscraper/Enum/EMeleeSelect.h"
#include "MeleeWidget.generated.h"

class UCanvasPanelSlot;
class UTextBlock;
class UHorizontalBox;
class UImage;
class UProgressBar;
/**
 * 
 */
UCLASS()
class SKYSCRAPER_API UMeleeWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetMeleeCooldownPercent(float CurrentCooldownTime, float MaxCooldownTime) const;

	void SetMeleeWeapon(EMeleeSelect MeleeSelect);

	void InitHitCountFunc();
	void HitSizeChangeFunc();
	void AddHitCount();
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

private:
public:
protected:
	UPROPERTY(meta = (BindWidget))
		UProgressBar* PB_MeleeCooldown;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		TObjectPtr<UImage> MeleeWeaponImage;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		TObjectPtr<UHorizontalBox> HitTextBox;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		TObjectPtr<UTextBlock> HitCountText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		TObjectPtr<UTextBlock> HitText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponTexture")
		TArray<TObjectPtr<UTexture2D>> WeaponTexture;

	int HitCount = 0;

	float InitHitCountTime = 3.0f;
	float CurrentInitHitCountTime = 0.0f;
	float TimeOffset = 0.05f;
	float CurrentHitSizeChangeTime = 0.0f;


	// Timer Handle
	FTimerHandle HitTextSizeChangeTimerHandle;
	FTimerHandle InitHitCountTimerHandle;

	// Curve Data
	UPROPERTY()
		TObjectPtr<UCurveFloat> HitSizeCurve;
	UPROPERTY()
		TObjectPtr<UCurveFloat> HitTextAlphaCurve;
private:
};
