// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JetpackGaugeBar.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class SKYSCRAPER_API UJetpackGaugeBar : public UUserWidget
{
	GENERATED_BODY()
private:
	// == Border variable
	UPROPERTY(meta = (BindWidget))
		UProgressBar* PB_GaugeBar;

	// 실제(타겟) 퍼센트
	UPROPERTY()
		float RealPercent;
	// ProgressBar 보간 속도(시간) // 초기값 0.5로, 0.5초 내에 보간이 끝내도록
	UPROPERTY(EditAnywhere)
		float InterpTime;
	UPROPERTY()
		bool bDoInterpGauge;

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	FORCEINLINE UProgressBar* GetGaugeBar() const { return PB_GaugeBar; }
	float GetJetpackGaugePercent() const;
	void SetJetpackGaugePercent(float Percent);
	
};
