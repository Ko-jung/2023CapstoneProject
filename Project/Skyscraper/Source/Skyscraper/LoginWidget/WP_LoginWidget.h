// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WP_LoginWidget.generated.h"

class UButton;
class UEditableText;
class UTextBlock;

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API UWP_LoginWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	//virtual bool Initialize();
	
private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ExtraMessage;

	UPROPERTY(meta = (BindWidget))
	UButton* RegisterButton;

	UPROPERTY(meta = (BindWidget))
	UButton* PlayButton;

	UPROPERTY(meta = (BindWidget))
	UEditableText* IdEditable;

	UPROPERTY(meta = (BindWidget))
	UEditableText* PasswordEditable;
};
