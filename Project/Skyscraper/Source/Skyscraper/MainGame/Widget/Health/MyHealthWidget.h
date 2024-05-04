// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyHealthWidget.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class SKYSCRAPER_API UMyHealthWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(meta = (BindWidget))
		UProgressBar* PB_HealthBar;

	UPROPERTY(meta = (BindWidget))
		UProgressBar* PB_DeleteHealthBar;

	// ProgressBar 보간 속도(시간) // 초기값 0.5로, 0.5초 내에 보간이 끝내도록
	UPROPERTY(EditAnywhere)
		float InterpTime;
	UPROPERTY()
		bool bDoInterpGauge;

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	float GetHealthPercent() const;
	void SetHealthPercent(float Percent);
};
