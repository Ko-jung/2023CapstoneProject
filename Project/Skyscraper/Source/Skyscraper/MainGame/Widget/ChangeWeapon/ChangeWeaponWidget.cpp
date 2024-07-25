// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeWeaponWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Engine/Canvas.h"
#include "Skyscraper/MainGame/Core/SkyscraperPlayerController.h"

#include "Skyscraper/Network/MainGameMode.h"
#include "Kismet/GameplayStatics.h"

void UChangeWeaponWidget::InitializeWeaponState(EMeleeSelect NowMeleeSelect, ERangeSelect NowRangeSelect)
{
	
	CurrentMeleeSelect = (NowMeleeSelect);
	CurrentRangeSelect = (NowRangeSelect);
}

void UChangeWeaponWidget::SetChangeWeaponWidgetVisibility(ESlateVisibility NewVisibility)
{
	WeaponSelectCanvas->SetVisibility(NewVisibility);
}

void UChangeWeaponWidget::FindButtonData()
{
	MeleeButton.Add(DaggerButton);
	MeleeButton.Add(KatanaButton);
	MeleeButton.Add(SwordButton);

	RangeButton.Add(SMGButton);
	RangeButton.Add(RifleButton);
	RangeButton.Add(RPGButton);
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

	if (AMainGameMode* GameMode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(OwnerPlayerController)))
	{
		GameMode->ChangeMeleeWeapon(NewMeleeSelect);
	}
}

void UChangeWeaponWidget::ChangeRangeWeapon(ERangeSelect NewRangeSelect)
{
	CurrentRangeSelect = NewRangeSelect;

	for (int i = 0; i < (int8)ERangeSelect::ERS_NONE; ++i)
	{
		RangeButton[i]->SetBackgroundColor(FLinearColor::White);
	}

	RangeButton[(int8)CurrentRangeSelect]->SetBackgroundColor(FLinearColor::FromSRGBColor(FColor(125, 125, 125)));

	OwnerPlayerController->ChangePlayerRangeWeapon(NewRangeSelect);

	if (AMainGameMode* GameMode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(OwnerPlayerController)))
	{
		GameMode->ChangeRangeWeapon(NewRangeSelect);
	}
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


}

void UChangeWeaponWidget::NativeConstruct()
{
	Super::NativeConstruct();

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

	OwnerPlayerController = Cast<ASkyscraperPlayerController>(GetOwningPlayer());
	OwnerPlayerController->SetShowMouseCursor(true);
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(OwnerPlayerController);

	
	ChangeMeleeWeapon(CurrentMeleeSelect);
	ChangeRangeWeapon(CurrentRangeSelect);
	
}

void UChangeWeaponWidget::NativeDestruct()
{
	Super::NativeDestruct();

	OwnerPlayerController->SetShowMouseCursor(false);
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(OwnerPlayerController);
}
