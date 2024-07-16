// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCombatWidget.h"

#include "Components/Image.h"

void UMainCombatWidget::SetCharacterImage(ECharacterSelect CharacterType)
{
	if (CharacterType == ECharacterSelect::ECS_Null || CharacterType == ECharacterSelect::ECS_Count) return;

	if(CharacterTextures.IsValidIndex(static_cast<int>(CharacterType)) && CharacterTextures[static_cast<int>(CharacterType)])
	{
		CharacterImage->SetBrushFromTexture(CharacterTextures[static_cast<int>(CharacterType)]);
	}
}

void UMainCombatWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	for(int i = 0; i < static_cast<int>(ECharacterSelect::ECS_Count); ++i)
	{
		CharacterTextures.AddDefaulted();
	}

	static UTexture2D* AssassinTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, L"/Script/Engine.Texture2D'/Game/2016180023/UI/character/assassin.assassin'"));
	CharacterTextures[static_cast<int>(ECharacterSelect::ECS_AssassinCharacter)] = AssassinTexture;

	static UTexture2D* BoomerangTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, L"/Script/Engine.Texture2D'/Game/2016180023/UI/character/boomerang.boomerang'"));
	CharacterTextures[static_cast<int>(ECharacterSelect::ECS_BoomerangCharacter)] = BoomerangTexture;

	static UTexture2D* ElectricTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, L"/Script/Engine.Texture2D'/Game/2016180023/UI/character/electric.electric'"));
	CharacterTextures[static_cast<int>(ECharacterSelect::ECS_ElectricCharacter)] = ElectricTexture;

	static UTexture2D* RadarTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, L"/Script/Engine.Texture2D'/Game/2016180023/UI/character/radar.radar'"));
	CharacterTextures[static_cast<int>(ECharacterSelect::ECS_DetectionCharacter)] = RadarTexture;

	static UTexture2D* ShieldTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, L"/Script/Engine.Texture2D'/Game/2016180023/UI/character/shield.shield'"));
	CharacterTextures[static_cast<int>(ECharacterSelect::ECS_ShieldCharacter)] = ShieldTexture;

	static UTexture2D* WindTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, L"/Script/Engine.Texture2D'/Game/2016180023/UI/character/wind.wind'"));
	CharacterTextures[static_cast<int>(ECharacterSelect::ECS_WindCharacter)] = WindTexture;
}
