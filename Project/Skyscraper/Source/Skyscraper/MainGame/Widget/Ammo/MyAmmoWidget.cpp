// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAmmoWidget.h"

#include "Components/Image.h"
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

void UMyAmmoWidget::SetRangeWeapon(ERangeSelect RangeSelect)
{
	if(WeaponTexture.IsValidIndex(static_cast<int>(RangeSelect)))
	{
		RangeWeaponImage->SetBrushFromTexture(WeaponTexture[static_cast<int>(RangeSelect)]);
	}
}

void UMyAmmoWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	for (int i = 0; i < (int8)ERangeSelect::ERS_COUNT; ++i)
	{
		WeaponTexture.AddDefaulted();
	}

	static UTexture2D* NoneTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, L"/Script/Engine.Texture2D'/Game/2016180023/UI/combat/weapon_plate.weapon_plate'"));
	WeaponTexture[static_cast<int>(ERangeSelect::ERS_NONE)] = NoneTexture;

	static UTexture2D* SMGTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, L"/Script/Engine.Texture2D'/Game/2016180023/UI/combat/smg.smg'"));
	WeaponTexture[static_cast<int>(ERangeSelect::ERS_SMG)] = SMGTexture;

	static UTexture2D* RifleTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, L"/Script/Engine.Texture2D'/Game/2016180023/UI/combat/ar.ar'"));
	WeaponTexture[static_cast<int>(ERangeSelect::ERS_Rifle)] = RifleTexture;

	static UTexture2D* RPGTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, L"/Script/Engine.Texture2D'/Game/2016180023/UI/combat/rpg.rpg'"));
	WeaponTexture[static_cast<int>(ERangeSelect::ERS_RPG)] = RPGTexture;
}
