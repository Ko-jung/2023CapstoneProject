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
	// == Border variable
	UPROPERTY(meta = (BindWidget))
		UProgressBar* HealthBar;

	virtual void NativeConstruct() override;
	
public:
	FORCEINLINE UProgressBar* GetHealthBar() const { return HealthBar; }
	void SetHealthPercent(float Percent);
};
