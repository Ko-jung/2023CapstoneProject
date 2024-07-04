// Fill out your copyright notice in the Description page of Project Settings.


#include "LockOnWidget.h"

#include "Blueprint/SlateBlueprintLibrary.h"
#include "Engine/Canvas.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"

void ULockOnWidget::SetTargetLockImageAlignment(FVector2D ViewportSize, FVector2D TargetScreenLocation)
{
	if(TargetLockImageSlot)
	{
		TargetLockImageSlot->SetPosition(TargetScreenLocation/ViewportSize*GetCachedGeometry().GetLocalSize());
	}
}

void ULockOnWidget::SetTargetLockImageVisibie(bool bNewVisible)
{
	if(bNewVisible)
	{
		TargetLockImage->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		TargetLockImage->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ULockOnWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	CanvasSlot = Cast<UCanvasPanelSlot>(GetWidgetFromName(TEXT("Wrap"))->Slot);
	TargetLockImageSlot = Cast<UCanvasPanelSlot>(TargetLockImage->Slot);
}

void ULockOnWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	TargetLockImage->SetRenderTransformAngle(TargetLockImage->GetRenderTransformAngle() + InDeltaTime * 100.0f);
}
