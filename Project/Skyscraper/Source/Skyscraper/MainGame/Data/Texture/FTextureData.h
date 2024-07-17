// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "FTextureData.generated.h"

class UTexture2D;

USTRUCT()
struct FTextureData : public FTableRowBase
{
	GENERATED_BODY()
public:
	FTextureData() {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextureAsset")
		TObjectPtr<UTexture2D> TextureAsset;
		
};
