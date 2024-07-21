// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skyscraper/SkyscraperWidget/SkyscraperWidget.h"
#include "LoginWidget.generated.h"

class UButton;
class UEditableText;
class UTextBlock;

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API ULoginWidget : public USkyscraperWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual bool Initialize();

	UFUNCTION()
	void OnPlayButtonClick();
	UFUNCTION()
	void OnRegisterButtonClick();
	UFUNCTION()
	void OnQuitButtonClick();

	void SetExtraMessage(struct PLoginResult* PLR);

	FString GetLoginId();

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ExtraMessage;

	UPROPERTY(meta = (BindWidget))
	UButton* RegisterButton;

	UPROPERTY(meta = (BindWidget))
	UButton* PlayButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	UEditableText* IdEditable;

	UPROPERTY(meta = (BindWidget))
	UEditableText* PasswordEditable;
};
