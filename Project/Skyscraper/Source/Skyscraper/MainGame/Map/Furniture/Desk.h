// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Desk.generated.h"

class UHierarchicalInstancedStaticMeshComponent;

UCLASS()
class SKYSCRAPER_API ADesk : public AActor
{
	GENERATED_BODY()
public:
	ADesk();


protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:

public:
	UPROPERTY(BlueprintReadWrite)
		TObjectPtr<UHierarchicalInstancedStaticMeshComponent> HISM_Chair;
	UPROPERTY(BlueprintReadWrite)
		TObjectPtr<UHierarchicalInstancedStaticMeshComponent> HISM_Partition;
	UPROPERTY(BlueprintReadWrite)
		TObjectPtr<UHierarchicalInstancedStaticMeshComponent> HISM_Monitor;
	UPROPERTY(BlueprintReadWrite)
		TObjectPtr<UHierarchicalInstancedStaticMeshComponent>
			HISM_Desk;
	UPROPERTY(BlueprintReadWrite)
		TObjectPtr<UHierarchicalInstancedStaticMeshComponent> HISM_Desktop;

protected:
private:

};
