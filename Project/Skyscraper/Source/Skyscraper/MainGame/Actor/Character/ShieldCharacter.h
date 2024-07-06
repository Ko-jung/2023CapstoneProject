// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "ShieldCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API AShieldCharacter : public ASkyscraperCharacter
{
	GENERATED_BODY()
public:
	AShieldCharacter();

	// 2019180016
	virtual void CastingSkill(bool IsSpecialSkill);
	// ==========
};
