// Fill out your copyright notice in the Description page of Project Settings.


#include "WP_LoginWidget.h"

#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

void UWP_LoginWidget::NativeConstruct()
{
	FLinearColor LinearColor;
	LinearColor.R = 255;
	LinearColor.G = 50;
	LinearColor.B = 50;
	FSlateColor Color(LinearColor);
	ExtraMessage->SetColorAndOpacity(Color);

	ExtraMessage->SetVisibility(ESlateVisibility::Hidden);
}

//bool UWP_LoginWidget::Initialize()
//{
//	//ExtraMessage->SetVisibility(ESlateVisibility::Hidden);
//	return true;
//}
