// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LiquidWetComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SKYSCRAPER_API ULiquidWetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULiquidWetComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void SetSkirtGravity(float value);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void FindOwnerClothConfigBase();

	void SetOwnerCharacterNewMesh();
private:
public:	
protected:
	TObjectPtr<ACharacter> OwnerCharacter;

	TObjectPtr<class UChaosClothConfig> SkirtConfig;
private:


		
};
