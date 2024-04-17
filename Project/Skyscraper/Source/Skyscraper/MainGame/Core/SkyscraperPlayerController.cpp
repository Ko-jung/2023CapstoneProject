// Fill out your copyright notice in the Description page of Project Settings.


#include "SkyscraperPlayerController.h"

#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"

ASkyscraperPlayerController::ASkyscraperPlayerController()
{
}

void ASkyscraperPlayerController::BeginPlay()
{
	Super::BeginPlay();
	PossessingPawn = Cast<ASkyscraperCharacter>(GetPawn());
}

void ASkyscraperPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// ĳ���� - ��Ʈ�ѷ� yaw �и���(Separate Camera ���) && ��ǲ �Է� ���� �� ���� ȸ�� ó��
	if(bCanLookInput && !PossessingPawn->InputEnabled())
	{
		FVector2D MouseDeltaValue{};
		GetInputMouseDelta(MouseDeltaValue.X, MouseDeltaValue.Y);
		
		SetControlRotation(GetControlRotation().Add(MouseDeltaValue.Y,MouseDeltaValue.X, 0.0f));
	}
	
}
