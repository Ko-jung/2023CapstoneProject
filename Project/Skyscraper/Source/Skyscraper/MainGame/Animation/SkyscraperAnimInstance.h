// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SkyscraperAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API USkyscraperAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	USkyscraperAnimInstance();

protected:
private:
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
		bool bIsDescent;
protected:
private:
};
