// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingTile.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
AFloatingTile::AFloatingTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TileAsset(TEXT("/Script/Engine.StaticMesh'/Game/2016180023/map_2/map_2_tile_00.map_2_tile_00'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> TileMaterial(TEXT("/Script/Engine.Material'/Engine/EngineDebugMaterials/MAT_LevelColorationLitLightmapUV.MAT_LevelColorationLitLightmapUV'"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloatingTile"));
	SetRootComponent(StaticMesh);
	StaticMesh->SetStaticMesh(TileAsset.Object);
	StaticMesh->SetMaterial(0,TileMaterial.Object);


	MovementOffset = FVector(0.0f, 0.0f, -3000.0f);
}

// Called when the game starts or when spawned
void AFloatingTile::BeginPlay()
{
	Super::BeginPlay();

	Speed = UKismetMathLibrary::RandomFloatInRange(0.5, 0.7);
	SetActorLocation(GetActorLocation() + FVector(0.0f, 0.0f, -200.0f));

	InitStartLocation = GetActorLocation();
	TargetLocation = InitEndLocation = GetActorLocation() + MovementOffset;
	MoveToEnd = true;
}

// Called every frame
void AFloatingTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector ResultLoc = UKismetMathLibrary::VInterpTo(
		GetActorLocation(),
		TargetLocation,
		DeltaTime,
		Speed
	);

	SetActorLocation(ResultLoc);

	float DistanceToTarget = (TargetLocation - GetActorLocation()).Length();

	if(DistanceToTarget<50.0f)
	{
		if (MoveToEnd) TargetLocation = InitStartLocation;
		else TargetLocation = InitEndLocation;
		MoveToEnd = !MoveToEnd;
	}
}

