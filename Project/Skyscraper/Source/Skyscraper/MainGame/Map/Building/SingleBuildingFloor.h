// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SingleBuildingFloor.generated.h"

class AFurniture;

UCLASS()
class SKYSCRAPER_API ASingleBuildingFloor : public AActor
{
	GENERATED_BODY()

public:
	ASingleBuildingFloor();

	void DoCollapse();

	// ====== 2019180016 ======
	void DoCollapseWindow(UStaticMeshComponent* Target, FVector ForceDirection);
	// ========================

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

public:

protected:
	// 건물 한 충의 스태틱 메시에 대한 배열
	UPROPERTY(EditAnywhere)
		TArray<UStaticMeshComponent*> FloorStaticMeshes;

	// 유리창에 대한 스태틱 메시 배열
	UPROPERTY(EditAnywhere)
		TArray<UStaticMeshComponent*> WindowStaticMeshes;

	/* 붕괴 후 생길 Geometry Collection */
	UPROPERTY()
		UClass* GC_BuildingClass;

	// 가구들에 대한 액터 및 클래스
	UPROPERTY()
		TObjectPtr<AFurniture> FurnitureActor;

private:
	// ====== 2019180016 ======
	UPROPERTY()
		TArray<UClass*> GC_WindowClass;

	UPROPERTY()
		UClass* BPGCWindowActorClass;

	// UPROPERTY()
	// TArray<UObject*> GC_WindowObject;
	// ========================
};
