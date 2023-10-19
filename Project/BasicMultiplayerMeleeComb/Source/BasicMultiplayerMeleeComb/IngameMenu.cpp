// Fill out your copyright notice in the Description page of Project Settings.

#include "IngameMenu.h"

#include "Components/Button.h"
#include "Engine/GameInstance.h"

bool UIngameMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	ResumeButton->OnClicked.AddDynamic(this, &UIngameMenu::Resume);
	QuitButton->OnClicked.AddDynamic(this, &UIngameMenu::Quit);
	ExitButton->OnClicked.AddDynamic(this, &UIngameMenu::Exit);

	return true;
}

void UIngameMenu::Resume()
{
}

void UIngameMenu::Quit()
{
}

void UIngameMenu::Exit()
{
}
