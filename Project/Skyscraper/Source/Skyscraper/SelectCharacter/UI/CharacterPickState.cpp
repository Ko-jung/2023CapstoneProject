#include "CharacterPickState.h"

#include "Components/Button.h"
// Fill out your copyright notice in the Description page of Project Settings.

void UCharacterPickState::NativeConstruct()
{
	MyCharacterButton->OnClicked.AddUniqueDynamic(this, &ThisClass::GoToDetail);
	MyMeleeButton->OnClicked.AddUniqueDynamic(this, &ThisClass::GoToDetail);
	MyRangeButton->OnClicked.AddUniqueDynamic(this, &ThisClass::GoToDetail);
}

void UCharacterPickState::NativeDestruct()
{
	Super::NativeDestruct();
}

void UCharacterPickState::GoToDetail()
{
	if(MyCharacterButton->GetVisibility()==ESlateVisibility::Hidden)
	{
		MyCharacterButton->SetVisibility(ESlateVisibility::Visible);
	}else
	{
		MyCharacterButton->SetVisibility(ESlateVisibility::Hidden);
	}
	
}
