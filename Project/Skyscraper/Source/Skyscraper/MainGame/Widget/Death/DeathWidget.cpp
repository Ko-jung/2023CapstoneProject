// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathWidget.h"

#include "Components/Button.h"
#include "Skyscraper/MainGame/Core/SkyscraperPlayerController.h"

void UDeathWidget::SetToSpectatorMode()
{
	SpectatorButton->SetVisibility(ESlateVisibility::Hidden);
	WeaponSelectButton->SetVisibility(ESlateVisibility::Visible);

	OwnerPlayerController->PressSetSpecatatorButton();
}

void UDeathWidget::SetToWeaponSelectMode()
{
	SpectatorButton->SetVisibility(ESlateVisibility::Visible);
	WeaponSelectButton->SetVisibility(ESlateVisibility::Hidden);

	OwnerPlayerController->PressChangeWeaponButton();
}

void UDeathWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SpectatorButton->OnClicked.AddUniqueDynamic(this, &ThisClass::SetToSpectatorMode);
	WeaponSelectButton->OnClicked.AddUniqueDynamic(this, &ThisClass::SetToWeaponSelectMode);

	OwnerPlayerController = Cast<ASkyscraperPlayerController>(GetOwningPlayer());
}
