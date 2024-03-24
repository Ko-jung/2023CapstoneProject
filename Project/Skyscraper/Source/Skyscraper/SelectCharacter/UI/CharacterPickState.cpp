#include "CharacterPickState.h"

#include "Components/Button.h"
#include "../Core/SelectCharacterController.h"
#include "Kismet/GameplayStatics.h"
#include "Skyscraper/SkyscraperGameMode.h"

// Fill out your copyright notice in the Description page of Project Settings.

void UCharacterPickState::NativeConstruct()
{
	MyCharacterButton->OnClicked.AddUniqueDynamic(this, &ThisClass::GoToDetail);
	MyMeleeButton->OnClicked.AddUniqueDynamic(this, &ThisClass::GoToDetail);
	MyRangeButton->OnClicked.AddUniqueDynamic(this, &ThisClass::GoToDetail);

	auto gamemode = UGameplayStatics::GetGameMode(this);
	Gamemode = static_cast<ASkyscraperGameMode*>(gamemode);

	IsInfoChanged = false;
}

void UCharacterPickState::NativeDestruct()
{
	Super::NativeDestruct();
}

void UCharacterPickState::Tick(FGeometry MyGeometry, float InDeltaTime)
{
	Super::Tick(MyGeometry, InDeltaTime);

	if (IsInfoChanged)
	{
		SelectInfoUpdate();
		IsInfoChanged = false;
	}

}

void UCharacterPickState::SelectInfoUpdate()
{
	UE_LOG(LogClass, Warning, TEXT("@@@@@@@@@@@@@@@@@@@@@@@"));
	//auto InfoArray = Gamemode->
	//for (int i = 0; i < MAXPLAYER; i++)
	//{

	//}
}

void UCharacterPickState::GoToDetail()
{
	if(ASelectCharacterController* Controller = Cast<ASelectCharacterController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))  )
	{
		Controller->SetDetailWidgetVisibility(true);
	}
}
