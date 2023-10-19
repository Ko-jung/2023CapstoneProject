// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleMenu.generated.h"

class UButton;
class UWidgetSwitcher;
class UEditableText;

/**
 * 
 */
UCLASS()
class BASICMULTIPLAYERMELEECOMB_API UTitleMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;
	
private:
	UPROPERTY(meta = (BindWidget))
	UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
	UButton* EnterButton;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* Switcher;

	UPROPERTY(meta = (BindWidget))
	UEditableText* AddressInput;

	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void JoinServer();

	UFUNCTION()
	void Quit();

	UFUNCTION()
	void EnterServer();

	UFUNCTION()
	void Cencel();
};
