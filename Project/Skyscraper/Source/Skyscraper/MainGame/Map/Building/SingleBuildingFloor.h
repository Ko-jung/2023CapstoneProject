// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SingleBuildingFloor.generated.h"

UCLASS()
class SKYSCRAPER_API ASingleBuildingFloor : public AActor
{
	GENERATED_BODY()

	// 건물 한 충의 스태틱 메시에 대한 배열
	UPROPERTY(EditAnywhere)
		TArray<UStaticMeshComponent*> FloorStaticMeshes;

	// 유리창에 대한 스태틱 메시 배열
	UPROPERTY(EditAnywhere)
		TArray<UStaticMeshComponent*> WindowStaticMeshes;

	/* 붕괴 후 생길 Geometry Collection */
	UPROPERTY()
		UClass* GC_BuildingClass;
public:
	void CreateFloorStaticMeshes();
	// Sets default values for this actor's properties
	ASingleBuildingFloor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DoCollapse();
};
