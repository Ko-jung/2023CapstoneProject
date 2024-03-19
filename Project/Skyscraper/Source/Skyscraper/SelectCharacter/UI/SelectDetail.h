// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Input/Reply.h"
#include "SelectDetail.generated.h"

class UImage;
class UButton;
class UWidgetSwitcher;

UCLASS()
class SKYSCRAPER_API USelectDetail : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	// 선택지 버튼 변수
	UPROPERTY(meta = (BindWidget))
		UButton* CharacterDetailButton;
	UPROPERTY(meta = (BindWidget))
		UButton* MeleeDetailButton;
	UPROPERTY(meta = (BindWidget))
		UButton* RangeDetailButton;
	UPROPERTY(meta = (BindWidget))
		UButton* GoToLastButton;
	UPROPERTY()
		TArray<UButton*> Buttons;

	// 선택지 위젯 스위쳐 변수
	UPROPERTY(meta = (BindWidget))
		UWidgetSwitcher* DetailSwitcher;

	void SetSwitcherValue(int32 Value) const;
public:
	/* Getter */
	FORCEINLINE UButton* GetCharacterDetailButton() const { return CharacterDetailButton; }
	FORCEINLINE UButton* GetMeleeDetailButton() const { return MeleeDetailButton; }
	FORCEINLINE UButton* GetRangeDetailButton() const { return RangeDetailButton; }
	FORCEINLINE UButton* GetGoToLastButton() const { return GoToLastButton; }

	FORCEINLINE UWidgetSwitcher* GetDetailSwitcher() const { return DetailSwitcher; }

	UFUNCTION()
		void OnClickCharacterDetailButton();
	UFUNCTION()
		void OnClickMeleeDetailButton();
	UFUNCTION()
		void OnClickRangeDetailButton();
	UFUNCTION()
		void OnClickGoToLastButton();

	
	
};
