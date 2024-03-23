// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeWeaponDetail.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Widgets/Input/SButton.h"

void UMeleeWeaponDetail::NativeConstruct()
{
	Super::NativeConstruct();
	DaggerSelectButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClickDaggerButton);
	KatanaSelectButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClickKatanaButton);
	GreatSwordButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClickGreatSwordButton);

	MeleeSwitcher->SetVisibility(ESlateVisibility::Hidden);
}

void UMeleeWeaponDetail::NativeDestruct()
{
	Super::NativeDestruct();
}


void UMeleeWeaponDetail::SetSwitcherValue(int32 Value) const
{
	// ���� �����ִ� ��ư�� ��� ���̱� ���
	if (MeleeSwitcher->GetActiveWidgetIndex() == Value && MeleeSwitcher->GetVisibility() == ESlateVisibility::Visible)
	{
		MeleeSwitcher->SetVisibility(ESlateVisibility::Hidden);
		return;
	}
	MeleeSwitcher->SetVisibility(ESlateVisibility::Visible);
	MeleeSwitcher->SetActiveWidgetIndex(Value);
}

void UMeleeWeaponDetail::OnClickDaggerButton() 
{
	SetSwitcherValue(0);
}

void UMeleeWeaponDetail::OnClickKatanaButton() 
{
	SetSwitcherValue(1);
}

void UMeleeWeaponDetail::OnClickGreatSwordButton() 
{
	SetSwitcherValue(2);
}

