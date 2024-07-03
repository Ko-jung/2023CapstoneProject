// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidget.h"

#include "Components/Image.h"


void UItemWidget::SetItemImageTexture(EItemEffect ItemEffect)
{
	ItemImage->SetBrushFromTexture(ItemTexture[(int8)ItemEffect]);
}

void UItemWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	for(int i =0; i<(int8)EItemEffect::EIE_COUNT; ++i)
	{
		ItemTexture.AddDefaulted();
	}
	

	ItemTexture[(int8)EItemEffect::EIE_NONE] = nullptr;

	
	static UTexture2D* InfinityTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, L"/Script/Engine.Texture2D'/Game/2016180023/UI/item/infinite.infinite'"));
	ItemTexture[(int8)EItemEffect::EIE_Single_BoostBulletInfinity] = InfinityTexture;

	static UTexture2D* GodModeTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, L"/Script/Engine.Texture2D'/Game/2016180023/UI/item/invincible.invincible'"));
	ItemTexture[(int8)EItemEffect::EIE_Single_GodMode] = GodModeTexture;


	static UTexture2D* PlusHealthTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, L"/Script/Engine.Texture2D'/Game/2016180023/UI/item/hp_up.hp_up'"));
	ItemTexture[(int8)EItemEffect::EIE_Team_PlusHealth] = PlusHealthTexture;

	static UTexture2D* PowerUpTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, L"/Script/Engine.Texture2D'/Game/2016180023/UI/item/attack_up.attack_up'"));
	ItemTexture[(int8)EItemEffect::EIE_Team_Power] = PowerUpTexture;

	static UTexture2D* SpeedUpTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, L"/Script/Engine.Texture2D'/Game/2016180023/UI/item/speed_up.speed_up'"));
	ItemTexture[(int8)EItemEffect::EIE_Team_Speed] = SpeedUpTexture;

	static UTexture2D* GravityUpTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, L"/Script/Engine.Texture2D'/Game/2016180023/UI/item/gravity_up.gravity_up'"));
	ItemTexture[(int8)EItemEffect::EIE_Gravity_Up] = GravityUpTexture;

	static UTexture2D* GravityDownTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, L"/Script/Engine.Texture2D'/Game/2016180023/UI/item/gravity_down.gravity_down'"));
	ItemTexture[(int8)EItemEffect::EIE_Gravity_Down] = GravityDownTexture;

	static UTexture2D* TileBreakTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, L"/Script/Engine.Texture2D'/Game/2016180023/UI/item/tile_break.tile_break'"));
	ItemTexture[(int8)EItemEffect::EIE_Tile_Break] = TileBreakTexture;
}
