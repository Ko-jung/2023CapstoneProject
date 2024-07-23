// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingTile.h"

#include "Animation/AnimPhysicsSolver.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "GeometryCollection/GeometryCollectionObject.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AFloatingTile::AFloatingTile()
{
 	// bCanEverTick
	PrimaryActorTick.bCanEverTick = true;

	// static mesh 에셋 로드
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TileAsset(TEXT("/Script/Engine.StaticMesh'/Game/2016180023/map/map_refine/tile_float.tile_float'"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloatingTile"));
	SetRootComponent(StaticMesh);
	StaticMesh->SetStaticMesh(TileAsset.Object);

	ConstructorHelpers::FClassFinder<AActor> GC_TileRef(TEXT("/Script/Engine.Blueprint'/Game/2019180031/MainGame/Map/FlotingTile/BP_GC_Floatingtile.BP_GC_Floatingtile_C'"));
	GC_Tile = GC_TileRef.Class;

	IsInitProperty = false;
}

void AFloatingTile::Initialize(FVector GetMovementOffset)
{
	MovementOffset = GetMovementOffset;
}

void AFloatingTile::InitializeProperty(double speed, float moveTime, float waitTime)
{
	Speed = speed;

	MoveTime = moveTime;
	WaitTime = waitTime;
	IsInitProperty = true;
}

void AFloatingTile::SetInitialSetting()
{
	if (!IsInitProperty)
	{
		// 초기값 설정
		Speed = UKismetMathLibrary::RandomFloatInRange(0.5, 0.7);

		MoveTime = UKismetMathLibrary::RandomFloatInRange(4.0, 7.0);
		WaitTime = UKismetMathLibrary::RandomFloatInRange(1.0, 2.0);
	}

	CurrentTime = 0.0f;

	SetActorLocation(GetActorLocation() + FVector(0.0f, 0.0f, -1000.0f));

	InitStartLocation = GetActorLocation();
	InitEndLocation = GetActorLocation() + MovementOffset;
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
	FVector ResultLoc{};

	CurrentTime += DeltaTime;
	
	// 위치 interpolation
	if(MoveToEnd)
	{
		// 위치 interpolation
		ResultLoc = FMath::Lerp(
			InitStartLocation,
			InitEndLocation,
			FMath::Min(1.0f, CurrentTime / MoveTime)
		);
	}
	else
	{
		
		ResultLoc = FMath::Lerp(
			InitEndLocation,
			InitStartLocation,
			FMath::Min(1.0f, CurrentTime / MoveTime)
		);
	}
	
	SetActorLocation(ResultLoc);

	if (CurrentTime >= MoveTime + WaitTime)
	{
		MoveToEnd = !MoveToEnd;
		CurrentTime = 0.0f;
	}

}

void AFloatingTile::DoCollapse()
{
	// 1. tick 이벤트 끄기
	SetActorTickEnabled(false);

	// 2. 기존 타일 StaticMesh 없애기
	StaticMesh->SetHiddenInGame(true);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 3. GCComp 액터 생성
	AActor* NewGCTileActor = GetWorld()->SpawnActor(GC_Tile);
	NewGCTileActor->SetActorLocation(GetActorLocation());

	
	
	
}

