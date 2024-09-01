// Fill out your copyright notice in the Description page of Project Settings.


#include "SkyscraperPlayerController.h"

#include "GameFramework/DefaultPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "Skyscraper/MainGame/Component/Combat/CombatSystemComponent.h"
#include "Skyscraper/MainGame/Map/HexagonTile/HexagonTile.h"
#include "Skyscraper/MainGame/Widget/ChangeWeapon/ChangeWeaponWidget.h"
#include "Skyscraper/MainGame/Widget/GameResult/GameResultWidget.h"
#include "Skyscraper/MainGame/Widget/Item/ItemWidget.h"
#include "Skyscraper/MainGame/Widget/LockOn/LockOnWidget.h"
#include "Skyscraper/MainGame/Widget/MiniMap/MiniMapWidget.h"
#include "Skyscraper/MainGame/Widget/TimeAndKillCount/TimeAndKillCountWidget.h"
#include "Skyscraper/MainGame/Widget/Combat/MainCombatWidget.h"
// 2019180016 if Lobby Gamemode, No use Widget
#include "SkyscraperPlayerController.h"

#include "Skyscraper/Network/LobbyMode.h"

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

	static ConstructorHelpers::FClassFinder<UUserWidget> WBP_LockOnWidgetRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/2019180031/MainGame/Widget/Lockon/WBP_LockOn.WBP_LockOn_C'"));
	LockOnWidgetClass = WBP_LockOnWidgetRef.Class;


	static ConstructorHelpers::FClassFinder<UUserWidget> WBP_MainCombatWidgetRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/2019180031/MainGame/Widget/MainCombatHUD/WBP_MainCombatHUD.WBP_MainCombatHUD_C'"));
	MainCombatWidgetClass = WBP_MainCombatWidgetRef.Class;
}

UMiniMapWidget* ASkyscraperPlayerController::GetMiniMapWidget() const
{
	return MiniMapWidget;
}

ULockOnWidget* ASkyscraperPlayerController::GetLockOnWidget() const
{
	return LockOnWidget;
}

