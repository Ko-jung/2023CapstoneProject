// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "Skyscraper/Network/LobbyMode.h"

void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

bool ULobbyWidget::Initialize()
{
	bool Succ = Super::Initialize();
	if (!Succ) return false;

	IsMatching = false;
	MatchingBtn->OnClicked.AddDynamic(this, &ULobbyWidget::OnMatchingButtonClick);
	MatchingTimer->SetVisibility(ESlateVisibility::Hidden);

	LobbyGameMode = Cast<ALobbyMode>(GetWorld()->GetAuthGameMode());

	// Now Gamemode Is ALobbyMode?
	return (bool)LobbyGameMode;
}

void ULobbyWidget::OnMatchingButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("ULobbyWidget::OnMatchingButtonClick()"));

	LobbyGameMode->Ready(IsMatching);
	if (IsMatching)
	{
		MatchingTimer->SetVisibility(ESlateVisibility::Hidden);
		FString String = TEXT("매칭 시작");
		MatchingText->SetText(FText::FromString(String));
		IsMatching = false;
	}
	else
	{
		MatchingStartTime = FDateTime::Now();
		MatchingTimer->SetVisibility(ESlateVisibility::HitTestInvisible);
		FString String = TEXT("매칭 종료");
		MatchingText->SetText(FText::FromString(String));
		IsMatching = true;
	}
}

void ULobbyWidget::UpdateMatchingTimer()
{
	FDateTime NowTime = FDateTime::Now();
	FTimespan MatchingDelta = NowTime - MatchingStartTime;

	int DeltaSec = (int)MatchingDelta.GetTotalSeconds();

	int Minute = DeltaSec / 60;
	int Second = DeltaSec % 60;

	TCHAR Buffer[256];
	FCString::Sprintf(Buffer, TEXT("%02d : %02d"), Minute, Second);
	FString TimerString = FString(Buffer);
	UE_LOG(LogClass, Warning, TEXT("ULobbyWidget::UpdateMatchingTimer() %s"), *TimerString);

	MatchingTimer->SetText(FText::FromString(TimerString));
}
