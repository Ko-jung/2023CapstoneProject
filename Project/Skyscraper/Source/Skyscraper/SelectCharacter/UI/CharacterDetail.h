// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterDetail.generated.h"

class UWidgetSwitcher;
class UImage;
class UButton;
UCLASS()
class SKYSCRAPER_API UCharacterDetail : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual void Tick(FGeometry MyGeometry, float InDeltaTime);

private:
	// ĳ���� �̹��� ����
	UPROPERTY(meta = (BindWidget))
		UImage* ShieldImage;
	UPROPERTY(meta = (BindWidget))
		UImage* WindImage;
	UPROPERTY(meta = (BindWidget))
		UImage* ElectricImage;
	UPROPERTY(meta = (BindWidget))
		UImage* ThrowImage;
	UPROPERTY(meta = (BindWidget))
		UImage* AssassinImage;
	UPROPERTY(meta = (BindWidget))
		UImage* DetectionImage;

	// ĳ���� ���� ���� ��ư ����
	UPROPERTY(meta = (BindWidget))
		UButton* SelectShieldButton;
	UPROPERTY(meta = (BindWidget))
		UButton* SelectWindButton;
	UPROPERTY(meta = (BindWidget))
		UButton* SelectElectricButton;
	UPROPERTY(meta = (BindWidget))
		UButton* SelectThrowButton;
	UPROPERTY(meta = (BindWidget))
		UButton* SelectAssassinButton;
	UPROPERTY(meta = (BindWidget))
		UButton* SelectDetectionButton;

	// ĳ���� ���� ���� ������ ����
	UPROPERTY(meta = (BindWidget))
		UWidgetSwitcher* CharacterDetailSwitcher;

	void SetSwitcherValue(int32 Value) const;
public:
	FORCEINLINE UImage* GetShieldImage() const { return ShieldImage; }
	FORCEINLINE UImage* GetWindImage() const { return WindImage; }
	FORCEINLINE UImage* GetElectricImage() const { return ElectricImage; }
	FORCEINLINE UImage* GetThrowImage() const { return ThrowImage; }
	FORCEINLINE UImage* GetAssassinImage() const { return AssassinImage; }
	FORCEINLINE UImage* GetDetectionImage() const { return DetectionImage; }

	FORCEINLINE UButton* GetSelectShieldButton() const { return SelectShieldButton; }
	FORCEINLINE UButton* GetSelectWindButton() const { return SelectWindButton; }
	FORCEINLINE UButton* GetSelectElectricButton() const { return SelectElectricButton; }
	FORCEINLINE UButton* GetSelectThrowButton() const { return SelectThrowButton; }
	FORCEINLINE UButton* GetSelectAssassinButton() const { return SelectAssassinButton; }
	FORCEINLINE UButton* GetSelectDetectionButton() const { return SelectDetectionButton; }

	FORCEINLINE UWidgetSwitcher* GetCharacterDetailSwitcher() const { return CharacterDetailSwitcher; }

	UFUNCTION()
		void OnClickSelectShieldButton();
	UFUNCTION()
		void OnClickSelectWindButton();
	UFUNCTION()
		void OnClickSelectElectricButton();
	UFUNCTION()
		void OnClickSelectThrowButton();
	UFUNCTION()
		void OnClickSelectAssassinButton();
	UFUNCTION()
		void OnClickSelectDetectionButton();

private:
	class ASkyscraperGameMode* Gamemode;
};
