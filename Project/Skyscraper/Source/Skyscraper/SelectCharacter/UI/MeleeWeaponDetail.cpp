// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeWeaponDetail.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Widgets/Input/SButton.h"

#include "Kismet/GameplayStatics.h"
#include "Skyscraper/SkyscraperGameMode.h"

void UMeleeWeaponDetail::NativeConstruct()
{
	Super::NativeConstruct();
	DaggerSelectButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClickDaggerButton);
	KatanaSelectButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClickKatanaButton);
	GreatSwordButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClickGreatSwordButton);

	MeleeSwitcher->SetVisibility(ESlateVisibility::Hidden);

	auto gamemode = UGameplayStatics::GetGameMode(this);
	Gamemode = static_cast<ASkyscraperGameMode*>(gamemode);
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

	Gamemode->UpdateSelectInfo(EMeleeWeapon::Dagger);
}

void UMeleeWeaponDetail::OnClickKatanaButton() 
{
	SetSwitcherValue(1);

	Gamemode->UpdateSelectInfo(EMeleeWeapon::Katana);
}

void UMeleeWeaponDetail::OnClickGreatSwordButton() 
{
	SetSwitcherValue(2);

	Gamemode->UpdateSelectInfo(EMeleeWeapon::Greatsword);
}

