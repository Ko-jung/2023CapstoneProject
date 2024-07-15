// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageWidget.generated.h"

class UCanvasPanel;
class UImage;
/**
 * 
 */
UCLASS()
class SKYSCRAPER_API UDamageWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		void CreateDamageImage(int Damage, int LengthOfDamage);
	
protected:
private:
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		TArray<TObjectPtr<UTexture2D>> DamageTextures;
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		TObjectPtr<UCanvasPanel> MainCanvas;

	UPROPERTY()
		TArray<TObjectPtr<UImage>> DamageImages;

	
private:
};
