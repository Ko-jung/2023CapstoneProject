// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Skyscraper/Enum/ETileImageType.h"
#include "MiniMapWidget.generated.h"

class AHexagonTile;
class UCanvasPanelSlot;
class UCanvasPanel;
class UImage;

USTRUCT()
struct FImageAndActor
{
	GENERATED_BODY()
public:
	FImageAndActor(){}
	FImageAndActor(UImage* TargetImage, AActor* TargetActor)
	{
		ImageWidget = TargetImage;
		Actor = TargetActor;
	}

	UPROPERTY()
	TObjectPtr<UImage> ImageWidget;
	UPROPERTY()
	TObjectPtr<AActor> Actor;

	bool IsValid() const
	{
		if(ImageWidget && Actor)
		{
			return true;
		}
		return false;
	}
};



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
		UImage* GetPlayerImage() const { return PlayerImageAndActor.ImageWidget; }

	// 플레이어 캐릭터의 위치를 갱신시키는 함수
	UFUNCTION(BlueprintCallable)
		void SetPlayerImageAlignment(FVector2D NewAlignment, float NewAngle);

	// 플레이어 외 아군 캐릭터나 적군 캐릭터 위치를 갱신시키는 함수
	UFUNCTION(BlueprintCallable)
		void SetOtherPlayerImageAlignment(UImage* TargetPlayerImage, FVector2D NewAlignment);

	// 아군/적군 플레이어를 이미지에 연결하는 함수
	// 이미지가 모두 사용 중일 경우 실행하지 않음
	UFUNCTION()
		void AddPlayerToImage(AActor* Player);
	UFUNCTION(BlueprintCallable)
		void AddFriendlyPlayerToImage(AActor* FriendlyPlayer);
	UFUNCTION(BlueprintCallable)
		void AddEnemyPlayerToImage(AActor* EnemyPlayer);
	
protected:
	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
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
	FImageAndActor PlayerImageAndActor;

	UPROPERTY()
		TArray<FImageAndActor> FriendlyPlayerImagesAndActors;
	UPROPERTY()
		TArray<FImageAndActor> EnemyPlayerImagesAndActors;

	UPROPERTY()
		AHexagonTile* HexagonTile;

private:

};

