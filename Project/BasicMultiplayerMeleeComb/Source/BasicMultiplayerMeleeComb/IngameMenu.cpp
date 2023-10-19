// Fill out your copyright notice in the Description page of Project Settings.

#include "IngameMenu.h"

#include "Components/Button.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"

bool UIngameMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	//ResumeButton->OnClicked.AddDynamic(this, &UIngameMenu::Resume);
	QuitButton->OnClicked.AddDynamic(this, &UIngameMenu::Quit);
	ExitButton->OnClicked.AddDynamic(this, &UIngameMenu::Exit);

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
