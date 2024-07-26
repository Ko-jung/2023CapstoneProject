// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBar.h"
#include "Components/ProgressBar.h"
#include "Kismet/KismetMathLibrary.h"

#define MAX_HEALTH_BAR_COUNT 5

void UHealthBar::NativeConstruct()
{
	//HealthBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HealthBar")));
	HealthBar->SetPercent(1.0f);

	for (int i = 0; i < MAX_HEALTH_BAR_COUNT; ++i)
	{
		FString WidgetName = "HealthBar_" + FString::FromInt(i + 1);
		UProgressBar* ProgressBar = Cast<UProgressBar>(GetWidgetFromName(*WidgetName));
		ProgressBar->SetPercent(1.0f);
		HealthBars.Add(ProgressBar);
	}
}

void UHealthBar::SetHealthPercent(float Percent)
{
	if (!(HealthBar && !HealthBars.IsEmpty())) return;

	HealthBar->SetPercent(Percent);

	int MaxHealthCount = static_cast<int> (Percent * MAX_HEALTH_BAR_COUNT);
	UE_LOG(LogTemp, Warning, TEXT("%d"), MaxHealthCount);
	for (int i = 0; i < MAX_HEALTH_BAR_COUNT; ++i)
	{
		HealthBars[i]->SetPercent(0.0f);
	}

	// Max(1.0f) 채우기
	{
		for(int i = 0; i < Percent * MAX_HEALTH_BAR_COUNT; ++i)
		{
			HealthBars[i]->SetPercent(1.0f);
		}
	}

	float RemainPercent = FMath::Fmod(Percent, (1.0f / MAX_HEALTH_BAR_COUNT));
	HealthBars[MaxHealthCount]->SetPercent(RemainPercent*MAX_HEALTH_BAR_COUNT);
}

void UHealthBar::SetFriendlyHealthBar()
{
	bIsFriendly = true;

	for(UProgressBar* ProgressBar : HealthBars)
	{
		ProgressBar->SetFillColorAndOpacity(FLinearColor{ 0.0f,1.0f,0.0f,1.0f });
	}
}