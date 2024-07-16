// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Skyscraper/Enum/EMeleeSelect.h"
#include "MeleeWidget.generated.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponTexture")
		TArray<TObjectPtr<UTexture2D>> WeaponTexture;
private:
};
