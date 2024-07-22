// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Skyscraper/Enum/ECharacterSelect.h"
#include "TileBreakItemWidget.generated.h"

class UButton;
class ASkyscraperCharacter;
class UImage;


UCLASS()
class SKYSCRAPER_API UTileBreakItemWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable)
		void SetEnemyPlayer(int PlayerIndex, ASkyscraperCharacter* TargetCharacter);

	// 2019180016
	void SetUseCharacter(ASkyscraperCharacter* Character) { UseCharacter = Character; };
	// ==========

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
		void FirstButtonClicked();
	UFUNCTION()
		void SecondButtonClicked();
	UFUNCTION()
		void ThirdButtonClicked();

	void CollapseTileWithEnemy(int PlayerIndex);

	UFUNCTION()
		void CancelUsingItem();

	UFUNCTION()
		void SetPlayerImage(int PlayerIndex, ECharacterSelect CharacterType);
private:

public:

protected:
	UPROPERTY()
		TArray<TObjectPtr<UImage>> PlayerImages;
	UPROPERTY()
		TArray<TObjectPtr<ASkyscraperCharacter>> TargetCharacters;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		TObjectPtr<UImage> FirstPlayerImage;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		TObjectPtr<UImage> SecondPlayerImage;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		TObjectPtr<UImage> ThirdPlayerImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		TObjectPtr<UButton> FirstPlayerButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		TObjectPtr<UButton> SecondPlayerButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		TObjectPtr<UButton> ThirdPlayerButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		TObjectPtr<UButton> CancelButton;

private:
	// 2019180016
	ASkyscraperCharacter* UseCharacter;
	// ==========
};
