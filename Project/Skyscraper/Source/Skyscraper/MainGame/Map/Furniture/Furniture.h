// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Furniture.generated.h"

class USpotLightComponent;
class UHierarchicalInstancedStaticMeshComponent;
class ADesk;

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
	// =============== 컴퍼넌트 ===============
	UPROPERTY()
		TObjectPtr<UHierarchicalInstancedStaticMeshComponent> HISM_Table;
	UPROPERTY()
		TObjectPtr<UHierarchicalInstancedStaticMeshComponent> HISM_Sofa;
	UPROPERTY()
		TObjectPtr<UHierarchicalInstancedStaticMeshComponent> HISM_Flowerpot;

	UPROPERTY()
		TArray<TObjectPtr<USpotLightComponent>> SpotLights;

	UPROPERTY()
		TArray<TObjectPtr<ADesk>> DeskActors;
	// =======================================


	

private:

};
