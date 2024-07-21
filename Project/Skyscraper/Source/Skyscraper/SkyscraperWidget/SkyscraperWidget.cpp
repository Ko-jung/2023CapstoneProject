// Fill out your copyright notice in the Description page of Project Settings.


#include "SkyscraperWidget.h"
#include "Skyscraper/Subsystem/SkyscraperEngineSubsystem.h"
#include "Kismet/GameplayStatics.h"

void USkyscraperWidget::PlayButtonOnClickSound()
{
	if (!GEngine) return;

	USoundBase* BtnSound = GEngine->GetEngineSubsystem<USkyscraperEngineSubsystem>()->GetSkyscraperSound(FName("Button_other"));
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), BtnSound, FVector{}, FRotator::ZeroRotator);
}
