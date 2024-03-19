// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MeleeWeaponDetail.generated.h"

class UWidgetSwitcher;
class UImage;
class UButton;
UCLASS()
class SKYSCRAPER_API UMeleeWeaponDetail : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	// 근접 무기 이미지 변수
	UPROPERTY(meta = (BindWidget))
		UImage* DaggerImage;
	UPROPERTY(meta = (BindWidget))
		UImage* KatanaImage;
	UPROPERTY(meta = (BindWidget))
		UImage* GreatSwordImage;

	// 근접 무기 설명 선택 버튼 변수
	UPROPERTY(meta = (BindWidget))
		UButton* DaggerSelectButton;
	UPROPERTY(meta = (BindWidget))
		UButton* KatanaSelectButton;
	UPROPERTY(meta = (BindWidget))
		UButton* GreatSwordButton;

	// 설명 위젯 스위쳐 변수
	UPROPERTY(meta = (BindWidget))
		UWidgetSwitcher* MeleeSwitcher;

	void SetSwitcherValue(int32 Value) const;
public:
	/* Getter */
	FORCEINLINE UImage* GetDaggerImage() const { return DaggerImage; }
	FORCEINLINE UImage* GetKatanaImage() const { return KatanaImage; }
	FORCEINLINE UImage* GetGreatSwordImage() const { return GreatSwordImage; }

	FORCEINLINE UButton* GetDaggerSelectButton() const { return DaggerSelectButton; }
	FORCEINLINE UButton* GetKatanaSelectButton() const { return KatanaSelectButton; }
	FORCEINLINE UButton* GetGreatSwordButton() const { return GreatSwordButton; }

	FORCEINLINE UWidgetSwitcher* GetMeleeSwitcher() const { return MeleeSwitcher; }

	UFUNCTION()
		void OnClickDaggerButton();
	UFUNCTION()
		void OnClickKatanaButton();
	UFUNCTION()
		void OnClickGreatSwordButton();

};
