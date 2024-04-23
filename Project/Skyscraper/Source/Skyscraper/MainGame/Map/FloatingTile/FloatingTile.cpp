// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingTile.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
AFloatingTile::AFloatingTile()
{
 	// bCanEverTick
	PrimaryActorTick.bCanEverTick = true;

	// static mesh 에셋 로드
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TileAsset(TEXT("/Script/Engine.StaticMesh'/Game/2016180023/map/map_3_tile.map_3_tile'"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloatingTile"));
	SetRootComponent(StaticMesh);
	StaticMesh->SetStaticMesh(TileAsset.Object);

	
}

void AFloatingTile::Initialize(FVector GetMovementOffset)
{
	MovementOffset = GetMovementOffset;
}

void AFloatingTile::SetInitialSetting()
{
	// 초기값 설정
	Speed = UKismetMathLibrary::RandomFloatInRange(0.5, 0.7);

	SetActorLocation(GetActorLocation() + FVector(0.0f, 0.0f, -1000.0f));

	InitStartLocation = GetActorLocation();
	TargetLocation = InitEndLocation = GetActorLocation() + MovementOffset;
	MoveToEnd = true;
}

// Called when the game starts or when spawned
void AFloatingTile::BeginPlay()
{
	Super::BeginPlay();

	SetInitialSetting();
}

// Called every frame
void AFloatingTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 위치 interpolation
	FVector ResultLoc = UKismetMathLibrary::VInterpTo(
		GetActorLocation(),
		TargetLocation,
		DeltaTime,
		Speed
	);
	SetActorLocation(ResultLoc);

	// 도착 위치 계산 및 도착했을 경우 반대로 이동하도록
	float DistanceToTarget = (TargetLocation - GetActorLocation()).Length();

	if (DistanceToTarget < 50.0f)
	{
		if (MoveToEnd) TargetLocation = InitStartLocation;
		else TargetLocation = InitEndLocation;
		MoveToEnd = !MoveToEnd;
	}

}

