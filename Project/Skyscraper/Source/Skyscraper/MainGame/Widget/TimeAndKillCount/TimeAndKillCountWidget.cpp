// Fill out your copyright notice in the Description page of Project Settings.

#include "TimeAndKillCountWidget.h"
#include "Components/TextBlock.h"

#define LOCTEXT_NAMESPACE "UMG"

void UTimeAndKillCountWidget::SetFriendlyKillCountText(int FriendlyKillCount)
{
	FriendlyTeamKillCountText->SetText(FText::FromString(FString::FromInt(FriendlyKillCount)));
}

void UTimeAndKillCountWidget::SetEnemyKillCountText(int EnemyKillCount)
{
	EnemyTeamKillCountText->SetText(FText::FromString(FString::FromInt(EnemyKillCount)));
}


void UTimeAndKillCountWidget::SetTimeText(int GetMinute, int GetSecond)
{
	FString MinuteString = "";
	if (GetMinute < 10) MinuteString = "0";
	MinuteString += FString::FromInt(GetMinute);

	FString SecondString = "";
	if (GetSecond < 10) SecondString = "0";
	SecondString += FString::FromInt(GetSecond);

	FText Text = FText::FromString(MinuteString + " : " + SecondString);
	TimeText->SetText(Text);

	//TimeText->SetText(FText::Format(LOCTEXT("TimeText", "{0} : {1}"), FText::FromString(MinuteString), SecondString));
}

void UTimeAndKillCountWidget::SetCollapseLevelText(int CollapseLevel)
{
	CollapseLevelText->SetText(FText::Format(LOCTEXT("CollapseLevelText", "타일 낙하 {0}단계"), CollapseLevel));
}


#undef LOCTEXT_NAMESPACE