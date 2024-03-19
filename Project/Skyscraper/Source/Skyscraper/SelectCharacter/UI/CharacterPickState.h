// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterPickState.generated.h"

class UButton;
UCLASS()
class SKYSCRAPER_API UCharacterPickState : public UUserWidget
{
	GENERATED_BODY()
public: 
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	// 선택 Border 변수
	UPROPERTY(meta = (BindWidget))
		UButton* MyCharacterButton;
	UPROPERTY(meta = (BindWidget))
		UButton* MyMeleeButton;
	UPROPERTY(meta = (BindWidget))
		UButton* MyRangeButton;

public:
	FORCEINLINE UButton* GetMyCharacterBorder() const { return MyCharacterButton; }
	FORCEINLINE UButton* GetMyMeleeBorder() const { return MyMeleeButton; }
	FORCEINLINE UButton* GetMyRangeBorder() const { return MyRangeButton; }

	UFUNCTION()
	void GoToDetail();
};
