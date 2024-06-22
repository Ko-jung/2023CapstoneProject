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

	UFUNCTION()
		UImage* GetPlayerImage()const { return PlayerImage; }

	// 플레이어 캐릭터의 위치를 갱신시키는 함수
	UFUNCTION(BlueprintCallable)
		void SetPlayerImageAlignment(FVector2D NewAlignment, float NewAngle);

	// 플레이어 외 아군 캐릭터나 적군 캐릭터 위치를 갱신시키는 함수
	UFUNCTION(BlueprintCallable)
		void SetOtherPlayerImageAlignment(UImage* TargetPlayerImage, FVector2D NewAlignment);
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

	UPROPERTY()
		UImage* PlayerImage;

	UPROPERTY()
		TArray<UImage*> FriendlyPlayerImages;
	UPROPERTY()
		TArray<UImage*> EnemyPlayerImages;
private:

};
