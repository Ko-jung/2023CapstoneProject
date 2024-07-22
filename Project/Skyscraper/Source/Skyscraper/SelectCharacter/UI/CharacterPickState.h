// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "../../Enum/ECharacterSelect.h"
#include "../../Enum/EMeleeSelect.h"
#include "../../Enum/ERangeSelect.h"

#include "CharacterPickState.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class SKYSCRAPER_API UCharacterPickState : public UUserWidget
{
	GENERATED_BODY()
public: 
	UCharacterPickState(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION(BlueprintCallable)
	void SelectInfoUpdate();

	UFUNCTION()
	void SetPlayerIDs(TArray<FString> IDs, int SerialNum);

	UFUNCTION()
	void SetOwnButtonOnClicked();

public:
	FORCEINLINE UButton* GetMyCharacterBorder() const	; //{ return CharacterButton0; }
	FORCEINLINE UButton* GetMyMeleeBorder() const		; //{ return MeleeButton0; }
	FORCEINLINE UButton* GetMyRangeBorder() const		; //{ return RangeButton0; }

	UFUNCTION()
	void GoToDetail();

	UPROPERTY(EditAnywhere, Category="SelectedImage")
	TMap<ECharacterSelect, UTexture2D*> CharacterImages;
	UPROPERTY(EditAnywhere, Category = "SelectedImage")
	TMap<EMeleeSelect, UTexture2D*> MeleeImages;
	UPROPERTY(EditAnywhere, Category = "SelectedImage")
	TMap<ERangeSelect, UTexture2D*> RangeImages;
	UPROPERTY(EditAnywhere, Category = "SelectedImage")
	UTexture2D* QuestionImages;

	TArray<UImage*> CharacterImgs;
	TArray<UImage*> MeleeImgs;
	TArray<UImage*> RangeImgs;

	TArray<UButton*> CharacterButtons;
	TArray<UButton*> MeleeButtons;
	TArray<UButton*> RangeButtons;

	TArray<UTextBlock*> PlayerIDs;

private:
	class ASkyscraperGameMode* Gamemode;
	bool IsBinding;

	uint8 PlayerSerialNum;

	// Widget Bind Variables
	UPROPERTY(meta = (BindWidget))	UImage* CharacterImg;
	UPROPERTY(meta = (BindWidget))	UImage* CharacterImg_1;
	UPROPERTY(meta = (BindWidget))	UImage* CharacterImg_2;
	UPROPERTY(meta = (BindWidget))	UImage* CharacterImg_3;
	UPROPERTY(meta = (BindWidget))	UImage* CharacterImg_4;
	UPROPERTY(meta = (BindWidget))	UImage* CharacterImg_5;

	UPROPERTY(meta = (BindWidget))	UImage* MeleeImg;
	UPROPERTY(meta = (BindWidget))	UImage* MeleeImg_1;
	UPROPERTY(meta = (BindWidget))	UImage* MeleeImg_2;
	UPROPERTY(meta = (BindWidget))	UImage* MeleeImg_3;
	UPROPERTY(meta = (BindWidget))	UImage* MeleeImg_4;
	UPROPERTY(meta = (BindWidget))	UImage* MeleeImg_5;

	UPROPERTY(meta = (BindWidget))	UImage* RangeImg;
	UPROPERTY(meta = (BindWidget))	UImage* RangeImg_1;
	UPROPERTY(meta = (BindWidget))	UImage* RangeImg_2;
	UPROPERTY(meta = (BindWidget))	UImage* RangeImg_3;
	UPROPERTY(meta = (BindWidget))	UImage* RangeImg_4;
	UPROPERTY(meta = (BindWidget))	UImage* RangeImg_5;

	UPROPERTY(meta = (BindWidget))	UTextBlock* PlayerId;
	UPROPERTY(meta = (BindWidget))	UTextBlock* PlayerId_1;
	UPROPERTY(meta = (BindWidget))	UTextBlock* PlayerId_2;
	UPROPERTY(meta = (BindWidget))	UTextBlock* PlayerId_3;
	UPROPERTY(meta = (BindWidget))	UTextBlock* PlayerId_4;
	UPROPERTY(meta = (BindWidget))	UTextBlock* PlayerId_5;

private:
	// == Border variable
	UPROPERTY(meta = (BindWidget))	UButton* CharacterButton;
	UPROPERTY(meta = (BindWidget))	UButton* CharacterButton_1;
	UPROPERTY(meta = (BindWidget))	UButton* CharacterButton_2;
	UPROPERTY(meta = (BindWidget))	UButton* CharacterButton_3;
	UPROPERTY(meta = (BindWidget))	UButton* CharacterButton_4;
	UPROPERTY(meta = (BindWidget))	UButton* CharacterButton_5;

	UPROPERTY(meta = (BindWidget))	UButton* MeleeButton;
	UPROPERTY(meta = (BindWidget))	UButton* MeleeButton_1;
	UPROPERTY(meta = (BindWidget))	UButton* MeleeButton_2;
	UPROPERTY(meta = (BindWidget))	UButton* MeleeButton_3;
	UPROPERTY(meta = (BindWidget))	UButton* MeleeButton_4;
	UPROPERTY(meta = (BindWidget))	UButton* MeleeButton_5;

	UPROPERTY(meta = (BindWidget))	UButton* RangeButton;
	UPROPERTY(meta = (BindWidget))	UButton* RangeButton_1;
	UPROPERTY(meta = (BindWidget))	UButton* RangeButton_2;
	UPROPERTY(meta = (BindWidget))	UButton* RangeButton_3;
	UPROPERTY(meta = (BindWidget))	UButton* RangeButton_4;
	UPROPERTY(meta = (BindWidget))	UButton* RangeButton_5;
};
