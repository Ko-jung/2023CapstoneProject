// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Skyscraper/Enum/ECharacterSelect.h"
#include "MainCombatWidget.generated.h"

class UImage;
class UProgressBar;
/**
 * 
 */
UCLASS()
class SKYSCRAPER_API UMainCombatWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
		void SetCharacterImage(ECharacterSelect CharacterType);

	// ===== 2019180016 =====
	UFUNCTION()
	void UseSkill(bool IsSpecial, float CoolTime);
	UFUNCTION()
	void UpdateProgressBar();
	void InitCoolTime();
	//=======================

protected:
	virtual void NativePreConstruct() override;


	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

private:
public:
protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		TObjectPtr<UImage> CharacterImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterTexture")
		TArray<TObjectPtr<UTexture2D>> CharacterTextures;


private:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* CommonSkillProgressBar;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* SpecialSkillProgressBar;

	float  CommonSkillCurrentTime;
	float SpecialSkillCurrentTime;

	float  CommonSkillRequestTime;
	float SpecialSkillRequestTime;
};
