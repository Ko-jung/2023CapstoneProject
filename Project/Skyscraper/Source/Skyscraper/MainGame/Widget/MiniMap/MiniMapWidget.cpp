// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniMapWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"

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

void UMiniMapWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	TileImageCanvas = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("TileImageCanvas")));

	for(int i =0; i<37; ++i)
	{
		FName WidgetName = FName(FString("TileImage_") + FString::FromInt(i));
		TileImages.Add(Cast<UImage>(GetWidgetFromName(WidgetName)));
	}

	for(int i =0; i<(int8)ETileImageType::ETIT_SIZE; ++i)
	{
		TileTextures.AddDefaulted();
	}

	static UTexture2D* BuildingTexture  = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, L"/Script/Engine.Texture2D'/Game/2016180023/UI/MAP_BUILDING.MAP_BUILDING'"));
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