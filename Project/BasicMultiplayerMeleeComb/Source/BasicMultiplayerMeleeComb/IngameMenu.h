// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IngameMenu.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class BASICMULTIPLAYERMELEECOMB_API UIngameMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

private:
	//UPROPERTY(meta = (BindWidget))
	//UButton* ResumeButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;


	//UFUNCTION()
	//void Resume();

	UFUNCTION()
	void Quit();

	UFUNCTION()
	void Exit();
	
};
