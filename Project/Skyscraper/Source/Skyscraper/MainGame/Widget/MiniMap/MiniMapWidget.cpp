// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniMapWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Skyscraper/MainGame/Map/HexagonTile/HexagonTile.h"

void UMiniMapWidget::SetTileImageAlignment(int index, FVector2D NewAlignment)
{
	if (index >= TileImages.Num()) return;

	if(UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(TileImages[index]->Slot))
	{
		CanvasPanelSlot->SetAlignment(NewAlignment);
	}
}

void UMiniMapWidget::SetTileImage(int index, ETileImageType TileImageType)
{
	if (index >= TileImages.Num()) return;
	if (TileImageType == ETileImageType::ETIT_SIZE) return;

	TileImages[index]->SetBrushFromTexture(TileTextures[(int8)TileImageType]);
	
}

void UMiniMapWidget::CollapseTileImage(int index)
{
	if (index >= TileImages.Num()) return;

	SetTileImage(index, ETileImageType::ETIT_Collapse);
	TileImages.RemoveAt(index);

	UE_LOG(LogTemp, Warning, TEXT("%d index's Is Collapse"), index);
}

void UMiniMapWidget::SetPlayerImageAlignment(FVector2D NewAlignment, float NewAngle)
{
	if (UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(PlayerImageAndActor.ImageWidget->Slot))
	{
		CanvasPanelSlot->SetAlignment(NewAlignment);
	}
	PlayerImageAndActor.ImageWidget->SetRenderTransformAngle(NewAngle);
}

void UMiniMapWidget::SetOtherPlayerImageAlignment(UImage* TargetPlayerImage, FVector2D NewAlignment)
{
	if (UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(TargetPlayerImage->Slot))
	{
		CanvasPanelSlot->SetAlignment(NewAlignment);
	}
}

void UMiniMapWidget::AddPlayerToImage(AActor* Player)
{
	if(!Player)
	{
		return;
	}

	// 새로운 캐릭터로 바로 적용될 수 있도록 그냥 대입
	//if(PlayerImageAndActor.Actor)
	PlayerImageAndActor.Actor = Player;
	
}

void UMiniMapWidget::AddFriendlyPlayerToImage(AActor* FriendlyPlayer)
{
	if (!FriendlyPlayer) 
	{
		return;
	}

	for(FImageAndActor& ImageAndActor : FriendlyPlayerImagesAndActors)
	{
		if(! ImageAndActor.Actor)
		{
			ImageAndActor.Actor = FriendlyPlayer;
			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("이미 모든 아군 이미지를 사용중"));
}

void UMiniMapWidget::AddEnemyPlayerToImage(AActor* EnemyPlayer)
{
	if (!EnemyPlayer)
	{
		return;
	}

	for (FImageAndActor& ImageAndActor : EnemyPlayerImagesAndActors)
	{
		if (!ImageAndActor.Actor)
		{
			ImageAndActor.Actor = EnemyPlayer;
			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("이미 모든 적군 이미지를 사용중"));
}


void UMiniMapWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	// 캔버스 찾기
	{
		TileImageCanvas = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("TileImageCanvas")));
	}

	// 타일 이미지 위젯들 찾기
	{
		for (int i = 0; i < 37; ++i)
		{
			FName WidgetName = FName(FString("TileImage_") + FString::FromInt(i));
			TileImages.Add(Cast<UImage>(GetWidgetFromName(WidgetName)));
		}
	}

	// 타일 이미지 텍스쳐 로드
	{
		for (int i = 0; i < (int8)ETileImageType::ETIT_SIZE; ++i)
		{
			TileTextures.AddDefaulted();
		}

		static UTexture2D* BuildingTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, L"/Script/Engine.Texture2D'/Game/2016180023/UI/MAP_BUILDING.MAP_BUILDING'"));
		TileTextures[(int8)ETileImageType::ETIT_Building] = BuildingTexture;

		static UTexture2D* ItemTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, L"/Script/Engine.Texture2D'/Game/2016180023/UI/MAP_ITEM.MAP_ITEM'"));
		TileTextures[(int8)ETileImageType::ETIT_Item] = ItemTexture;

		static UTexture2D* NormalTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, L"/Script/Engine.Texture2D'/Game/2016180023/UI/MAP_NORMAL_TILE.MAP_NORMAL_TILE'"));
		TileTextures[(int8)ETileImageType::ETIT_Normal] = NormalTexture;


		static UTexture2D* CollapseTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, L"/Script/Engine.Texture2D'/Game/2016180023/UI/EMPTY_BACKGROUND.EMPTY_BACKGROUND'"));
		TileTextures[(int8)ETileImageType::ETIT_Collapse] = CollapseTexture;

		static UTexture2D* FloatTileTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, L"/Script/Engine.Texture2D'/Game/2016180023/UI/MAP_FLOAT.MAP_FLOAT'"));
		TileTextures[(int8)ETileImageType::ETIT_FloatTile] = FloatTileTexture;
	}

	// 플레이어 이미지 찾기
	{
		PlayerImageAndActor.ImageWidget = Cast<UImage>(GetWidgetFromName(TEXT("PlayerImageWidget")));
	}

	// 아군 플레이어 이미지
	{
		FriendlyPlayerImagesAndActors.Add(FImageAndActor{ Cast<UImage>(GetWidgetFromName("FriendlyPlayerWidget_1")) , nullptr });
		FriendlyPlayerImagesAndActors.Add(FImageAndActor{ Cast<UImage>(GetWidgetFromName("FriendlyPlayerWidget_2")) , nullptr });
	}

	// 적군 플레이어 이미지
	{
		EnemyPlayerImagesAndActors.Add(FImageAndActor{ Cast<UImage>(GetWidgetFromName("EnemyPlayerWidget_1")) , nullptr });
		EnemyPlayerImagesAndActors.Add(FImageAndActor{ Cast<UImage>(GetWidgetFromName("EnemyPlayerWidget_2")) , nullptr });
		EnemyPlayerImagesAndActors.Add(FImageAndActor{ Cast<UImage>(GetWidgetFromName("EnemyPlayerWidget_3")) , nullptr });
	}
}

void UMiniMapWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HexagonTile = Cast<AHexagonTile>(UGameplayStatics::GetActorOfClass(this, AHexagonTile::StaticClass()));
}

bool UMiniMapWidget::CheckEnemyPlayerIsVisible(TObjectPtr<AActor> Actor)
{
	// 75도 반경을 관찰 영역으로 측정
	// 거리는 타일 반지름 * 3
	float CosHalfAngle = UKismetMathLibrary::DegCos(75.0f / 2.0f);
	
	float Distance = pow(HexagonTile->GetTileOffsetValue() * 3/2,2) ;

	AActor* Player = PlayerImageAndActor.Actor;

	FVector2D PlayerLocation2D = FVector2D{ Player->GetActorLocation() };
	FVector2D EnemyLocation2D = FVector2D{ Actor->GetActorLocation() };

	FVector2D PlayerForwardVector2D = FVector2D{ Player->GetActorForwardVector() };
	PlayerForwardVector2D.Normalize();

	FVector2D TargetVector2D = (EnemyLocation2D - PlayerLocation2D);
	TargetVector2D.Normalize();

	float CosAngleDiff = UKismetMathLibrary::DotProduct2D(PlayerForwardVector2D, TargetVector2D);

	// 시야각 외 구역에 존재
	if(CosAngleDiff < CosHalfAngle)
	{
		return false;
	}

	// 시야 거리 외 구역에 존재
	if (UKismetMathLibrary::DistanceSquared2D(PlayerLocation2D, EnemyLocation2D) > Distance)
	{
		return false;
	}

	return true;
}

void UMiniMapWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(! HexagonTile)
	{
		return;
	}

	// 자신 플레이어 위치 및 회전 적용
	{
		// 미니맵 내 액터 위치 설정
		if (PlayerImageAndActor.IsValid())
		{
			FVector ForwardVector = PlayerImageAndActor.Actor->GetActorRotation().Vector();
			FRotator RotationValue = UKismetMathLibrary::FindLookAtRotation(FVector{ 0.0f,0.0f,0.0f }, ForwardVector);
			SetPlayerImageAlignment(HexagonTile->GetAlignmentByLocation(PlayerImageAndActor.Actor->GetActorLocation()), RotationValue.Yaw);
		}
	}

	// 아군 및 적군 플레이어 위치 적용
	{
		for(FImageAndActor& ImageAndActor : FriendlyPlayerImagesAndActors)
		{
			if(ImageAndActor.Actor)
			{
				SetOtherPlayerImageAlignment(ImageAndActor.ImageWidget, HexagonTile->GetAlignmentByLocation(ImageAndActor.Actor->GetActorLocation()));
			}
		}

		// 적군 캐릭터에 대해서는 일정 거리 내, 특정 각도 내 있는 캐릭터에 대해서만 관찰 가능하게 설정
		for (FImageAndActor& ImageAndActor : EnemyPlayerImagesAndActors)
		{
			if (ImageAndActor.Actor)
			{
				if (CheckEnemyPlayerIsVisible(ImageAndActor.Actor))
				{
					ImageAndActor.ImageWidget->SetVisibility(ESlateVisibility::Visible);
					SetOtherPlayerImageAlignment(ImageAndActor.ImageWidget, HexagonTile->GetAlignmentByLocation(ImageAndActor.Actor->GetActorLocation()));
				}
				else
				{
					ImageAndActor.ImageWidget->SetVisibility(ESlateVisibility::Hidden);
				}
				
			}
		}
	}
}
