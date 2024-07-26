// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeWidget.h"

#include "Components/CanvasPanelSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UMeleeWidget::SetMeleeCooldownPercent(float CurrentCooldownTime, float MaxCooldownTime) const
{
	if(MaxCooldownTime >= FLT_EPSILON && PB_MeleeCooldown)
	{
		PB_MeleeCooldown->SetPercent(CurrentCooldownTime / MaxCooldownTime);
	}
}

void UMeleeWidget::SetMeleeWeapon(EMeleeSelect MeleeSelect)
{
	if(WeaponTexture.IsValidIndex(static_cast<int>(MeleeSelect)))
	{
		MeleeWeaponImage->SetBrushFromTexture(WeaponTexture[static_cast<int>(MeleeSelect)]);
	}
}

void UMeleeWidget::InitHitCountFunc()
{
	CurrentInitHitCountTime += TimeOffset;

	// Curve값 alpha에 반영
	{
		if(HitTextBox && HitTextAlphaCurve)
		{
			HitTextBox->SetRenderOpacity(HitTextAlphaCurve->GetFloatValue(CurrentInitHitCountTime));
		}
	}

	if(CurrentInitHitCountTime >= InitHitCountTime)
	{
		if (InitHitCountTimerHandle.IsValid())
		{
			GetWorld()->GetTimerManager().ClearTimer(InitHitCountTimerHandle);
		}
		HitCount = 0;
		CurrentInitHitCountTime = 0.0f;

		HitTextBox->SetVisibility(ESlateVisibility::Hidden);
	}
	
}

void UMeleeWidget::HitSizeChangeFunc()
{
	CurrentHitSizeChangeTime = FMath::Min(CurrentHitSizeChangeTime+TimeOffset,1.0f);

	// Curve 반영
	{
		float ScaleSize = HitSizeCurve->GetFloatValue(CurrentHitSizeChangeTime);
		if(HitSizeCurve && HitTextBox )
		{
			FWidgetTransform NewTransform{ FVector2D{0.0f},FVector2D{ScaleSize},FVector2D{0.0f},0.0f };
			HitTextBox->SetRenderTransform(NewTransform);
		}

	}

	if(CurrentHitSizeChangeTime >= 1.0f)
	{
		if (InitHitCountTimerHandle.IsValid())
		{
			GetWorld()->GetTimerManager().ClearTimer(HitTextSizeChangeTimerHandle);
		}
		CurrentHitSizeChangeTime = 0.0f;
	}
}

void UMeleeWidget::AddHitCount()
{
	++HitCount;

	if(HitCountText)
	{
		HitCountText->SetText(FText::FromString(FString::FromInt(HitCount)));
	}

	// hit count 초기화 함수
	{
		CurrentInitHitCountTime = 0.0f;
		if (!InitHitCountTimerHandle.IsValid())
		{
			HitTextBox->SetVisibility(ESlateVisibility::Visible);
			GetWorld()->GetTimerManager().SetTimer(InitHitCountTimerHandle, this, &ThisClass::InitHitCountFunc, TimeOffset, true, TimeOffset);
		}
	}

	// Hit text 사이즈 조절
	{
		CurrentHitSizeChangeTime = 0.0f;
		if(!HitTextSizeChangeTimerHandle.IsValid())
		{
			GetWorld()->GetTimerManager().SetTimer(HitTextSizeChangeTimerHandle, this, &ThisClass::HitSizeChangeFunc, TimeOffset, true, TimeOffset);
		}
	}
	
}

void UMeleeWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void UMeleeWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
}
