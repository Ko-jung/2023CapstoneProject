// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkyscraperCharacter.h"
#include "BoomerangCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API ABoomerangCharacter : public ASkyscraperCharacter
{
	GENERATED_BODY()
public:
	ABoomerangCharacter();

protected:
private:

public:
	// ===== 2019180016 =====
	UFUNCTION(BlueprintNativeEvent)
	void SpawnBoomerangActor(bool IsSpecialSkill);

	virtual void CastingSkill(bool IsSpecialSkill);
	// ======================

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boost")
	TObjectPtr<UStaticMeshComponent> Boomerang_R;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boost")
		TObjectPtr<UStaticMeshComponent> Boomerang_L;

private:
};

