// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Furniture.generated.h"

UCLASS()
class SKYSCRAPER_API AFurniture : public AActor
{
	GENERATED_BODY()
	
public:	
	AFurniture();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:

public:
protected:
	UPROPERTY()
		TArray<TObjectPtr<UStaticMeshComponent>> FurnitureObjects;

private:

};
