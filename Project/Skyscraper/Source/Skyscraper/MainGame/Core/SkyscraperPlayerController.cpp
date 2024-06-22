// Fill out your copyright notice in the Description page of Project Settings.


#include "SkyscraperPlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "Skyscraper/MainGame/Component/Combat/CombatSystemComponent.h"
#include "Skyscraper/MainGame/Map/HexagonTile/HexagonTile.h"
#include "Skyscraper/MainGame/Widget/ChangeWeapon/ChangeWeaponWidget.h"
#include "Skyscraper/MainGame/Widget/GameResult/GameResultWidget.h"
#include "Skyscraper/MainGame/Widget/MiniMap/MiniMapWidget.h"
#include "Skyscraper/MainGame/Widget/TimeAndKillCount/TimeAndKillCountWidget.h"

ASkyscraperPlayerController::ASkyscraperPlayerController()
{

	static ConstructorHelpers::FClassFinder<UUserWidget> WBP_TimeAndKillCountRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/2019180031/MainGame/Widget/TimeAndKillCount/WBP_TimeAndKillCount.WBP_TimeAndKillCount_C'"));
	TimeAndKillCountWidgetClass = WBP_TimeAndKillCountRef.Class;


	static ConstructorHelpers::FClassFinder<UUserWidget> WBP_MiniMapRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/2019180031/MainGame/Widget/Map/WBP_Map.WBP_Map_C'"));
	MiniMapWidgetClass = WBP_MiniMapRef.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> WBP_ChangeWeapon(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/2019180031/MainGame/Widget/ChangeWeapon/WBP_ChangeWeapon.WBP_ChangeWeapon_C'"));
	ChangeWeaponWidgetClass = WBP_ChangeWeapon.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> WBP_GameResult(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/2019180031/MainGame/Widget/GameResult/WBP_GameResult.WBP_GameResult_C'"));
	GameResultWidgetClass = WBP_GameResult.Class;
}

void ASkyscraperPlayerController::AddChangeWeaponWidget()
{
	if(!ChangeWeaponWidget)
	{
		ChangeWeaponWidget = Cast<UChangeWeaponWidget>(CreateWidget(this, ChangeWeaponWidgetClass));
	}

	if(ChangeWeaponWidget)
	{
		if (PossessingPawn && PossessingPawn->CombatSystemComponent)
		{
			ChangeWeaponWidget->InitializeWeaponState(PossessingPawn->CombatSystemComponent->GetCurrentMeleeSelect(), PossessingPawn->CombatSystemComponent->GetCurrentRangeSelect());
			ChangeWeaponWidget->AddToViewport(15);
		}
			
	}
	
}

void ASkyscraperPlayerController::RemoveChangeWeaponWidget()
{
	if(ChangeWeaponWidget)
	{
		ChangeWeaponWidget->RemoveFromParent();
	}
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

void ASkyscraperPlayerController::AddGameResultWidget(const FText& WinnerText)
{
	if (!GameResultWidget)
	{
		GameResultWidget = Cast<UGameResultWidget>(CreateWidget(this, GameResultWidgetClass));
	}

	if (GameResultWidget)
	{
		GameResultWidget->SetWinnerText(WinnerText);
		GameResultWidget->AddToViewport(20);
	}
}

void ASkyscraperPlayerController::SetObserveMode(bool bToObserveMode)
{
	if(bToObserveMode)
	{
		if (PossessingPawn->GetAnimInstance() && PossessingPawn->GetAnimInstance()->IsAnyMontagePlaying()) return;

		PossessingPawn->bUseControllerRotationYaw = false;
		SetCanLookInput(true);
		PossessingPawn->DisableInput(this);
		LastRotator = GetControlRotation();
	}
	else
	{
		if (!bCanLookInput) return;

		SetControlRotation(LastRotator);
		LastRotator = FRotator{};

		PossessingPawn->bUseControllerRotationYaw = true;
		SetCanLookInput(false);
		PossessingPawn->EnableInput(this);

	}

}

void ASkyscraperPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetPossessingPawn();

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

	UpdateImage();
	

}

void ASkyscraperPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// 캐릭터 - 컨트롤러 yaw 분리시(Separate Camera 모드) && 인풋 입력 제한 시 직접 회전 처리
	// if (bCanLookInput && !(Cast<ASkyscraperCharacter>(GetOwner())->InputEnabled()))
	if(bCanLookInput && PossessingPawn && !PossessingPawn->InputEnabled())
	{
		if(IsInputKeyDown(EKeys::LeftAlt))
		{
			FVector2D MouseDeltaValue{};
			GetInputMouseDelta(MouseDeltaValue.X, MouseDeltaValue.Y);

			SetControlRotation(GetControlRotation().Add(MouseDeltaValue.Y, MouseDeltaValue.X, 0.0f));
		}
		else
		{
			SetObserveMode(false);
			UE_LOG(LogTemp, Warning, TEXT("놨음"));
		}
	}

	if (MiniMapWidget && MiniMapWidget->GetPlayerImage() && HexagonTile)
	{
		FVector ForwardVector = GetControlRotation().Vector();
		FRotator RotationValue = UKismetMathLibrary::FindLookAtRotation(FVector{ 0.0f,0.0f,0.0f }, ForwardVector);
		MiniMapWidget->SetPlayerImageAlignment(HexagonTile->GetAlignmentByLocation(PossessingPawn->GetActorLocation()), RotationValue.Yaw);
	}

}

void ASkyscraperPlayerController::UpdateImage()
{
	HexagonTile = Cast<AHexagonTile>(UGameplayStatics::GetActorOfClass(this, AHexagonTile::StaticClass()));

	// 육각 타일 이미지 배치
	if (HexagonTile)
	{
		for (int i = 0; i < 37; ++i)
		{
			if (MiniMapWidget)
			{
				MiniMapWidget->SetTileImageAlignment(i, HexagonTile->GetTileWidgetAlignment(i));
				MiniMapWidget->SetTileImage(i, HexagonTile->GetTileImageType(i));
			}

		}
	}
}

void ASkyscraperPlayerController::UpdateImage(int index)
{
	HexagonTile = Cast<AHexagonTile>(UGameplayStatics::GetActorOfClass(this, AHexagonTile::StaticClass()));

	if (HexagonTile)
	{
		if (MiniMapWidget)
		{
			MiniMapWidget->SetTileImageAlignment(index, HexagonTile->GetTileWidgetAlignment(index));
			MiniMapWidget->SetTileImage(index, HexagonTile->GetTileImageType(index));
		}
	}
}

void ASkyscraperPlayerController::SetPossessingPawn()
{
	PossessingPawn = Cast<ASkyscraperCharacter>(GetPawn());
}
