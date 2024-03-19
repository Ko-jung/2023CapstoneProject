// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectDetail.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

void USelectDetail::NativeConstruct()
{
	Super::NativeConstruct();

	CharacterDetailButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClickCharacterDetailButton);
	MeleeDetailButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClickMeleeDetailButton);
	RangeDetailButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClickRangeDetailButton);
	GoToLastButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClickGoToLastButton);

	DetailSwitcher->SetVisibility(ESlateVisibility::Hidden);
}

void USelectDetail::NativeDestruct()
{
	Super::NativeDestruct();
}

void USelectDetail::SetSwitcherValue(int32 Value) const
{
	// ���� �����ִ� ��ư�� ��� ���̱� ����
	if(DetailSwitcher->GetActiveWidgetIndex() == Value && DetailSwitcher->GetVisibility()==ESlateVisibility::Visible)
	{
		DetailSwitcher->SetVisibility(ESlateVisibility::Hidden);
		return;
	}
	DetailSwitcher->SetVisibility(ESlateVisibility::Visible);
	DetailSwitcher->SetActiveWidgetIndex(Value);
}

void USelectDetail::OnClickCharacterDetailButton()
{
	SetSwitcherValue(0);

}

void USelectDetail::OnClickMeleeDetailButton()
{
	SetSwitcherValue(1);
}

void USelectDetail::OnClickRangeDetailButton()
{
	SetSwitcherValue(2);
}

void USelectDetail::OnClickGoToLastButton()
{
	UE_LOG(LogTemp, Warning, TEXT("���� ȭ������ ���ư��� ��ư ����"));
}
