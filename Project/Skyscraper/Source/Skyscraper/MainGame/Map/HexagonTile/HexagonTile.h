// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HexagonTile.generated.h"

UCLASS()
class SKYSCRAPER_API AHexagonTile : public AActor
{
	GENERATED_BODY()
protected:
	/* 육각 타일 지름 길이 */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		double offset;

	/* 현재 중간 타일 static mesh component */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		TObjectPtr<UChildActorComponent> CurrentMiddleTile;

	/* 전체 육각 타일 배열 */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		TArray<UChildActorComponent*> Tiles;

	/* 육각타일과 그 아래 건물/부유타일에 대한 map */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		TMap<UStaticMeshComponent*, AActor*> Tile_Actor;

	/**/
	UPROPERTY(EditAnywhere)
		float CollapseDirectionAngle;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> BuildingBP;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> FloatingTileBP;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> GC_TileBP;
public:	
	// 생성자
	AHexagonTile();

	/* 생성자에서 타일들의 위치 계산해주는 함수 */
	UFUNCTION(BlueprintPure, Category = "Construct")
		FVector CalculateRelativeLocation(int32 AngleCount, int32 Distance);

	///* 건물 및 부유타일 생성 함수 */
	//UFUNCTION(BlueprintCallable, Category = "Init")
	//	void SpawnBuildingsAndFloatingTiles(int32 SpawnCount, FName TileTag, int32 Floor, int32 FloatingTileCount, FVector MovementOffset);

	///* 붕괴 1단계/2단계 함수 */
	//UFUNCTION(BlueprintCallable, Category = "Collapse")
	//	void CollapseLevel1And2(int CollapseLevel);

	///* 붕괴 3단계 함수 */
	//UFUNCTION(BlueprintCallable, Category = "Collapse")
	//	void CollapseLevel3();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
