// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Skyscraper/Enum/EItemEffect.h"
#include "ItemWidget.generated.h"

class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class SKYSCRAPER_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetItemImageTexture(EItemEffect ItemEffect);
protected:
	virtual void NativePreConstruct() override;
	FString GetItemTextByEItemEffect(EItemEffect ItemEffect);
private:

public:
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		TObjectPtr<UImage> ItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemTexture")
		TArray<TObjectPtr<UTexture2D>> ItemTexture;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		TObjectPtr<UTextBlock> ItemText;
	
private:
};
