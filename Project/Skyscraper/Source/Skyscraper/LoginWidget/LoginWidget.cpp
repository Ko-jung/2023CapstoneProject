// Fill out your copyright notice in the Description page of Project Settings.

#include "LoginWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"

#include "Skyscraper/Network/Packet.h"
#include "Skyscraper/Network/Packet.h"

void ULoginWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// RegisterButton->OnClicked.AddUniqueDynamic(this, &ULoginWidget::OnRegisterButtonClick);
	

}

bool ULoginWidget::Initialize()
{
	bool Succ = Super::Initialize();
	if (!Succ) return false;

	if(!PlayButton)
		UE_LOG(LogClass, Warning, TEXT("PlayButton is Nullptr!"));

	PlayButton->OnClicked.AddDynamic(this, &ULoginWidget::OnPlayButtonClick);
	return true;
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

	UE_LOG(LogClass, Warning, TEXT("Play Button!"));
}

void ULoginWidget::OnRegisterButtonClick()
{
	FText IDText = IdEditable->GetText();
	FText PasswordText = PasswordEditable->GetText();
}
