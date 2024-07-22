// Fill out your copyright notice in the Description page of Project Settings.


#include "TileBreakItemWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "Skyscraper/MainGame/Core/SkyscraperPlayerController.h"
#include "Skyscraper/MainGame/Map/Furniture/Furniture.h"
#include "Skyscraper/MainGame/Map/HexagonTile/HexagonTile.h"
#include "Skyscraper/Subsystem/SkyscraperEngineSubsystem.h"
#include <Blueprint/WidgetBlueprintLibrary.h>

#include "Skyscraper/Network/MainGameMode.h"
#include "Kismet/GameplayStatics.h"


void UTileBreakItemWidget::SetEnemyPlayer(int PlayerIndex, ASkyscraperCharacter* TargetCharacter)
{
	if (TargetCharacters[PlayerIndex]) return;

	TargetCharacters[PlayerIndex] = TargetCharacter;

	//SetPlayerImage
	SetPlayerImage(PlayerIndex, TargetCharacter->CharacterType);
}

void UTileBreakItemWidget::FirstButtonClicked()
{
	if(TargetCharacters[0])
	{
		CollapseTileWithEnemy(0);
	}
}

void UTileBreakItemWidget::SecondButtonClicked()
{
	if (TargetCharacters[1])
	{
		CollapseTileWithEnemy(1);
	}
}

void UTileBreakItemWidget::ThirdButtonClicked()
{
	if (TargetCharacters[2])
	{
		CollapseTileWithEnemy(2);
	}
}

void UTileBreakItemWidget::CollapseTileWithEnemy(int PlayerIndex)
{
	AMainGameMode* GameMode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(this));
	GameMode->SendTileBreakItem(UseCharacter, PlayerIndex);


	//Move to AMainGameMode::ProcessTileBreakItem(const uint8 TargetSerial)
	// // 게임 플레이 중 타일 붕괴 아이템이 등장할 때에만 작동하는 함수이므로 GetAllActorsOfClass를 사용
	// TArray<AActor*> TargetActors;
	// UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFurniture::StaticClass(),TargetActors);
	// 
	// bool bUseItem{false};
	// for(AActor* Actor : TargetActors)
	// {
	// 	if(AFurniture* Furniture = Cast<AFurniture>(Actor))
	// 	{
	// 		if(Furniture->CollapseByTileCollapseItem(TargetCharacters[PlayerIndex]))
	// 		{
	// 			bUseItem = true;
	// 			break;
	// 		}
	// 	}
	// }
	//
	// // 아이템을 사용하지 못했다면 그대로 정지
	// if(!bUseItem)
	// {
	// 	return;
	// }

	// 아이템을 정상적으로 사용 시 위젯 종료
	RemoveFromParent();
}

void UTileBreakItemWidget::CancelUsingItem()
{
	if(GetOwningPlayer())
	{
		if(ASkyscraperPlayerController* PlayerController = Cast<ASkyscraperPlayerController>(GetOwningPlayer()))
		{
			if(PlayerController->GetPossessingPawn())
			{
				PlayerController->GetPossessingPawn()->AddItem(EItemEffect::EIE_Tile_Break, EItemRareLevel::EIRL_Normal, nullptr);
			}
		}
	}
	RemoveFromParent();
}

void UTileBreakItemWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	PlayerImages.Add(FirstPlayerImage);
	PlayerImages.Add(SecondPlayerImage);
	PlayerImages.Add(ThirdPlayerImage);

	TargetCharacters.AddDefaulted();
	TargetCharacters.AddDefaulted();
	TargetCharacters.AddDefaulted();

	if(FirstPlayerButton)
	{
		FirstPlayerButton->OnClicked.AddUniqueDynamic(this, &ThisClass::FirstButtonClicked);
	}
	if (SecondPlayerButton)
	{
		SecondPlayerButton->OnClicked.AddUniqueDynamic(this, &ThisClass::SecondButtonClicked);
	}
	if (ThirdPlayerImage)
	{
		ThirdPlayerButton->OnClicked.AddUniqueDynamic(this, &ThisClass::ThirdButtonClicked);
	}
	if(CancelButton)
	{
		CancelButton->OnClicked.AddUniqueDynamic(this, &ThisClass::CancelUsingItem);
	}
	
}

void UTileBreakItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ASkyscraperPlayerController* OwnerPlayerController = Cast<ASkyscraperPlayerController>(GetOwningPlayer());
	OwnerPlayerController->SetShowMouseCursor(true);
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(OwnerPlayerController);
}

void UTileBreakItemWidget::NativeDestruct()
{
	Super::NativeDestruct();

	ASkyscraperPlayerController* OwnerPlayerController = Cast<ASkyscraperPlayerController>(GetOwningPlayer());
	OwnerPlayerController->SetShowMouseCursor(false);
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(OwnerPlayerController);
}

void UTileBreakItemWidget::SetPlayerImage(int PlayerIndex, ECharacterSelect CharacterType)
{
	UTexture2D* Texture = GEngine->GetEngineSubsystem<USkyscraperEngineSubsystem>()->GetSkyscraperCharacterTexture(CharacterType);

	if(PlayerImages[PlayerIndex])
	{
		PlayerImages[PlayerIndex]->SetBrushFromTexture(Texture);
	}
	
}

