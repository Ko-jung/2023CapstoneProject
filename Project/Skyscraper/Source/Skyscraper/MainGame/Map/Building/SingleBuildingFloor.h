// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SingleBuildingFloor.generated.h"

UCLASS()
class SKYSCRAPER_API ASingleBuildingFloor : public AActor
{
	GENERATED_BODY()

	// �ǹ� �� ���� ����ƽ �޽ÿ� ���� �迭
	UPROPERTY(EditAnywhere)
		TArray<UStaticMeshComponent*> FloorStaticMeshes;

	// ����â�� ���� ����ƽ �޽� �迭
	UPROPERTY(EditAnywhere)
		TArray<UStaticMeshComponent*> WindowStaticMeshes;

	/* �ر� �� ���� Geometry Collection */
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
