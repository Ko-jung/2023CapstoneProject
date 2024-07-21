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
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION(BlueprintCallable)
	void SelectInfoUpdate();

	UFUNCTION()
	void SetPlayerIDs(TArray<FString> IDs, int SerialNum);

private:
	// == Border variable
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

	UPROPERTY(EditAnywhere, Category="SelectedImage")
	TMap<ECharacterSelect, UTexture2D*> CharacterImages;
	UPROPERTY(EditAnywhere, Category = "SelectedImage")
	TMap<EMeleeSelect, UTexture2D*> MeleeImages;
	UPROPERTY(EditAnywhere, Category = "SelectedImage")
	TMap<ERangeSelect, UTexture2D*> RangeImages;
	UPROPERTY(EditAnywhere, Category = "SelectedImage")
	UTexture2D* QuestionImages;

	UPROPERTY(meta = (BindWidget))
	UImage* FriendlyCharacter0;
	UPROPERTY(meta = (BindWidget))
	UImage* FriendlyMelee0;
	UPROPERTY(meta = (BindWidget))
	UImage* FriendlyRange0;
	UPROPERTY(meta = (BindWidget))
	UImage* FriendlyCharacter1;
	UPROPERTY(meta = (BindWidget))
	UImage* FriendlyMelee1;
	UPROPERTY(meta = (BindWidget))
	UImage* FriendlyRange1;
	UPROPERTY(meta = (BindWidget))
	UImage* FriendlyCharacter2;
	UPROPERTY(meta = (BindWidget))
	UImage* FriendlyMelee2;
	UPROPERTY(meta = (BindWidget))
	UImage* FriendlyRange2;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerId0;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerId1;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerId2;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerId3;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerId4;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerId5;

	TArray<UImage*> FriendlyChracters;
	TArray<UImage*> FriendlyMelee;
	TArray<UImage*> FriendlyRange;

	TArray<UTextBlock*> PlayerIDs;

private:
	class ASkyscraperGameMode* Gamemode;
	bool IsInfoChanged;
};
