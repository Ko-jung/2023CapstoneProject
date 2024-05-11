// Fill out your copyright notice in the Description page of Project Settings.


#include "SkyscraperPlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "Skyscraper/MainGame/Component/Combat/CombatSystemComponent.h"
#include "Skyscraper/MainGame/Map/HexagonTile/HexagonTile.h"
#include "Skyscraper/MainGame/Widget/MiniMap/MiniMapWidget.h"
#include "Skyscraper/MainGame/Widget/TimeAndKillCount/TimeAndKillCountWidget.h"

ASkyscraperPlayerController::ASkyscraperPlayerController()
{

	static ConstructorHelpers::FClassFinder<UUserWidget> WBP_TimeAndKillCountRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/2019180031/MainGame/Widget/TimeAndKillCount/WBP_TimeAndKillCount.WBP_TimeAndKillCount_C'"));
	TimeAndKillCountWidgetClass = WBP_TimeAndKillCountRef.Class;


	static ConstructorHelpers::FClassFinder<UUserWidget> WBP_MiniMapRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/2019180031/MainGame/Widget/Map/WBP_Map.WBP_Map_C'"));
	MiniMapWidgetClass = WBP_MiniMapRef.Class;
}

void ASkyscraperPlayerController::ChangePlayerMeleeWeapon(EMeleeSelect NewMeleeSelect) const
{
	if(PossessingPawn && PossessingPawn->CombatSystemComponent)
	{
		PossessingPawn->CombatSystemComponent->ChangeMeleeWeapon(NewMeleeSelect);
	}

}

void ASkyscraperPlayerController::ChangePlayerRangeWeapon(ERangeSelect NewRangeSelect) const
{
	if (PossessingPawn && PossessingPawn->CombatSystemComponent)
	{
		PossessingPawn->CombatSystemComponent->ChangeRangeWeapon(NewRangeSelect);
	}
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

	MiniMapWidget = Cast<UMiniMapWidget>(CreateWidget(this, MiniMapWidgetClass));
	if(MiniMapWidget)
	{
		MiniMapWidget->AddToViewport();
	}

	{//TODO: 서버이전 전 테스트용 코드
		AHexagonTile* HexagonTile = Cast<AHexagonTile>(UGameplayStatics::GetActorOfClass(this, AHexagonTile::StaticClass()));

		if (HexagonTile) 
		{
			for(int i =0 ;i<37; ++i)
			{
				if(MiniMapWidget)
				{
					MiniMapWidget->SetTileImageAlignment(i, HexagonTile->GetTileWidgetAlignment(i));
					MiniMapWidget->SetTileImage(i, HexagonTile->GetTileImageType(i));
				}
				
			}
		}
	}
	

}

void ASkyscraperPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// 캐릭터 - 컨트롤러 yaw 분리시(Separate Camera 모드) && 인풋 입력 제한 시 직접 회전 처리
	// if (bCanLookInput && !(Cast<ASkyscraperCharacter>(GetOwner())->InputEnabled()))
	if(bCanLookInput && PossessingPawn && !PossessingPawn->InputEnabled())
	{
		FVector2D MouseDeltaValue{};
		GetInputMouseDelta(MouseDeltaValue.X, MouseDeltaValue.Y);
		
		SetControlRotation(GetControlRotation().Add(MouseDeltaValue.Y,MouseDeltaValue.X, 0.0f));
	}
	
}
