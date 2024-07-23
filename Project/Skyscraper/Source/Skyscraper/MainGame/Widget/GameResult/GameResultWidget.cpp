// Fill out your copyright notice in the Description page of Project Settings.


#include "GameResultWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Skyscraper/MainGame/Core/SkyscraperPlayerController.h"

#include "Skyscraper/Network/MainGameMode.h"

void UGameResultWidget::SetWinnerText(const bool IsWin) const
{
	if(WinnerText)
	{
		//WinnerText->SetText(FText(NewText));
		if (IsWin)
		{
			WinnerText->SetText(FText::FromString(TEXT("승리")));
			WinnerText->SetColorAndOpacity(FSlateColor(FLinearColor::Blue));
		}
		else
		{
			WinnerText->SetText(FText::FromString(TEXT("패배")));
			WinnerText->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
		}
	}
}

void UGameResultWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ToLobbyButton->OnClicked.AddUniqueDynamic(this, &ThisClass::GoToLobby);


	OwnerPlayerController = Cast<ASkyscraperPlayerController>(GetOwningPlayer());
	OwnerPlayerController->SetShowMouseCursor(true);
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(OwnerPlayerController);
}

void UGameResultWidget::GoToLobby()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("LobbyLevel"));
	//auto gamemode = UGameplayStatics::GetGameMode(this);
	//Cast<AMainGameMode>(gamemode)->GoToLobby();
}


void UGameResultWidget::NativeDestruct()
{
	Super::NativeDestruct();

	OwnerPlayerController->SetShowMouseCursor(false);
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(OwnerPlayerController);
}
