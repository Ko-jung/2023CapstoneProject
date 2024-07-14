// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GravityChangerArea.generated.h"

UCLASS()
class SKYSCRAPER_API AGravityChangerArea : public AActor
{
	GENERATED_BODY()
	
public:	
	AGravityChangerArea();

	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

public:
protected:
private:
};
