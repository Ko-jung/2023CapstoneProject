// Fill out your copyright notice in the Description page of Project Settings.


#include "SkyscraperPlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "Skyscraper/MainGame/Component/Combat/CombatSystemComponent.h"
#include "Skyscraper/MainGame/Map/HexagonTile/HexagonTile.h"
#include "Skyscraper/MainGame/Widget/ChangeWeapon/ChangeWeaponWidget.h"
#include "Skyscraper/MainGame/Widget/GameResult/GameResultWidget.h"
#include "Skyscraper/MainGame/Widget/Item/ItemWidget.h"
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

	static ConstructorHelpers::FClassFinder<UUserWidget> WBP_ItemRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/2019180031/MainGame/Widget/Item/WBP_Item.WBP_Item_C'"));
	ItemWidgetClass = WBP_ItemRef.Class;
}

UMiniMapWidget* ASkyscraperPlayerController::GetMiniMapWidget() const
{
	return MiniMapWidget;
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
		//if (PossessingPawn->GetAnimInstance() && PossessingPawn->GetAnimInstance()->IsAnyMontagePlaying()) return;

		PossessingPawn->bUseControllerRotationYaw = false;
		PossessingPawn->RemoveAllInputMappingTemporary();

		LastRotator = GetControlRotation();
		PossessingPawn->AddObserveInputMappingContext();
	}
	else
	{
		SetControlRotation(LastRotator);
		LastRotator = FRotator{};

		PossessingPawn->RemoveObserveInputMappingContext();
		PossessingPawn->bUseControllerRotationYaw = true;
		PossessingPawn->AddAllInputMappingContext();
		

	}

}

void ASkyscraperPlayerController::SetSpectatorMode(bool bSetMode, AActor* NewDamageCauser)
{
	if(bSetMode)
	{
		bSpectatorMode = true;
		DamageCauser = NewDamageCauser;
	}
	else
	{
		bSpectatorMode = false;
		DamageCauser = nullptr;
	}
}

void ASkyscraperPlayerController::PressSetSpecatatorButton()
{
	ChangeWeaponWidget->SetChangeWeaponWidgetVisibility(ESlateVisibility::Hidden);
	SetViewTargetWithBlend(DamageCauser);
}

void ASkyscraperPlayerController::PressChangeWeaponButton()
{
	ChangeWeaponWidget->SetChangeWeaponWidgetVisibility(ESlateVisibility::Visible);
	SetViewTargetWithBlend(PossessingPawn);
}

void ASkyscraperPlayerController::SetItemImage(EItemEffect ItemEffect)
{
	if(ItemWidget)
	{
		ItemWidget->SetItemImageTexture(ItemEffect);
	}
}

void ASkyscraperPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetPossessingPawn();

	PlayerCameraManager->ViewPitchMin = -45.0f;
	PlayerCameraManager->ViewPitchMax = 45.0f;

	TimeAndKillCountWidget = Cast<UTimeAndKillCountWidget>(CreateWidget(this, TimeAndKillCountWidgetClass));
	if(TimeAndKillCountWidget)
	{
		TimeAndKillCountWidget->AddToViewport();
	}

	ItemWidget = Cast<UItemWidget>(CreateWidget(this, ItemWidgetClass));
	if (ItemWidget)
	{
		ItemWidget->AddToViewport();
	}

	MiniMapWidget = Cast<UMiniMapWidget>(CreateWidget(this, MiniMapWidgetClass));
	if(MiniMapWidget)
	{
		MiniMapWidget->AddToViewport();
		MiniMapWidget->AddPlayerToImage(PossessingPawn);
	}

	UpdateImage();
	

}

void ASkyscraperPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

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

void ASkyscraperPlayerController::SetPlayerImage(int MaxPlayer, TArray<ASkyscraperCharacter*> PlayerCharacter, int SerialNum)
{
	MiniMapWidget->AddPlayerToImage(PlayerCharacter[SerialNum]);

	if (SerialNum < MaxPlayer)
	{
		for (int i = 0; i < MaxPlayer / 2; i++)
		{
			if(i != SerialNum)
				MiniMapWidget->AddFriendlyPlayerToImage(PlayerCharacter[i]);
		}
		for (int i = MaxPlayer / 2; i < MaxPlayer; i++)
		{
			MiniMapWidget->AddEnemyPlayerToImage(PlayerCharacter[i]);
		}
	}
	else
	{
		for (int i = 0; i < MaxPlayer / 2; i++)
		{
			MiniMapWidget->AddEnemyPlayerToImage(PlayerCharacter[i]);
		}
		for (int i = MaxPlayer / 2; i < MaxPlayer; i++)
		{
			if (i != SerialNum)
				MiniMapWidget->AddFriendlyPlayerToImage(PlayerCharacter[i]);
		}
	}
}
