// Fill out your copyright notice in the Description page of Project Settings.

#include "LoginWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"

void ULoginWidget::NativeConstruct()
{
	//Super::NativeConstruct();
	PlayButton->OnClicked.AddUniqueDynamic(this, &ULoginWidget::OnPlayButtonClick);
	RegisterButton->OnClicked.AddUniqueDynamic(this, &ULoginWidget::OnRegisterButtonClick);
}

void ULoginWidget::OnPlayButtonClick()
{
	FText IDText = IdEditable->GetText();
	FText PasswordText = PasswordEditable->GetText();
}

void ULoginWidget::OnRegisterButtonClick()
{

}
