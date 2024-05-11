// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeWeaponWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Skyscraper/MainGame/Core/SkyscraperPlayerController.h"

void UChangeWeaponWidget::InitializeWeaponState(EMeleeSelect NowMeleeSelect, ERangeSelect NowRangeSelect)
{
	ChangeMeleeWeapon(NowMeleeSelect);
	ChangeRangeWeapon(NowRangeSelect);
}

void UChangeWeaponWidget::ChangeMeleeWeapon(EMeleeSelect NewMeleeSelect)
{
	CurrentMeleeSelect = NewMeleeSelect;

	for(int i =0; i<(int8)EMeleeSelect::EMS_NONE; ++i)
	{
		MeleeButton[i]->SetBackgroundColor(FLinearColor::White);
	}

	MeleeButton[(int8)CurrentMeleeSelect]->SetBackgroundColor(FLinearColor::FromSRGBColor(FColor(125, 125, 125)));

	OwnerPlayerController->ChangePlayerMeleeWeapon(NewMeleeSelect);
}

void UChangeWeaponWidget::ChangeRangeWeapon(ERangeSelect NewRangeSelect)
{
	CurrentRangeSelect = NewRangeSelect;

	for (int i = 0; i < (int8)ERangeSelect::ERS_NONE; ++i)
	{
		RangeButton[i]->SetBackgroundColor(FLinearColor::White);
	}

	RangeButton[(int8)CurrentMeleeSelect]->SetBackgroundColor(FLinearColor::FromSRGBColor(FColor(125, 125, 125)));

	OwnerPlayerController->ChangePlayerRangeWeapon(NewRangeSelect);
}

void UChangeWeaponWidget::OnClickMeleeToDagger()
{
	ChangeMeleeWeapon(EMeleeSelect::EMS_Dagger);
}

void UChangeWeaponWidget::OnClickMeleeToKatana()
{
	ChangeMeleeWeapon(EMeleeSelect::EMS_Katana);
}

void UChangeWeaponWidget::OnClickMeleeToSword()
{
	ChangeMeleeWeapon(EMeleeSelect::EMS_GreatSword);
}

void UChangeWeaponWidget::OnClickRangeToSMG()
{
	ChangeRangeWeapon(ERangeSelect::ERS_SMG);
}

void UChangeWeaponWidget::OnClickRangeToRifle()
{
	ChangeRangeWeapon(ERangeSelect::ERS_Rifle);
}

void UChangeWeaponWidget::OnClickRangeToRPG()
{
	ChangeRangeWeapon(ERangeSelect::ERS_RPG);
}

void UChangeWeaponWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	DaggerButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClickMeleeToDagger);
	KatanaButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClickMeleeToKatana);
	SwordButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClickMeleeToSword);
	SMGButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClickRangeToSMG);
	RifleButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClickRangeToRifle);
	RPGButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClickRangeToRPG);

	MeleeButton.Add(DaggerButton);
	MeleeButton.Add(KatanaButton);
	MeleeButton.Add(SwordButton);

	RangeButton.Add(SMGButton);
	RangeButton.Add(RifleButton);
	RangeButton.Add(RPGButton);

}

void UChangeWeaponWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OwnerPlayerController = Cast<ASkyscraperPlayerController>(GetOwningPlayer());
	OwnerPlayerController->SetShowMouseCursor(true);
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(OwnerPlayerController);
	
}

void UChangeWeaponWidget::NativeDestruct()
{
	Super::NativeDestruct();

	OwnerPlayerController->SetShowMouseCursor(false);
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(OwnerPlayerController);
}
