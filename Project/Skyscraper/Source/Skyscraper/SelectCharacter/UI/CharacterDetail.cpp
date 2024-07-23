// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterDetail.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"

#include "Skyscraper/SkyscraperGameMode.h"
#include "Skyscraper/Enum/ECharacterSelect.h"

void UCharacterDetail::NativeConstruct()
{
	Super::NativeConstruct();
	SelectShieldButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClickSelectShieldButton);
	SelectWindButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClickSelectWindButton);
	SelectElectricButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClickSelectElectricButton);
	SelectThrowButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClickSelectThrowButton);
	SelectAssassinButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClickSelectAssassinButton);
	SelectDetectionButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClickSelectDetectionButton);

	if (CharacterButtons.IsEmpty())
	{
		CharacterButtons.Add(ECharacterSelect::ECS_ShieldCharacter, SelectShieldButton);
		CharacterButtons.Add(ECharacterSelect::ECS_WindCharacter, SelectWindButton);
		CharacterButtons.Add(ECharacterSelect::ECS_ElectricCharacter, SelectElectricButton);
		CharacterButtons.Add(ECharacterSelect::ECS_BoomerangCharacter, SelectThrowButton);
		CharacterButtons.Add(ECharacterSelect::ECS_AssassinCharacter, SelectAssassinButton);
		CharacterButtons.Add(ECharacterSelect::ECS_DetectionCharacter, SelectDetectionButton);
	}

	auto gamemode = UGameplayStatics::GetGameMode(this);
	Gamemode = static_cast<ASkyscraperGameMode*>(gamemode);
	PlayerSerialNum = Gamemode->GetSerialNum();
}

void UCharacterDetail::NativeDestruct()
{
	Super::NativeDestruct();
}

void UCharacterDetail::Tick(FGeometry MyGeometry, float InDeltaTime)
{
	Super::Tick(MyGeometry, InDeltaTime);

	UpdateCharacterButton();
}

void UCharacterDetail::UpdateCharacterButton()
{
	TArray<PPlayerSelectInfo*>& PlayerSelectInfos = Gamemode->GetPlayerSelectInfo();

	bool IsRight = PlayerSerialNum >= MAXPLAYER / 2;
	for (const auto& button : CharacterButtons)	button.Value->SetIsEnabled(true);

	for (int i = 0; i < MAXPLAYER / 2; i++)
	{
		int index = i + IsRight * MAXPLAYER / 2;
		if (CharacterButtons.Find((ECharacterSelect)PlayerSelectInfos[i]->PickedCharacter))
		{
			CharacterButtons[(ECharacterSelect)PlayerSelectInfos[i]->PickedCharacter]->SetIsEnabled(false);
		}
	}
}



void UCharacterDetail::OnClickSelectShieldButton()
{
	Gamemode->UpdateSelectInfo(ECharacterSelect::ECS_ShieldCharacter);
}

void UCharacterDetail::OnClickSelectWindButton()
{
	Gamemode->UpdateSelectInfo(ECharacterSelect::ECS_WindCharacter);
}

void UCharacterDetail::OnClickSelectElectricButton()
{
	Gamemode->UpdateSelectInfo(ECharacterSelect::ECS_ElectricCharacter);
}

void UCharacterDetail::OnClickSelectThrowButton()
{
	Gamemode->UpdateSelectInfo(ECharacterSelect::ECS_BoomerangCharacter);
}

void UCharacterDetail::OnClickSelectAssassinButton()
{
	Gamemode->UpdateSelectInfo(ECharacterSelect::ECS_AssassinCharacter);
}

void UCharacterDetail::OnClickSelectDetectionButton()
{
	Gamemode->UpdateSelectInfo(ECharacterSelect::ECS_DetectionCharacter);
}
