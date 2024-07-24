// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "HealthBar.generated.h"

class UProgressBar;

UCLASS()
class SKYSCRAPER_API UHealthBar : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(meta = (BindWidget))
		TObjectPtr<UProgressBar> HealthBar;

	UPROPERTY()
		TArray<TObjectPtr<UProgressBar>> HealthBars;

	virtual void NativeConstruct() override;
	
public:
	FORCEINLINE UProgressBar* GetHealthBar() const { return HealthBar; }
	void SetHealthPercent(float Percent);
};
