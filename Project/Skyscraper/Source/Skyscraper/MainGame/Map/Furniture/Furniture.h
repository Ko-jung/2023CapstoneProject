// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "Skyscraper/MainGame/Interface/Destructible/Collapsible.h"
#include "Furniture.generated.h"

class UBoxComponent;
class USpotLightComponent;
class UHierarchicalInstancedStaticMeshComponent;
class ADesk;
class ABuilding;

UCLASS()
class SKYSCRAPER_API AFurniture : public AActor, public ICollapsible
{
	GENERATED_BODY()
	
public:	
	AFurniture();

	virtual void DoCollapse() override;

	UFUNCTION(BlueprintCallable)
	bool CollapseByTileCollapseItem(ASkyscraperCharacter* TargetCharacter);

	UFUNCTION()
		void SetBuildingFloorInfo(ABuilding* GetBuilding, int Floor);

protected:
	bool IsCharacterInHere(ASkyscraperCharacter* TargetCharacter) const;

	void SettingSpotLight();
	UFUNCTION()
	void BoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void BoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void FindStartOverlapActors();

	UFUNCTION()
		void ChangeHISMToPhysicsSM(UHierarchicalInstancedStaticMeshComponent* HISM, int Index = 0);
	UFUNCTION()
		void AllHISMToPhysicsSM(UHierarchicalInstancedStaticMeshComponent* HISM);

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:

public:
protected:
	// =============== 컴퍼넌트 ===============
	UPROPERTY(BlueprintReadWrite)
		TObjectPtr<UHierarchicalInstancedStaticMeshComponent> HISM_Table;
	UPROPERTY(BlueprintReadWrite)
		TObjectPtr<UHierarchicalInstancedStaticMeshComponent> HISM_Sofa;
	UPROPERTY(BlueprintReadWrite)
		TObjectPtr<UHierarchicalInstancedStaticMeshComponent> HISM_Flowerpot;

	UPROPERTY(BlueprintReadWrite)
		TArray<TObjectPtr<USpotLightComponent>> SpotLights;

	UPROPERTY(BlueprintReadWrite)
		TObjectPtr<UBoxComponent> BoxCollision;

	UPROPERTY(BlueprintReadWrite)
		TArray<TObjectPtr<ADesk>> DeskActors;
	// =======================================

	UPROPERTY()
		TArray<TObjectPtr<AActor>> InsidePlayers;

	UPROPERTY()
		FTimerHandle StartOverlapTimerHandle;

	UPROPERTY(BlueprintReadWrite)
		TArray<TObjectPtr<UStaticMeshComponent>> DummyStaticMeshComp;
	UPROPERTY()
		TArray<TObjectPtr<UStaticMeshComponent>> PhysicsFurniture;

	// 해당 가구 액터가 어떤 빌딩의 몇층의 액터인지에 대한 정보
	UPROPERTY()
		ABuilding* OwnerBuilding;
	int Floor;

	// ==== Furniture Dissolve를 위한 변수들
	UPROPERTY()
		FTimerHandle FurnitureDissolveTimerHandle;
	UPROPERTY()
		TMap<TObjectPtr<UStaticMeshComponent>, float> FurnitureSimulateTime;
	UPROPERTY()
		float FurnitureDissolveTime;
	UPROPERTY()
		TArray<TObjectPtr<UMaterial>> FurnitureDissolveMaterial;
	

private:

};
