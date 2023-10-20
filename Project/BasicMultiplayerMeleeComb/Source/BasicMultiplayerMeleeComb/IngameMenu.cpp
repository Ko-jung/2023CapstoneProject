// Fill out your copyright notice in the Description page of Project Settings.

#include "IngameMenu.h"

#include "Components/Button.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameUserSettings.h"

bool UIngameMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	QuitButton->OnClicked.AddDynamic(this, &UIngameMenu::Quit);
	ExitButton->OnClicked.AddDynamic(this, &UIngameMenu::Exit);

	WindowButton->OnClicked.AddDynamic(this, &UIngameMenu::Window);

	return true;
}

//void UIngameMenu::Resume()
//{
//	UWorld* World					= GetWorld();
//	APlayerController* Controller	= World->GetFirstPlayerController();
//	APawn* Pawn						= Controller->GetPawn();
//
//	ACharacter* Character = Cast<ACharacter>(Pawn);
//
//
//}

void UIngameMenu::Quit()
{
	EWindowMode::Fullscreen;

	UGameplayStatics::OpenLevel(this, TEXT("Title"));
	UE_LOG(LogTemp, Warning, TEXT("Open Level: Title"));
}

void UIngameMenu::Exit()
{
	UWorld* World = GetWorld();
	APlayerController* Controller = World->GetFirstPlayerController();

	UE_LOG(LogTemp, Warning, TEXT("Quit Game"));
	Controller->ConsoleCommand("quit");
}

void UIngameMenu::Window()
{
	auto GameSetting = UGameUserSettings::GetGameUserSettings();

	if (GameSetting->GetFullscreenMode() == EWindowMode::Fullscreen)
	{
		GameSetting->SetFullscreenMode(EWindowMode::Windowed);
		GameSetting->SetScreenResolution(FIntPoint(1280, 720));
	}
	else
	{
		GameSetting->SetFullscreenMode(EWindowMode::Fullscreen);
		GameSetting->SetScreenResolution(FIntPoint(1920, 1080));
	}
	GameSetting->ApplyResolutionSettings(false);
	GameSetting->ApplySettings(true);
}
