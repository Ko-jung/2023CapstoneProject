// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAmmoWidget.h"

#include "Components/Image.h"
#include "Components/ProgressBar.h"

void UMyAmmoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PB_AmmoBar->SetPercent(0.0f);
}

void UMyAmmoWidget::SetAmmoPercent(int CurrentBulletCount, int MaxBulletCount) const
{
	if(MaxBulletCount != 0 && PB_AmmoBar)
	{
		PB_AmmoBar->SetPercent(1 - (float)CurrentBulletCount / (float)MaxBulletCount);
	}
}

#include "Kismet/KismetSystemLibrary.h"
void UMyAmmoWidget::SetRangeWeapon(ERangeSelect RangeSelect)
{
	if(WeaponTexture.IsValidIndex(static_cast<int>(RangeSelect)))
	{
		UE_LOG(LogTemp, Warning, TEXT("UMyAmmoWidget::SetRangeWeapon RangeSelect: %d, WeaponTexture[static_cast<int>(RangeSelect)]: %s"),
			static_cast<int>(RangeSelect), *UKismetSystemLibrary::GetDisplayName(WeaponTexture[static_cast<int>(RangeSelect)]));
		RangeWeaponImage->SetBrushFromTexture(WeaponTexture[static_cast<int>(RangeSelect)]);
	}
}

void UMyAmmoWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

}
