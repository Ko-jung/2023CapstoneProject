// Fill out your copyright notice in the Description page of Project Settings.


#include "HexagonTile.h"
#include <Kismet/KismetMathLibrary.h>

#include "Building.h"
#include "Kismet/KismetArrayLibrary.h"


// Sets default values
AHexagonTile::AHexagonTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	offset = 3030.0f;

	// 타일 static mesh와 material 로드
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TileAsset(TEXT("/Script/Engine.StaticMesh'/Game/2016180023/map_2/map_2_tile_00.map_2_tile_00'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> TileMaterial(TEXT("/Script/Engine.Material'/Game/2019180031/Material/M_Test.M_Test'"));


	if(!(TileAsset.Succeeded()&&TileMaterial.Succeeded())) return;

	for (int i = 0; i < 37; ++i)
		Tiles.AddDefaulted();

	{	//중앙 육각 타일 배치
		Tiles[0] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MiddleTile"));
		Tiles[0]->SetStaticMesh(TileAsset.Object);
		Tiles[0]->SetMaterial(0, TileMaterial.Object);
		Tiles[0]->ComponentTags.Add(TEXT("Middle"));

		CurrentMiddleTile = Tiles[0];
		SetRootComponent(Tiles[0]);
	}


	int tilecount = 1;
	for(int angle = 0; angle<6; ++angle)	// 각도 6부분 타일에 대해
	{	
		for (int distance = 1; distance < 4; ++distance)	// 중앙 타일로부터의 거리
		{
			{//60도 방면 위치에 StaticMesh 추가
				FString tag = "Section" + FString::FromInt(abs(distance - 2));
				FString name = tag + "_" + FString::FromInt(tilecount);
				Tiles[tilecount] = CreateDefaultSubobject<UStaticMeshComponent>(FName(name));
				Tiles[tilecount]->SetStaticMesh(TileAsset.Object);
				Tiles[tilecount]->SetMaterial(0, TileMaterial.Object);
				Tiles[tilecount]->SetupAttachment(Tiles[0]);
				Tiles[tilecount]->SetRelativeLocation(CalculateRelativeLocation(angle, distance));
				Tiles[tilecount]->ComponentTags.Add(FName(tag));
				++tilecount;
			}

			for(int midCount = 2; midCount<distance+1; ++midCount)
			{
				FVector firstLoc = CalculateRelativeLocation(angle, distance);
				FVector SecondLoc = CalculateRelativeLocation(angle+1, distance);

				FVector RelatLoc = ((firstLoc - SecondLoc) / (float)distance) * (midCount - 1) + SecondLoc;
				UE_LOG(LogTemp, Warning, TEXT("%f , %f, %f"),RelatLoc.X, RelatLoc.Y, RelatLoc.Z);
				FString tag = "Section" + FString::FromInt(abs(distance-2));
				FString name = tag + "_" + FString::FromInt(tilecount);
				Tiles[tilecount] = CreateDefaultSubobject<UStaticMeshComponent>(FName(name));
				Tiles[tilecount]->SetStaticMesh(TileAsset.Object);
				Tiles[tilecount]->SetMaterial(0, TileMaterial.Object);
				Tiles[tilecount]->SetupAttachment(Tiles[0]);
				Tiles[tilecount]->SetRelativeLocation(RelatLoc);
				Tiles[tilecount]->ComponentTags.Add(FName(tag));
				++tilecount;
				
			}

		}
		
	}
	
	static ConstructorHelpers::FObjectFinder<UBlueprint> BuildingItem(TEXT("/Script/Engine.Blueprint'/Game/2019180031/Blueprints/Map/Building/CodeBuilding.CodeBuilding'"));
	if(BuildingItem.Object)
	{
		BuildingBP = (UClass*)BuildingItem.Object->GeneratedClass;
	}
	static ConstructorHelpers::FObjectFinder<UBlueprint> FloatingTileItem(TEXT("/Script/Engine.Blueprint'/Game/2019180031/Blueprints/Map/FloatingTile/CodeFloatingTile.CodeFloatingTile'"));
	if (FloatingTileItem.Object)
	{
		FloatingTileBP = (UClass*)FloatingTileItem.Object->GeneratedClass;
	}
}

FVector AHexagonTile::CalculateRelativeLocation(int32 AngleCount, int32 Distance)
{
	float TileDistance = offset * Distance;

	float sin = UKismetMathLibrary::DegSin(AngleCount * 60 + 30);
	float cos = UKismetMathLibrary::DegCos(AngleCount * 60 + 30);
	
	return FVector(TileDistance * sin, TileDistance * cos, 0.0f);
}

void AHexagonTile::InitialSettiongs()
{
	SpawnBuildingsAndFloatingTiles(8, FName("Section1"), 3, 4, FVector(0.0f, 0.0f, -3000.0f));
}

void AHexagonTile::SpawnBuildingsAndFloatingTiles(int32 SpawnCount, FName TileTag, int32 GetFloor, int32 FloatingTileCount, FVector MovementOffset)
{
	/*
	 SpawnCount - 설치될 건물의 갯수 / TileTag - 설치될 타일 섹션 (Section1~3) / Floor - 설치될 건물의 층 수 / FloatingTileCount - 설치될 부유타일의 갯수 / MovementOffset - 부유타일의 이동 오프셋
	 */
	TArray<UStaticMeshComponent*> UsedTile;	// 건물이 생성된 타일을 저장하는 배열
	TArray<UStaticMeshComponent*> SectionTiles;	// 특정 섹션의 타일들이 저장되는 배열
	TObjectPtr<UStaticMeshComponent> TargetTile; // 건물이 설치될 타일

	{ // 섹션 타일 구하기
		for (auto pTile = Tiles.begin(); pTile != Tiles.end(); ++pTile)
		{
			if(*pTile)
			{
				if((*pTile)->ComponentHasTag(TileTag))
				{
					SectionTiles.Add(*pTile);
				}
			}
		}
	}

	{ // 건물 배치하기
		while(UsedTile.Num()<SpawnCount)
		{
			int32 index = FMath::RandRange(0, Tiles.Num() - 1);
			TargetTile = Tiles[index];

			if(!UsedTile.Contains(TargetTile))
			{
				UsedTile.Add(TargetTile);
				SectionTiles.Remove(TargetTile);
				FTransform SpawnTransform;
				SpawnTransform.SetLocation(TargetTile->GetRelativeLocation());
				AActor* test = GetWorld()->SpawnActor<AActor>(BuildingBP, SpawnTransform);

				Tile_Actor.Add(TargetTile, test);
			}
		}
	}

	//TODO: 부유타일 배치 진행 및 선행 건물의 Expose 설정
}

// Called when the game starts or when spawned
void AHexagonTile::BeginPlay()
{
	Super::BeginPlay();

	InitialSettiongs();
}


// Called every frame
void AHexagonTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

