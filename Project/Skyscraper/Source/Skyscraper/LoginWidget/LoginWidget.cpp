// Fill out your copyright notice in the Description page of Project Settings.

#include "LoginWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"

#include "Skyscraper/Network/Packet.h"
#include "Skyscraper/Network/Packet.h"

void ULoginWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// PlayButton->OnClicked.AddUniqueDynamic(this, &ULoginWidget::OnPlayButtonClick);
	// RegisterButton->OnClicked.AddUniqueDynamic(this, &ULoginWidget::OnRegisterButtonClick);
	

}

void ULoginWidget::OnPlayButtonClick()
{
	FText IDText = IdEditable->GetText();
	FText PasswordText = PasswordEditable->GetText();

	FString IDFString = IDText.ToString();
	std::string IDString = TCHAR_TO_UTF8(*IDFString);
	FString PasswordFString = IDText.ToString();
	std::string PasswordString = TCHAR_TO_UTF8(*PasswordFString);

	PTryLogin PTL;
	strcpy_s(PTL.ID, IDString.c_str());
	strcpy_s(PTL.Password, PasswordString.c_str());
	
}

void ULoginWidget::OnRegisterButtonClick()
{
	FText IDText = IdEditable->GetText();
	FText PasswordText = PasswordEditable->GetText();
}
