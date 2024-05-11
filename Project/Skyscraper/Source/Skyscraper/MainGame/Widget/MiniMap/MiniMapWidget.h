// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Skyscraper/Enum/ETileImageType.h"
#include "MiniMapWidget.generated.h"

class UCanvasPanelSlot;
class UCanvasPanel;
class UImage;
/**
 * 
 */
UCLASS()
class SKYSCRAPER_API UMiniMapWidget : public UUserWidget
{
	GENERATED_BODY()

	
public:
	UFUNCTION(BlueprintCallable)
		void SetTileImageAlignment(int index, FVector2D NewAlignment);

	UFUNCTION(BlueprintCallable)
		void SetTileImage(int index, ETileImageType TileImageType);

	UFUNCTION()
		void CollapseTileImage(int index);

protected:
	virtual void NativePreConstruct() override;
	
private:

public:

protected:
	UPROPERTY()
		UCanvasPanel* TileImageCanvas;

	UPROPERTY()
		TArray<UImage*> TileImages;

	UPROPERTY()
		TArray<UTexture2D*> TileTextures;
private:

};
