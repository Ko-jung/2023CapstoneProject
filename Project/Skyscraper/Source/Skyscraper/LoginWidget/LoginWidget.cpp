// Fill out your copyright notice in the Description page of Project Settings.

#include "LoginWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/TextBlock.h"

#include "Skyscraper/Network/Packet.h"
#include "Kismet/GameplayStatics.h"
#include "Skyscraper/Network/LoginGameMode.h"

void ULoginWidget::NativeConstruct()
{
	Super::NativeConstruct();
	

}

bool ULoginWidget::Initialize()
{
	bool Succ = Super::Initialize();
	if (!Succ) return false;

	PlayButton->OnClicked.AddDynamic(this, &ULoginWidget::OnPlayButtonClick);
	RegisterButton->OnClicked.AddDynamic(this, &ULoginWidget::OnRegisterButtonClick);
	QuitButton->OnClicked.AddDynamic(this, &ULoginWidget::OnQuitButtonClick);

	ExtraMessage->SetVisibility(ESlateVisibility::Hidden);
	return true;
}

void ULoginWidget::OnPlayButtonClick()
{
	FText IDText = IdEditable->GetText();
	FText PasswordText = PasswordEditable->GetText();

	FString IDFString = IDText.ToString();
	std::string IDString = TCHAR_TO_UTF8(*IDFString);
	FString PasswordFString = PasswordText.ToString();
	std::string PasswordString = TCHAR_TO_UTF8(*PasswordFString);

	PTryLogin PTL;
	strcpy_s(PTL.ID, IDString.c_str());
	strcpy_s(PTL.Password, PasswordString.c_str());
	PTL.IsRegister = false;

	//UE_LOG(LogClass, Warning, TEXT("ID: %s, Password: %s"), IDString, PasswordString);

	ALoginGameMode* LoginGameMode = Cast<ALoginGameMode>(UGameplayStatics::GetGameMode(this));
	LoginGameMode->Send(&PTL, sizeof(PTL));
}

void ULoginWidget::OnRegisterButtonClick()
{
	FText IDText = IdEditable->GetText();
	FText PasswordText = PasswordEditable->GetText();

	FString IDFString = IDText.ToString();
	std::string IDString = TCHAR_TO_UTF8(*IDFString);
	FString PasswordFString = PasswordText.ToString();
	std::string PasswordString = TCHAR_TO_UTF8(*PasswordFString);

	PTryLogin PTL;
	strcpy_s(PTL.ID, IDString.c_str());
	strcpy_s(PTL.Password, PasswordString.c_str());
	PTL.IsRegister = true;

	ALoginGameMode* LoginGameMode = Cast<ALoginGameMode>(UGameplayStatics::GetGameMode(this));
	LoginGameMode->Send(&PTL, sizeof(PTL));
}

void ULoginWidget::OnQuitButtonClick()
{
	if(GEngine)
	{
		UWorld* World = GEngine->GetWorldFromContextObjectChecked(this);
		if (World)
		{
			if (World->WorldType == EWorldType::Editor)
			{
				GEngine->Exec(World, TEXT("QUIT_EDITOR"));
			}
			else if (World->WorldType == EWorldType::Game || World->WorldType == EWorldType::PIE)
			{
				UKismetSystemLibrary::QuitGame(World, nullptr, EQuitPreference::Quit, false);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ULoginWidget::OnQuitButtonClick() GEngine is nullptr"));
	}
}

void ULoginWidget::SetExtraMessage(PLoginResult* PLR)
{
	FText ExtraMess;
	int8 ErrorCode = PLR->LoginResult;
	if (PLR->IsRegister)
	{
		switch (ErrorCode)
		{
		case (int8)ELoginResult::DatabaseError:
			ExtraMess = FText::FromString(TEXT("DatabaseError"));
			break;
		case (int8)ELoginResult::IDError:
			ExtraMess = FText::FromString(TEXT("Duplicate ID"));
			break;
		case (int8)ELoginResult::PasswordError:
			ExtraMess = FText::FromString(TEXT(""));
			break;
		default:
			break;
		}
	}
	else
	{
		switch (ErrorCode)
		{
		case (int8)ELoginResult::DatabaseError:
			ExtraMess = FText::FromString(TEXT("DatabaseError"));
			break;
		case (int8)ELoginResult::IDError:
			ExtraMess = FText::FromString(TEXT("IDError"));
			break;
		case (int8)ELoginResult::PasswordError:
			ExtraMess = FText::FromString(TEXT("PasswordError"));
			break;
		default:
			break;
		}
	}

	//ExtraMessage->SetColorAndOpacity();
	ExtraMessage->SetVisibility(ESlateVisibility::Visible);
	ExtraMessage->SetText(ExtraMess);
}

FString ULoginWidget::GetLoginId()
{
	FText IDText = IdEditable->GetText();
	FString IDFString = IDText.ToString();
	return IDFString;
}
