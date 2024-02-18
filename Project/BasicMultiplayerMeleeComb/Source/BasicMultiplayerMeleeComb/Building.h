// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapCollapseInterface.h"
#include "GameFramework/Actor.h"
#include "Building.generated.h"

UENUM(BlueprintType)
enum class BuildingComposition
{
	Floor,
	Wall1,Wall2,Wall3,Wall4
};


UCLASS()
class BASICMULTIPLAYERMELEECOMB_API ABuilding : public AActor, public IMapCollapseInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	/* 건물 붕괴 진행 시 호출 함수 */
	UFUNCTION(BlueprintCallable)
		void CollapseBuilding(int32 CollapseStartFloor);

	/* 건물 붕괴 적용 함수 */
	//UFUNCTION(BlueprintCallable)
	void SwapStaticToGeometry(UStaticMeshComponent* Target, BuildingComposition Composition);

	/* 루트 컴퍼넌트 */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default")
		TObjectPtr<USceneComponent> DefaultSceneRoot;


	/* 건물의 초기/최대 층수 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default", meta = (ExposeOnSpawn = "true"))
		int32 Floor = 5;

	/* 층 간 높이 */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		double FloorDistance;

	/* 벽 간 길이 (오프셋) */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		double WallOffset;

	/* 바닥/벽에 대한 Static Mesh */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		TArray<UStaticMeshComponent*> Building_Floor;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		TArray<UStaticMeshComponent*> Building_Wall1;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		TArray<UStaticMeshComponent*> Building_Wall2;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		TArray<UStaticMeshComponent*> Building_Wall3;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		TArray<UStaticMeshComponent*> Building_Wall4;

	/* 게임진행중 현재 층 수에 대한 변수 */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		int32 CurrentFloor;

	/* 바닥/벽 에 대한 Geometry Actor */
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AActor> GC_Floor;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AActor> GC_Wall01;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AActor> GC_Wall02;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AActor> GC_Wall03;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AActor> GC_Wall04;

public:
	/* IMapCollapseInterface */
	virtual void DoCollapse() override;
};
