// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HexagonTile.generated.h"

class ABuilding;

UCLASS()
class SKYSCRAPER_API AHexagonTile : public AActor
{
	GENERATED_BODY()
protected:
	/* ���� Ÿ�� ���� ���� */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		double offset;

	/* ���� �߰� Ÿ�� static mesh component */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		TObjectPtr<UChildActorComponent> CurrentMiddleTile;

	/* ��ü ���� Ÿ�� �迭 */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		TArray<UChildActorComponent*> Tiles;

	/* ����Ÿ�ϰ� �� �Ʒ� �ǹ�/����Ÿ�Ͽ� ���� map */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		TMap<UChildActorComponent*, AActor*> Tile_Actor;

	/**/
	UPROPERTY(EditAnywhere)
		int CollapseDirectionAngle;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> BuildingClass;

public:	
	// ������
	AHexagonTile();

	/* �����ڿ��� Ÿ�ϵ��� ��ġ ������ִ� �Լ� */
	UFUNCTION(BlueprintPure, Category = "Construct")
		FVector CalculateRelativeLocation(int32 AngleCount, int32 Distance);


	


	///* �ر� 1�ܰ�/2�ܰ� �Լ� */
	//UFUNCTION(BlueprintCallable, Category = "Collapse")
	//	void CollapseLevel1And2(int CollapseLevel);

	///* �ر� 3�ܰ� �Լ� */
	//UFUNCTION(BlueprintCallable, Category = "Collapse")
	//	void CollapseLevel3();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// BeginPlay�� ������ �Լ�
	void InitialSettings();

	///* �ǹ� �� ����Ÿ�� ���� �Լ� */
	UFUNCTION(BlueprintCallable, Category = "Init")
		void SpawnBuildings(int32 SpawnCount, FName TileTag, int32 Floor);
	UFUNCTION(BlueprintCallable, Category = "Init")
		void SpawnFloatingTiles(int32 SpawnCount, FName TileTag, FVector MovementOffset);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
