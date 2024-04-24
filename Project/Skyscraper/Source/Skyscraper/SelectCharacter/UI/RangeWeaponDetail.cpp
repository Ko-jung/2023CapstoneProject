// Fill out your copyright notice in the Description page of Project Settings.


#include "RangeWeaponDetail.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

#include "Kismet/GameplayStatics.h"
#include "Skyscraper/SkyscraperGameMode.h"

void URangeWeaponDetail::NativeConstruct()
{
	Super::NativeConstruct();
	SMGSelectButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClickSMGSelectButton);
	RifleSelectButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClickRifleSelectButton);
	RPGSelectButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClickRPGSelectButton);

	RangeSwitcher->SetVisibility(ESlateVisibility::Hidden);

	auto gamemode = UGameplayStatics::GetGameMode(this);
	Gamemode = static_cast<ASkyscraperGameMode*>(gamemode);
}

void URangeWeaponDetail::NativeDestruct()
{
	Super::NativeDestruct();
}


void URangeWeaponDetail::SetSwitcherValue(int32 Value) const
{
	// ���� �����ִ� ��ư�� ��� ���̱� ���
	if (RangeSwitcher->GetActiveWidgetIndex() == Value && RangeSwitcher->GetVisibility() == ESlateVisibility::Visible)
	{
		RangeSwitcher->SetVisibility(ESlateVisibility::Hidden);
		return;
	}
	RangeSwitcher->SetVisibility(ESlateVisibility::Visible);
	RangeSwitcher->SetActiveWidgetIndex(Value);
}

void URangeWeaponDetail::OnClickSMGSelectButton() 
{
	SetSwitcherValue(0);

	Gamemode->UpdateSelectInfo(ERangeSelect::ERS_SMG);
}

void URangeWeaponDetail::OnClickRifleSelectButton() 
{
	SetSwitcherValue(1);

	Gamemode->UpdateSelectInfo(ERangeSelect::ERS_Rifle);
}

void URangeWeaponDetail::OnClickRPGSelectButton()
{
	SetSwitcherValue(2);

	Gamemode->UpdateSelectInfo(ERangeSelect::ERS_RPG);
}
