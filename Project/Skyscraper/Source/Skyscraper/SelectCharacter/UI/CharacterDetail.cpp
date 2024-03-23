// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterDetail.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

void UCharacterDetail::NativeConstruct()
{
	Super::NativeConstruct();
	SelectShieldButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClickSelectShieldButton);
	SelectWindButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClickSelectWindButton);
	SelectElectricButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClickSelectElectricButton);
	SelectThrowButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClickSelectThrowButton);
	SelectAssassinButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClickSelectAssassinButton);
	SelectDetectionButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClickSelectDetectionButton);

	CharacterDetailSwitcher->SetVisibility(ESlateVisibility::Hidden);
}

void UCharacterDetail::NativeDestruct()
{
	Super::NativeDestruct();
}


void UCharacterDetail::SetSwitcherValue(int32 Value) const
{
	// ���� �����ִ� ��ư�� ��� ���̱� ���
	if (CharacterDetailSwitcher->GetActiveWidgetIndex() == Value && CharacterDetailSwitcher->GetVisibility() == ESlateVisibility::Visible)
	{
		CharacterDetailSwitcher->SetVisibility(ESlateVisibility::Hidden);
		return;
	}
	CharacterDetailSwitcher->SetVisibility(ESlateVisibility::Visible);
	CharacterDetailSwitcher->SetActiveWidgetIndex(Value);
}


void UCharacterDetail::OnClickSelectShieldButton()
{
	SetSwitcherValue(0);
}

void UCharacterDetail::OnClickSelectWindButton()
{
	SetSwitcherValue(1);
}

void UCharacterDetail::OnClickSelectElectricButton()
{
	SetSwitcherValue(2);
}

void UCharacterDetail::OnClickSelectThrowButton()
{
	SetSwitcherValue(3);
}

void UCharacterDetail::OnClickSelectAssassinButton()
{
	SetSwitcherValue(4);
}

void UCharacterDetail::OnClickSelectDetectionButton()
{
	SetSwitcherValue(5);
}
