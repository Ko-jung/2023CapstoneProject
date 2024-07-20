// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkyscraperCharacter.h"
#include "AssassinCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API AAssassinCharacter : public ASkyscraperCharacter
{
	GENERATED_BODY()

public:
	AAssassinCharacter();

	// 2019180016
	virtual void CharacterAttackEvent();

	UFUNCTION(BlueprintCallable)
	void BuffUsingSkill();

	UPROPERTY(BlueprintReadWrite)
	bool IsStealthMode;
	// ==========
};
