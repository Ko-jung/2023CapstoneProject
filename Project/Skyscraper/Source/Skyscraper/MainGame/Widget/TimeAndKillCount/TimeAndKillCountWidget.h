// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimeAndKillCountWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class SKYSCRAPER_API UTimeAndKillCountWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SetFriendlyKillCountText(int FriendlyKillCount);
	UFUNCTION()
	void SetEnemyKillCountText(int EnemyKillCount);

	UFUNCTION(BlueprintCallable)
	void SetTimeText(int GetMinute, int GetSecond);

	UFUNCTION()
	void SetCollapseLevelText(int CollapseLevel);


private:
	UPROPERTY(meta = (BindWidget))
		TObjectPtr<UTextBlock> FriendlyTeamKillCountText;
	UPROPERTY(meta = (BindWidget))
		TObjectPtr<UTextBlock> EnemyTeamKillCountText;
	UPROPERTY(meta = (BindWidget))
		TObjectPtr<UTextBlock> TimeText;
	UPROPERTY(meta = (BindWidget))
		TObjectPtr<UTextBlock> CollapseLevelText;
};
