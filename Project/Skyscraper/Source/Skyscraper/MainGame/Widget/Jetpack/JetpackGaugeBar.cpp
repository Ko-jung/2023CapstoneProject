// Fill out your copyright notice in the Description page of Project Settings.


#include "JetpackGaugeBar.h"

#include "Components/ProgressBar.h"
#include "Kismet/KismetMathLibrary.h"

void UJetpackGaugeBar::NativeConstruct()
{
	Super::NativeConstruct();

	PB_GaugeBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_GaugeBar")));
	PB_GaugeBar->SetPercent(1.0f);

	bDoInterpGauge = false;
	InterpTime = 0.2;
}

void UJetpackGaugeBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(bDoInterpGauge)
	{
		if(PB_GaugeBar)
		{
			float NewPercent = UKismetMathLibrary::FInterpTo(
				PB_GaugeBar->GetPercent(), RealPercent, InDeltaTime, 1/InterpTime);
			// 보간 완료
			if (abs(RealPercent - NewPercent) <= FLT_EPSILON)
			{
				bDoInterpGauge = false;
			}
			PB_GaugeBar->SetPercent(NewPercent);
		}
		
	}
}

float UJetpackGaugeBar::GetJetpackGaugePercent() const
{
	if(PB_GaugeBar)
	{
		//return PB_GaugeBar->GetPercent();
		return RealPercent;
	}

	return 0.0f;
}

void UJetpackGaugeBar::SetJetpackGaugePercent(float Percent)
{
	if(PB_GaugeBar)
	{
		bDoInterpGauge = true;
		//PB_GaugeBar->SetPercent(Percent);
		RealPercent = Percent;
	}
}

