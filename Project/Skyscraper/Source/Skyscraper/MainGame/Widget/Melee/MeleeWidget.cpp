// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeWidget.h"

#include "Components/Image.h"
#include "Components/ProgressBar.h"

void UMeleeWidget::SetMeleeCooldownPercent(float CurrentCooldownTime, float MaxCooldownTime) const
{
	if(MaxCooldownTime >= FLT_EPSILON && PB_MeleeCooldown)
	{
		PB_MeleeCooldown->SetPercent(CurrentCooldownTime / MaxCooldownTime);
	}
}

void UMeleeWidget::SetMeleeWeapon(EMeleeSelect MeleeSelect)
{
	if(WeaponTexture.IsValidIndex(static_cast<int>(MeleeSelect)))
	{
		MeleeWeaponImage->SetBrushFromTexture(WeaponTexture[static_cast<int>(MeleeSelect)]);
	}
}

void UMeleeWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UMeleeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	for (int i = 0; i < static_cast<int>(EMeleeSelect::EMS_Count); ++i)
	{
		WeaponTexture.AddDefaulted();
	}

	static UTexture2D* NoneTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, L"/Script/Engine.Texture2D'/Game/2016180023/UI/combat/weapon_plate.weapon_plate'"));
	WeaponTexture[static_cast<int>(EMeleeSelect::EMS_NONE)] = NoneTexture;

	static UTexture2D* DaggerTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, L"/Script/Engine.Texture2D'/Game/2016180023/UI/combat/dagger.dagger'"));
	WeaponTexture[static_cast<int>(EMeleeSelect::EMS_Dagger)] = DaggerTexture;

	static UTexture2D* KatanaTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, L"/Script/Engine.Texture2D'/Game/2016180023/UI/combat/katana.katana'"));
	WeaponTexture[static_cast<int>(EMeleeSelect::EMS_Katana)] = KatanaTexture;

	static UTexture2D* SwordTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, L"/Script/Engine.Texture2D'/Game/2016180023/UI/combat/sword.sword'"));
	WeaponTexture[static_cast<int>(EMeleeSelect::EMS_GreatSword)] = SwordTexture;
}
