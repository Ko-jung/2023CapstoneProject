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

	// ����(Ÿ��) �ۼ�Ʈ
	UPROPERTY()
		float RealPercent;
	// ProgressBar ���� �ӵ�(�ð�) // �ʱⰪ 0.5��, 0.5�� ���� ������ ��������
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
