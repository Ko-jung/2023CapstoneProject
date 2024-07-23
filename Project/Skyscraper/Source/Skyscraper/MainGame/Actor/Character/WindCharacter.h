// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkyscraperCharacter.h"
#include "WindCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API AWindCharacter : public ASkyscraperCharacter
{
	GENERATED_BODY()
public:
	AWindCharacter();

	virtual void SetBoostEffectVisibility(bool bVisible) override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TObjectPtr<UNiagaraComponent> NS_BoostEffectRight;

	// 2019180016
	// 
	// ==========
};
