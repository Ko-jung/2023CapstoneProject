// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClientTestCharacter.h"
#include "ClientCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CLIENTTEST_API AClientCharacter : public AClientTestCharacter
{
	GENERATED_BODY()
	
public:
	// To add mapping context
	virtual void BeginPlay();

public:
	UPROPERTY(BlueprintReadWrite)
	float Speed;
};
