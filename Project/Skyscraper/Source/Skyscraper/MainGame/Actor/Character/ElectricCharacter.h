// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkyscraperCharacter.h"
#include "ElectricCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API AElectricCharacter : public ASkyscraperCharacter
{
	GENERATED_BODY()
public:
	AElectricCharacter();

	// 2019180016
	virtual void CastingSkill(bool IsSpecialSkill);
	// ==========
};
