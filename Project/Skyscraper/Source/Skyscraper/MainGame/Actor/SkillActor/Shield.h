// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Skyscraper/MainGame/Actor/Character/ShieldCharacter.h"

#include "Shield.generated.h"

UCLASS()
class SKYSCRAPER_API AShield : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShield();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void GetDamage(float Damage);

	UFUNCTION(BlueprintCallable)
	void SetSpawnCharacter(AShieldCharacter* Character) { SpawnCharacter = Character; }
protected:
	UPROPERTY(BlueprintReadWrite)
	AShieldCharacter* SpawnCharacter;

};
