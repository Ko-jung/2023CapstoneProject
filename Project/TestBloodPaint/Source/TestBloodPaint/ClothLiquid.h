// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ClothLiquid.generated.h"


class UChaosClothConfig;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTBLOODPAINT_API UClothLiquid : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClothLiquid();

	UFUNCTION(BlueprintCallable)
		void DebugBlueprintCallable();

	UFUNCTION(BlueprintCallable)
		void SetSkirtGravity(float value);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void FindOwnerClothConfigBase();
private:

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	TObjectPtr<UChaosClothConfig> SkirtConfig;

private:
		
};
