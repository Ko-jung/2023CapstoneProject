// Fill out your copyright notice in the Description page of Project Settings.


#include "HexagonTile.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
AHexagonTile::AHexagonTile()
{
	// bCanEverTick
	PrimaryActorTick.bCanEverTick = false;

	// 변수값 초기화
	offset = 3465.0f;

	// 타일 static mesh 로드
	static ConstructorHelpers::FClassFinder<AActor> SingleHexagonTileClass(TEXT("/Script/Engine.Blueprint'/Game/2019180031/MainGame/Map/HexagonTile/SingleHexagonTile.SingleHexagonTile_C'"));
	if (!(SingleHexagonTileClass.Succeeded())) return;

	UClass* TileClass = SingleHexagonTileClass.Class;

	for (int i = 0; i < 37; ++i)
		Tiles.AddDefaulted();

	{	//중앙 육각 타일 배치
		Tiles[0] = CreateDefaultSubobject<UChildActorComponent>(TEXT("MiddleTile"));
		Tiles[0]->SetChildActorClass(TileClass);
		Tiles[0]->ComponentTags.Add(TEXT("MiddleTile"));
		CurrentMiddleTile = Tiles[0];
		SetRootComponent(Tiles[0]);
	}


	int tilecount = 1;
	for (int angle = 0; angle < 6; ++angle)	// 각도 6부분 타일에 대해
	{
		for (int distance = 1; distance < 4; ++distance)	// 중앙 타일로부터의 거리
		{
			FString tag = "Section" + FString::FromInt((distance - 2) * -1 + 2);
			{//60도 방면 위치에 StaticMesh 추가
				FString name = tag + "_" + FString::FromInt(tilecount);
				Tiles[tilecount] = CreateDefaultSubobject<UChildActorComponent>(FName(name));
				Tiles[tilecount]->SetChildActorClass(TileClass);
				Tiles[tilecount]->SetupAttachment(Tiles[0]);
				Tiles[tilecount]->SetRelativeLocation(CalculateRelativeLocation(angle, distance));
				Tiles[tilecount]->ComponentTags.Add(FName(tag));
				++tilecount;
			}

			// 60도 방면 사이 위치에 Static Mesh 추가
			for (int midCount = 2; midCount < distance + 1; ++midCount)
			{
				FVector firstLoc = CalculateRelativeLocation(angle, distance);
				FVector SecondLoc = CalculateRelativeLocation(angle + 1, distance);

				FVector RelatLoc = ((firstLoc - SecondLoc) / (float)distance) * (midCount - 1) + SecondLoc;
				FString name = tag + "_" + FString::FromInt(tilecount);
				Tiles[tilecount] = CreateDefaultSubobject<UChildActorComponent>(FName(name));
				Tiles[tilecount]->SetChildActorClass(TileClass);
				Tiles[tilecount]->SetupAttachment(Tiles[0]);
				Tiles[tilecount]->SetRelativeLocation(RelatLoc);
				Tiles[tilecount]->ComponentTags.Add(FName(tag));
				++tilecount;

			}

		}

	}

	/*static ConstructorHelpers::FObjectFinder<UBlueprint> BuildingItem(TEXT("/Script/Engine.Blueprint'/Game/2019180031/Blueprints/Map/Building/CodeBuilding.CodeBuilding'"));
	if (BuildingItem.Object)
	{
		BuildingBP = (UClass*)BuildingItem.Object->GeneratedClass;
	}
	static ConstructorHelpers::FObjectFinder<UBlueprint> FloatingTileItem(TEXT("/Script/Engine.Blueprint'/Game/2019180031/Blueprints/Map/FloatingTile/CodeFloatingTile.CodeFloatingTile'"));
	if (FloatingTileItem.Object)
	{
		FloatingTileBP = (UClass*)FloatingTileItem.Object->GeneratedClass;
	}
	static ConstructorHelpers::FObjectFinder<UBlueprint> GCTileItem(TEXT("/Script/Engine.Blueprint'/Game/2019180031/Blueprints/Map/Tile/Tile_Geometry/GC_Tile.GC_Tile'"));
	if (GCTileItem.Object)
	{
		GC_TileBP = (UClass*)GCTileItem.Object->GeneratedClass;
	}*/
}

FVector AHexagonTile::CalculateRelativeLocation(int32 AngleCount, int32 Distance)
{
	// 주어진 각도와 거리(구역1~4) 에 따라 적합한 RelativeLocation을 반환하는 함수
	float TileDistance = offset * Distance;

	float sin = UKismetMathLibrary::DegSin(AngleCount * 60 + 30);
	float cos = UKismetMathLibrary::DegCos(AngleCount * 60 + 30);

	return FVector(TileDistance * sin, TileDistance * cos, 0.0f);
}

// Called when the game starts or when spawned
void AHexagonTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHexagonTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

