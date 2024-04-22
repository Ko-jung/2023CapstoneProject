// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Building.generated.h"

class ASingleBuildingFloor;

UENUM(BlueprintType)
enum class BuildingComposition
{
	BC_Floor = 0,
	BC_Wall1, BC_Wall2, BC_Wall3, BC_Wall4,
	BC_SIZE

};

UCLASS()
class SKYSCRAPER_API ABuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuilding();

	void Initialize(int32 GetFloor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	///* 건물 붕괴 진행 시 호출 함수 */
	//UFUNCTION(BlueprintCallable)
	//	void CollapseBuilding(int32 CollapseStartFloor);

	///* 건물 붕괴 적용 함수 */
	////UFUNCTION(BlueprintCallable)
	//void SwapStaticToGeometry(UStaticMeshComponent* Target, BuildingComposition Composition);


	/* 건물의 초기(최대) 층수 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default", meta = (ExposeOnSpawn = "true"))
		int32 InitialFloor = 5;

	/* 층 간 높이 */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		double FloorDistance;


	/* 최상단 천장에 대한 static mesh 변수 */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		UStaticMeshComponent* Building_Ceiling;
	/* 층 들에 대한 차일드 액터 컴퍼넌트 배열 */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		TArray<AActor*> Building_Floors;
	
	/* 게임진행중 현재 층 수에 대한 변수 */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		int32 CurrentFloor;

	///* 바닥/벽 에 대한 Geometry Actor */
	//UPROPERTY(EditDefaultsOnly)
	//	TSubclassOf<AActor> GC_Floor;
	//UPROPERTY(EditDefaultsOnly)
	//	TSubclassOf<AActor> GC_Wall01;
	//UPROPERTY(EditDefaultsOnly)
	//	TSubclassOf<AActor> GC_Wall02;
	//UPROPERTY(EditDefaultsOnly)
	//	TSubclassOf<AActor> GC_Wall03;
	//UPROPERTY(EditDefaultsOnly)
	//	TSubclassOf<AActor> GC_Wall04;

	UPROPERTY()
		TSubclassOf<ASingleBuildingFloor> SingleBuildingClass;

public:
	/* IMapCollapseInterface */
	//virtual void DoCollapse() override;
};
