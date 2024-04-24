// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterDetail.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"

#include "Skyscraper/SkyscraperGameMode.h"

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

	auto gamemode = UGameplayStatics::GetGameMode(this);
	Gamemode = static_cast<ASkyscraperGameMode*>(gamemode);
}

void UCharacterDetail::NativeDestruct()
{
	Super::NativeDestruct();
}

void UCharacterDetail::Tick(FGeometry MyGeometry, float InDeltaTime)
{
	Super::Tick(MyGeometry, InDeltaTime);
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

	Gamemode->UpdateSelectInfo(ECharacterSelect::ECS_ShieldCharacter);
}

void UCharacterDetail::OnClickSelectWindButton()
{
	SetSwitcherValue(1);

	Gamemode->UpdateSelectInfo(ECharacterSelect::ECS_WindCharacter);
}

void UCharacterDetail::OnClickSelectElectricButton()
{
	SetSwitcherValue(2);

	Gamemode->UpdateSelectInfo(ECharacterSelect::ECS_ElectricCharacter);
}

void UCharacterDetail::OnClickSelectThrowButton()
{
	SetSwitcherValue(3);

	Gamemode->UpdateSelectInfo(ECharacterSelect::ECS_BoomerangCharacter);
}

void UCharacterDetail::OnClickSelectAssassinButton()
{
	SetSwitcherValue(4);

	Gamemode->UpdateSelectInfo(ECharacterSelect::ECS_AssassinCharacter);
}

void UCharacterDetail::OnClickSelectDetectionButton()
{
	SetSwitcherValue(5);

	Gamemode->UpdateSelectInfo(ECharacterSelect::ECS_DetectionCharacter);
}
