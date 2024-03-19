// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RangeWeaponDetail.generated.h"

class UImage;
class UButton;
class UWidgetSwitcher;
UCLASS()
class SKYSCRAPER_API URangeWeaponDetail : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	// 원거리 무기 이미지 변수
	UPROPERTY(meta = (BindWidget))
		UImage* SMGImage;
	UPROPERTY(meta = (BindWidget))
		UImage* RifleImage;
	UPROPERTY(meta = (BindWidget))
		UImage* RPGImage;

	// 원거리 무기 설명 선택 버튼 변수
	UPROPERTY(meta = (BindWidget))
		UButton* SMGSelectButton;
	UPROPERTY(meta = (BindWidget))
		UButton* RifleSelectButton;
	UPROPERTY(meta = (BindWidget))
		UButton* RPGSelectButton;

	// 원거리 무기 설명 위젯 스위쳐 변수
	UPROPERTY(meta = (BindWidget))
		UWidgetSwitcher* RangeSwitcher;

	void SetSwitcherValue(int32 Value) const;
public:
	/* Getter */
	FORCEINLINE UImage* GetSMGImage() const { return SMGImage; }
	FORCEINLINE UImage* GetRifleImage() const { return RifleImage; }
	FORCEINLINE UImage* GetRPGImage() const { return RPGImage; }

	FORCEINLINE UButton* GetSMGSelectButton() const { return SMGSelectButton; }
	FORCEINLINE UButton* GetRifleSelectButton() const { return RifleSelectButton; }
	FORCEINLINE UButton* GetRPGSelectButton() const { return RPGSelectButton; }

	FORCEINLINE UWidgetSwitcher* GetRangeSwitcher() const { return RangeSwitcher; }

	UFUNCTION()
		void OnClickSMGSelectButton();
	UFUNCTION()
		void OnClickRifleSelectButton();
	UFUNCTION()
		void OnClickRPGSelectButton();

};
