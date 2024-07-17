// Fill out your copyright notice in the Description page of Project Settings.


#include "SkyscraperEngineSubsystem.h"

#include "Skyscraper/MainGame/Data/Sound/FSoundData.h"

USoundBase* USkyscraperEngineSubsystem::GetSkyscraperSound(FName RowName) const
{
	USoundBase* ReturnSound{};

	if (FSoundData* SoundData = SoundDataTable->FindRow<FSoundData>(RowName, ""))
	{
		ReturnSound = SoundData->SoundAsset;
	}

	return ReturnSound;
}

void USkyscraperEngineSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// 사운드 데이터 테이블 로드
	{
		UDataTable* TempDataTable{};
		FSoftObjectPath DataTablePath = FSoftObjectPath(TEXT("/Script/Engine.DataTable'/Game/2019180031/DT_SoundData.DT_SoundData'"));
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
}
