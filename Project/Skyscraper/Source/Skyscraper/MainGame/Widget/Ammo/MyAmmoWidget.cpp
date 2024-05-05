// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAmmoWidget.h"

#include "Components/ProgressBar.h"

void UMyAmmoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PB_AmmoBar->SetPercent(1.0f);
}

void UMyAmmoWidget::SetAmmoPercent(int CurrentBulletCount, int MaxBulletCount) const
{
	if(MaxBulletCount != 0 && PB_AmmoBar)
	{
		PB_AmmoBar->SetPercent((float)CurrentBulletCount / (float)MaxBulletCount);
	}
}
