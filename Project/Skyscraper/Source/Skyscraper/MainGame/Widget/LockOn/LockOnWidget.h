// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LockOnWidget.generated.h"

class UCanvasPanelSlot;
class UImage;
/**
 * 
 */
UCLASS()
class SKYSCRAPER_API ULockOnWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetTargetLockImageAlignment(FVector2D ViewportSize, FVector2D TargetScreenLocation);

	void SetTargetLockImageVisibie(bool bNewVisible);
protected:
	void NativeConstruct() override;
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
private:
public:
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		TObjectPtr<UImage> TargetLockImage;

	UPROPERTY()
		TObjectPtr<UCanvasPanelSlot> CanvasSlot;

	UPROPERTY()
		TObjectPtr<UCanvasPanelSlot> TargetLockImageSlot;
private:
};
