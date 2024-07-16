// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Skyscraper/Enum/ECharacterSelect.h"
#include "MainCombatWidget.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class SKYSCRAPER_API UMainCombatWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
		void SetCharacterImage(ECharacterSelect CharacterType);
protected:
	virtual void NativePreConstruct() override;
private:
public:
protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		TObjectPtr<UImage> CharacterImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterTexture")
		TArray<TObjectPtr<UTexture2D>> CharacterTextures;
private:
};
