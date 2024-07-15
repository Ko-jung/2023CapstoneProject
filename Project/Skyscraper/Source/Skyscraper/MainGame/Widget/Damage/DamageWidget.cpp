// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Engine/Canvas.h"
#include "Kismet/KismetStringLibrary.h"

void UDamageWidget::CreateDamageImage(int Damage, int LengthOfDamage)
{
	if (!MainCanvas) {
		return;
	}

	for (int i = 0; i< LengthOfDamage; ++i)
	{
		FString Name = "Image" + FString::FromInt(i);
		UImage* NewImage = Cast<UImage>(NewObject<UImage>(this, UImage::StaticClass(), FName(Name)));
		DamageImages.Add(NewImage);

		MainCanvas->AddChild(NewImage);
		UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(NewImage->Slot);

		CanvasPanelSlot->SetSize(FVector2D{ 40.0f,80.0f });
		CanvasPanelSlot->SetAlignment(FVector2D{  ((DamageImages.Num() - 1) * -1.0f), 0.0f });

		//int TextureIndex = Damage / (10 ^ (LengthOfDamage - 1 - i)) % 10;
		FString DamageString = FString::FromInt(Damage);
		int TextureIndex = FCString::Atoi(*UKismetStringLibrary::GetSubstring(DamageString, i, 1));
		
		NewImage->SetBrushFromTexture(DamageTextures[TextureIndex]);
		
	}
}

