// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleMenu.h"
#include "Blueprint/Userwidget.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Engine/GameInstance.h"
#include "Components/EditableText.h"

bool UTitleMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!HostButton) return false;

	HostButton->OnClicked.AddDynamic(this, &UTitleMenu::HostServer);
	JoinButton->OnClicked.AddDynamic(this, &UTitleMenu::JoinServer);
	QuitButton->OnClicked.AddDynamic(this, &UTitleMenu::Quit);

	CancelButton->OnClicked.AddDynamic(this, &UTitleMenu::Cencel);
	EnterButton->OnClicked.AddDynamic(this, &UTitleMenu::EnterServer);

	return true;
}

void UTitleMenu::HostServer()
{
	UE_LOG(LogTemp, Warning, TEXT("Called Host Server"));

	UWorld* World = GetWorld();
	if (!World) return;

	// Host
	World->ServerTravel("/Game/2019180016/SingleTestMap?listen?Port=7777");
}

void UTitleMenu::JoinServer()
{
	Switcher->SetActiveWidgetIndex(1);
}

void UTitleMenu::Quit()
{
	UE_LOG(LogTemp, Warning, TEXT("Called Quit"));
	//FGenericPlatformMisc::RequestExit(false);
	

	UWorld* World = GetWorld();
	APlayerController* Controller = World->GetFirstPlayerController();

	Controller->ConsoleCommand("quit");
}

void UTitleMenu::EnterServer()
{
	UE_LOG(LogTemp, Warning, TEXT("Called Enter Server"));

	UWorld* World = GetWorld();
	APlayerController* Controller = World->GetFirstPlayerController();

	FText Address = AddressInput->GetText();

	Controller->ClientTravel(Address.ToString() + ":7777", ETravelType::TRAVEL_Absolute);
}

void UTitleMenu::Cencel()
{
	Switcher->SetActiveWidgetIndex(0);
}