UMainCombatWidget* ASkyscraperPlayerController::GetMainCombatWidget() const
{
	return MainCombatWidget;
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

void ASkyscraperPlayerController::AddGameResultWidget(const bool IsWin)
{
	if (!GameResultWidget)
	{
		GameResultWidget = Cast<UGameResultWidget>(CreateWidget(this, GameResultWidgetClass));
	}

	if (GameResultWidget)
	{
		GameResultWidget->SetWinnerText(IsWin);
		GameResultWidget->AddToViewport(20);
	}
}

void ASkyscraperPlayerController::SetObserveMode(bool bToObserveMode)
{
	if (!PossessingPawn) return;

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

		//PossessingPawn->RemoveObserveInputMappingContext();
		PossessingPawn->RemoveAllInputMappingTemporary();
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

void ASkyscraperPlayerController::CastingSkill(bool IsSpecialSkill, float CoolTime)
{
	if (MainCombatWidget)
	{
		MainCombatWidget->UseSkill(IsSpecialSkill, CoolTime);
	}
}

void ASkyscraperPlayerController::InitCoolTime(bool IsSpecial)
{
	if (MainCombatWidget)
	{
		MainCombatWidget->InitCoolTime(IsSpecial);
	}
}

void ASkyscraperPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetPossessingPawn();

	PlayerCameraManager->ViewPitchMin = -45.0f;
	PlayerCameraManager->ViewPitchMax = 45.0f;


	if (!Cast<ALobbyMode>(GetWorld()->GetAuthGameMode()))	// 2019180016 If Lobby Gamemode, no use
	{
		TimeAndKillCountWidget = Cast<UTimeAndKillCountWidget>(CreateWidget(this, TimeAndKillCountWidgetClass));
		if(TimeAndKillCountWidget)
		{
			TimeAndKillCountWidget->AddToViewport();
		}
	}
	else													// 2019180016
	{
		UE_LOG(LogTemp, Warning, TEXT("Gamemode is LobbyGameMode"));
	}
	//

	if(PossessingPawn)
	{
		ItemWidget = Cast<UItemWidget>(CreateWidget(this, ItemWidgetClass));
		if (ItemWidget)
		{
			ItemWidget->AddToViewport();
		}
	}
	

	MiniMapWidget = Cast<UMiniMapWidget>(CreateWidget(this, MiniMapWidgetClass));
	if(MiniMapWidget)
	{
		MiniMapWidget->AddToViewport();
		if(PossessingPawn)
		{
			MiniMapWidget->AddPlayerToImage(PossessingPawn);
		}
		else if(APawn* DefaultPawn = Cast<ADefaultPawn>(GetPawn()))
		{
			MiniMapWidget->AddPlayerToImage(GetPawn());
		}
		
		UpdateImage();
	}
	
	LockOnWidget = Cast<ULockOnWidget>(CreateWidget(this, LockOnWidgetClass));
	if(LockOnWidget)
	{
		LockOnWidget->AddToViewport();
		LockOnWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	
	MainCombatWidget = Cast<UMainCombatWidget>(CreateWidget(this, MainCombatWidgetClass));
	if(MainCombatWidget)
	{
		MainCombatWidget->AddToViewport();

		if(PossessingPawn)
			MainCombatWidget->SetCharacterImage(PossessingPawn->CharacterType);
	}
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

	if (SerialNum < MaxPlayer / 2)
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

void ASkyscraperPlayerController::AddAllWidget()
{
	if(TimeAndKillCountWidget)
		TimeAndKillCountWidget->RemoveFromParent();

	if (!Cast<ALobbyMode>(GetWorld()->GetAuthGameMode()))	// 2019180016 If Lobby Gamemode, no use
	{
		TimeAndKillCountWidget = Cast<UTimeAndKillCountWidget>(CreateWidget(this, TimeAndKillCountWidgetClass));
		if (TimeAndKillCountWidget)
		{
			TimeAndKillCountWidget->AddToViewport();
		}
	}
	else													// 2019180016
	{
		UE_LOG(LogTemp, Warning, TEXT("Gamemode is LobbyGameMode"));
	}
	//

	if (ItemWidget)
		ItemWidget->RemoveFromParent();
	ItemWidget = Cast<UItemWidget>(CreateWidget(this, ItemWidgetClass));
	if (ItemWidget)
	{
		ItemWidget->AddToViewport();
	}

	if (MiniMapWidget)
		MiniMapWidget->RemoveFromParent();
	MiniMapWidget = Cast<UMiniMapWidget>(CreateWidget(this, MiniMapWidgetClass));
	if (MiniMapWidget)
	{
		MiniMapWidget->AddToViewport();
		if (PossessingPawn)
		{
			MiniMapWidget->AddPlayerToImage(PossessingPawn);
		}
		else if (APawn* DefaultPawn = Cast<ADefaultPawn>(GetPawn()))
		{
			MiniMapWidget->AddPlayerToImage(GetPawn());
		}

		UpdateImage();
	}

	if (LockOnWidget)
		LockOnWidget->RemoveFromParent();
	LockOnWidget = Cast<ULockOnWidget>(CreateWidget(this, LockOnWidgetClass));
	if (LockOnWidget)
	{
		LockOnWidget->AddToViewport();
		LockOnWidget->SetVisibility(ESlateVisibility::Hidden);
	}


	if (MainCombatWidget)
		MainCombatWidget->RemoveFromParent();
	MainCombatWidget = Cast<UMainCombatWidget>(CreateWidget(this, MainCombatWidgetClass));
	if (MainCombatWidget)
	{
		MainCombatWidget->AddToViewport();

		if (PossessingPawn)
			MainCombatWidget->SetCharacterImage(PossessingPawn->CharacterType);
	}
}
