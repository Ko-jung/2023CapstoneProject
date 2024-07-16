// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Skyscraper/Enum/ERangeSelect.h"
#include "MyAmmoWidget.generated.h"

class UTextBlock;
class UImage;
class UProgressBar;
/**
 * 
 */
UCLASS()
class SKYSCRAPER_API UMyAmmoWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	FORCEINLINE UProgressBar* GetAmmoBar() const { return PB_AmmoBar; }
	void SetAmmoPercent(int CurrentBulletCount, int MaxBulletCount) const;

	void SetRangeWeapon(ERangeSelect RangeSelect);
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

private:
public:
protected:
	UPROPERTY(meta = (BindWidget))
		UProgressBar* PB_AmmoBar;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		TObjectPtr<UImage> RangeWeaponImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponTexture")
		TArray<TObjectPtr<UTexture2D>> WeaponTexture;
private:
};
