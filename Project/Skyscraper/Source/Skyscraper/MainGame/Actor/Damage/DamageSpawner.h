// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageSpawner.generated.h"

class UNiagaraSystem;

UCLASS()
class SKYSCRAPER_API ADamageSpawner : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		int Damage;
	UPROPERTY(VisibleAnywhere)
		float TextOffsetY;
	UPROPERTY(VisibleAnywhere)
		TArray<UTexture*> DigitTexture;
	UPROPERTY(EditAnywhere)
		FVector DamageLocationOffset;
	UPROPERTY(EditAnywhere)
		float DigitScale;
	UPROPERTY(EditAnywhere)
		UNiagaraSystem* FX_FloatingDamage;

	UPROPERTY(VisibleAnywhere)
		FVector InitLocation;
	UPROPERTY(VisibleAnywhere)
		FRotator InitRotator;

	UPROPERTY(VisibleAnywhere)
		USceneComponent* SpawnerRootComponent;
public:	
	// Sets default values for this actor's properties
	ADamageSpawner();

protected:
	void SpawnDamageFX(const std::string& DamageString);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Initialize(float InDamage, float InScale);
};
