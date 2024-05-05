// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyAmmoWidget.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class SKYSCRAPER_API UMyAmmoWidget : public UUserWidget
{
	GENERATED_BODY()
	// == Border variable
	UPROPERTY(meta = (BindWidget))
	UProgressBar* PB_AmmoBar;

	

	virtual void NativeConstruct() override;

public:
	FORCEINLINE UProgressBar* GetAmmoBar() const { return PB_AmmoBar; }
	void SetAmmoPercent(int CurrentBulletCount, int MaxBulletCount) const;
};
