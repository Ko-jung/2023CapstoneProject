// Fill out your copyright notice in the Description page of Project Settings.


#include "Furniture.h"

// Sets default values
AFurniture::AFurniture()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AFurniture::BeginPlay()
{
	Super::BeginPlay();

	GetComponents<UStaticMeshComponent>(FurnitureObjects);

	UE_LOG(LogTemp, Warning, TEXT("가구 갯수: %d"), FurnitureObjects.Num());
}

// Called every frame
void AFurniture::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

