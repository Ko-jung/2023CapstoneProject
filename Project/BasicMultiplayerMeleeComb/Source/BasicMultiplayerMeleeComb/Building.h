// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Building.generated.h"

UCLASS()
class BASICMULTIPLAYERMELEECOMB_API ABuilding : public AActor
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
	//UFUNCTION(BlueprintCallable)
	//	void CollapseBuilding(int32 CollapseStartFloor);

	/* 건물 붕괴 적용 함수 */
	//UFUNCTION(BlueprintCallable)
	//	void SwapStaticToGeometry(UStaticMeshComponent* Target, const UGeometryCollection* RestCollectionIn, FVector RelativeLocation);

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


};
