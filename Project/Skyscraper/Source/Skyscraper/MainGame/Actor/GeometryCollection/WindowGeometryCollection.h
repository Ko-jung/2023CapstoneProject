// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "GeometryCollection/GeometryCollectionComponent.h"

#include "WindowGeometryCollection.generated.h"

UCLASS()
class SKYSCRAPER_API AWindowGeometryCollection : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWindowGeometryCollection();

	void Init(uint8 WindowNum);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetWindowObject(uint8 WindowNum);
	void AddForce(FVector Direction);

private:
	UPROPERTY(EditAnywhere)
	UGeometryCollectionComponent* GCWindow;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* MaterialInterface;

	UPROPERTY()
	 TArray<UObject*> GC_WindowObject;
};
