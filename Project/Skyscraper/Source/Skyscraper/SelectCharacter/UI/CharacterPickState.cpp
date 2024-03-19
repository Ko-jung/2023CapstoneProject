#include "CharacterPickState.h"

#include "Components/Button.h"
#include "../Core/SelectCharacterController.h"
#include "Kismet/GameplayStatics.h"
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
	if(ASelectCharacterController* Controller = Cast<ASelectCharacterController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))  )
	{
		Controller->SetDetailWidgetVisibility(true);
	}
}
