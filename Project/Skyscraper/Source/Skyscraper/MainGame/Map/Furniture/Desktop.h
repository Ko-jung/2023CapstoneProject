// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Desktop.generated.h"

UCLASS()
class SKYSCRAPER_API ADesktop : public AActor
{
	GENERATED_BODY()
public:
	ADesktop();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:

public:
protected:
	UPROPERTY()
		TArray<TObjectPtr<UStaticMeshComponent>> Desktops;

private:

};
