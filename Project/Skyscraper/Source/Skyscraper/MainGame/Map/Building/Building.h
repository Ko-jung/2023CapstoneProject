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
	///* �ǹ� �ر� ���� �� ȣ�� �Լ� */
	//UFUNCTION(BlueprintCallable)
	//	void CollapseBuilding(int32 CollapseStartFloor);

	///* �ǹ� �ر� ���� �Լ� */
	////UFUNCTION(BlueprintCallable)
	//void SwapStaticToGeometry(UStaticMeshComponent* Target, BuildingComposition Composition);


	/* �ǹ��� �ʱ�(�ִ�) ���� */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default", meta = (ExposeOnSpawn = "true"))
		int32 InitialFloor = 5;

	/* �� �� ���� */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		double FloorDistance;


	/* �ֻ�� õ�忡 ���� static mesh ���� */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		UStaticMeshComponent* Building_Ceiling;
	/* �� �鿡 ���� ���ϵ� ���� ���۳�Ʈ �迭 */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		TArray<AActor*> Building_Floors;
	
	/* ���������� ���� �� ���� ���� ���� */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		int32 CurrentFloor;

	///* �ٴ�/�� �� ���� Geometry Actor */
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
