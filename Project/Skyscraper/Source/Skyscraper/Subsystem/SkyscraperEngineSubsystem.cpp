// Fill out your copyright notice in the Description page of Project Settings.


#include "SkyscraperEngineSubsystem.h"

#include "Skyscraper/MainGame/Data/Sound/FSoundData.h"
#include "Skyscraper/MainGame/Data/Texture/FTextureData.h"

USoundBase* USkyscraperEngineSubsystem::GetSkyscraperSound(FName RowName) const
{
	USoundBase* ReturnSound{};

	if (FSoundData* SoundData = SoundDataTable->FindRow<FSoundData>(RowName, ""))
	{
		ReturnSound = SoundData->SoundAsset;
	}

	return ReturnSound;
}

UTexture2D* USkyscraperEngineSubsystem::GetSkyscraperCharacterTexture(ECharacterSelect CharacterType)
{
	UTexture2D* ReturnTexture{};

	FName RowName = GetCharacterNameByECharacterSelect(CharacterType);
	if (FTextureData* TextureData = TextureDataTable->FindRow<FTextureData>(RowName, ""))
	{
		ReturnTexture = TextureData->TextureAsset;
	}

	return ReturnTexture;
}

void USkyscraperEngineSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// 사운드 데이터 테이블 로드
	{
		UDataTable* TempDataTable{};
		FSoftObjectPath DataTablePath = FSoftObjectPath(TEXT("/Script/Engine.DataTable'/Game/2019180031/MainGame/Data/Sound/DT_SoundData.DT_SoundData'"));
		TempDataTable = Cast<UDataTable>(DataTablePath.ResolveObject());
		if(TempDataTable)
		{
			SoundDataTable = TempDataTable;
		}
		else
		{
			TempDataTable = Cast<UDataTable>(DataTablePath.TryLoad());
			if(TempDataTable)
			{
				SoundDataTable = TempDataTable;
			}
		}
	}

	// 텍스쳐 데이터 테이블 로드
	{
		UDataTable* TempDataTable{};
		FSoftObjectPath DataTablePath = FSoftObjectPath(TEXT("/Script/Engine.DataTable'/Game/2019180031/MainGame/Data/Texture/TextureData.TextureData'"));
		TempDataTable = Cast<UDataTable>(DataTablePath.ResolveObject());
		if (TempDataTable)
		{
			TextureDataTable = TempDataTable;
		}
		else
		{
			TempDataTable = Cast<UDataTable>(DataTablePath.TryLoad());
			if (TempDataTable)
			{
				TextureDataTable = TempDataTable;
			}
		}
	}
}

FName USkyscraperEngineSubsystem::GetCharacterNameByECharacterSelect(ECharacterSelect CharacterSelect)
{
	FName ReturnName{};
	switch (CharacterSelect)
	{
	case ECharacterSelect::ECS_AssassinCharacter:
		ReturnName = TEXT("Assassin");
		break;
	case ECharacterSelect::ECS_BoomerangCharacter:
		ReturnName = TEXT("Boomerang");
		break;
	case ECharacterSelect::ECS_ElectricCharacter:
		ReturnName = TEXT("Electric");
		break;
	case ECharacterSelect::ECS_DetectionCharacter:
		ReturnName = TEXT("Radar");
		break;
	case ECharacterSelect::ECS_ShieldCharacter:
		ReturnName = TEXT("Shield");
		break;
	case ECharacterSelect::ECS_WindCharacter:
		ReturnName = TEXT("Wind");
		break;
	default:
		break;
	}

	return ReturnName;
}
