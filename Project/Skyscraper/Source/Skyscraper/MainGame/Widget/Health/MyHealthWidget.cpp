// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHealthWidget.h"

#include "Components/ProgressBar.h"
#include "Kismet/KismetMathLibrary.h"

void UMyHealthWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	//PB_HealthBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HealthBar")));
	PB_HealthBar->SetPercent(1.0f);

	//PB_DeleteHealthBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_DeleteHealthBar")));
	PB_DeleteHealthBar->SetPercent(1.0f);

	bDoInterpGauge = false;
	InterpTime = 0.2;
}

void UMyHealthWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bDoInterpGauge)
	{
		if (PB_HealthBar && PB_DeleteHealthBar)
		{
			float NewPercent = UKismetMathLibrary::FInterpTo(
				PB_DeleteHealthBar->GetPercent(), PB_HealthBar->GetPercent(), InDeltaTime, 1 / InterpTime);
			// 보간 완료
			if (abs(PB_HealthBar->GetPercent() - NewPercent) <= FLT_EPSILON)
			{
				bDoInterpGauge = false;
			}
			PB_DeleteHealthBar->SetPercent(NewPercent);
		}

	}
}

float UMyHealthWidget::GetHealthPercent() const
{
	if (PB_HealthBar)
	{
		return PB_HealthBar->GetPercent();
	}

	return 0.0f;
}

void UMyHealthWidget::SetHealthPercent(float Percent)
{
	if (PB_HealthBar)
	{
		bDoInterpGauge = true;
		PB_HealthBar->SetPercent(Percent);
	}
}
