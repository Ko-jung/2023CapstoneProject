// Fill out your copyright notice in the Description page of Project Settings.


#include "RangeWeaponDetail.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

void URangeWeaponDetail::NativeConstruct()
{
	Super::NativeConstruct();
	SMGSelectButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClickSMGSelectButton);
	RifleSelectButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClickRifleSelectButton);
	RPGSelectButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClickRPGSelectButton);

	RangeSwitcher->SetVisibility(ESlateVisibility::Hidden);
}

void URangeWeaponDetail::NativeDestruct()
{
	Super::NativeDestruct();
}


void URangeWeaponDetail::SetSwitcherValue(int32 Value) const
{
	// 현재 켜져있는 버튼일 경우 보이기 끄기
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
}

void URangeWeaponDetail::OnClickRifleSelectButton() 
{
	SetSwitcherValue(1);
}

void URangeWeaponDetail::OnClickRPGSelectButton() 
{
	SetSwitcherValue(2);
}
