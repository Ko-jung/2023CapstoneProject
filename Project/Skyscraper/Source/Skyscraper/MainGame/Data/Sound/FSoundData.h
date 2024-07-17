// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "FSoundData.generated.h"

class USoundBase;

USTRUCT()
struct FSoundData : public FTableRowBase
{
	GENERATED_BODY()
public:
	FSoundData() {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoundAsset")
		TObjectPtr<USoundBase> SoundAsset;
		
};
