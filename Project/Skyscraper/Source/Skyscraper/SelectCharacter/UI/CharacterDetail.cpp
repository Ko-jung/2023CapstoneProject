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



void UCharacterDetail::OnClickSelectShieldButton()
{
	Gamemode->UpdateSelectInfo(ECharacterSelect::ECS_ShieldCharacter);
	UE_LOG(LogTemp, Warning, TEXT("ABC"));
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
