// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LiquidWetComponent.generated.h"


class ASkyscraperCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SKYSCRAPER_API ULiquidWetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULiquidWetComponent();

	
	UFUNCTION(BlueprintCallable)
		void SetSkirtGravity(float value);
protected:
	
	// Called when the game starts
	virtual void BeginPlay() override;
	void AddSkirtCollisionMesh();
	void FindOwnerClothConfigBase();

	void SetOwnerCharacterNewMesh();
private:
public:	
protected:
	TObjectPtr<ASkyscraperCharacter> OwnerCharacter;

	TObjectPtr<class UChaosClothConfig> SkirtConfig;
private:


		
};
