// Fill out your copyright notice in the Description page of Project Settings.


#include "SkyscraperPlayerController.h"

#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "Skyscraper/MainGame/Widget/TimeAndKillCount/TimeAndKillCountWidget.h"

ASkyscraperPlayerController::ASkyscraperPlayerController()
{

	static ConstructorHelpers::FClassFinder<UUserWidget> WBP_TimeAndKillCountRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/2019180031/MainGame/Widget/TimeAndKillCount/WBP_TimeAndKillCount.WBP_TimeAndKillCount_C'"));
	TimeAndKillCountWidgetClass = WBP_TimeAndKillCountRef.Class;
}

void ASkyscraperPlayerController::BeginPlay()
{
	Super::BeginPlay();
	PossessingPawn = Cast<ASkyscraperCharacter>(GetPawn());

	TimeAndKillCountWidget = Cast<UTimeAndKillCountWidget>(CreateWidget(this, TimeAndKillCountWidgetClass));
	if(TimeAndKillCountWidget)
	{
		TimeAndKillCountWidget->AddToViewport();
	}
	
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
