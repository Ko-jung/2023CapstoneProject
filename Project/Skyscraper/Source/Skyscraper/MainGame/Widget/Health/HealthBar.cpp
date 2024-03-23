// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBar.h"

#include "Components/ProgressBar.h"

void UHealthBar::NativeConstruct()
{
	HealthBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HealthBar")));
	HealthBar->SetPercent(1.0f);
}

void UHealthBar::SetHealthPercent(float Percent)
{
	HealthBar->SetPercent(Percent);
}
