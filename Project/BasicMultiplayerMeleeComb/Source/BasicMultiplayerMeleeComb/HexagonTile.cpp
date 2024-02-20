// Fill out your copyright notice in the Description page of Project Settings.


#include "HexagonTile.h"

#include <functional>
#include <Kismet/KismetMathLibrary.h>
#include "Building.h"
#include "FloatingTile.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "GeometryCollection/GeometryCollectionObject.h"
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
		Tiles[0]->ComponentTags.Add(TEXT("MiddleTile"));

		CurrentMiddleTile = Tiles[0];
		SetRootComponent(Tiles[0]);
	}


	int tilecount = 1;
	for(int angle = 0; angle<6; ++angle)	// 각도 6부분 타일에 대해
	{	
		for (int distance = 1; distance < 4; ++distance)	// 중앙 타일로부터의 거리
		{
			FString tag = "Section" + FString::FromInt((distance-2)*-1+2);
			{//60도 방면 위치에 StaticMesh 추가
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
	static ConstructorHelpers::FObjectFinder<UBlueprint> GCTileItem(TEXT("/Script/Engine.Blueprint'/Game/2019180031/Blueprints/Map/Tile/Tile_Geometry/GC_Tile.GC_Tile'"));
	if (GCTileItem.Object)
	{
		GC_TileBP = (UClass*)GCTileItem.Object->GeneratedClass;
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
	SpawnBuildingsAndFloatingTiles(4, FName("Section2"), 7, 2, FVector(0.0f, 0.0f, -5000.0f));
	SpawnBuildingsAndFloatingTiles(2, FName("Section3"), 11, 1, FVector(0.0f, 0.0f, -7000.0f));
	SpawnBuildingsAndFloatingTiles(1, FName("MiddleTile"), 15, 0, FVector());
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
			int32 index = FMath::RandRange(0, SectionTiles.Num() - 1);
			TargetTile = SectionTiles[index];

			if(!UsedTile.Contains(TargetTile))
			{
				UsedTile.Add(TargetTile);
				SectionTiles.Remove(TargetTile);
				FTransform SpawnTransform;
				SpawnTransform.SetLocation(TargetTile->GetRelativeLocation());
				AActor* BuildingActor = GetWorld()->SpawnActor<AActor>(BuildingBP, SpawnTransform);
				(Cast<ABuilding>(BuildingActor))->SetFloorAndCreate(GetFloor);
				Tile_Actor.Add(TargetTile, BuildingActor);
			}
		}
	}

	{ // 부유타일 배치하기
		while (UsedTile.Num() < SpawnCount + FloatingTileCount)
		{
			int32 index = FMath::RandRange(0, SectionTiles.Num() - 1);
			TargetTile = SectionTiles[index];

			if (!UsedTile.Contains(TargetTile))
			{
				UsedTile.Add(TargetTile);
				SectionTiles.Remove(TargetTile);
				FTransform SpawnTransform;
				SpawnTransform.SetLocation(TargetTile->GetRelativeLocation());
				AActor* FloatingActor = GetWorld()->SpawnActor<AActor>(FloatingTileBP, SpawnTransform);
				(Cast<AFloatingTile>(FloatingActor))->SetInitalSetting(MovementOffset);

				Tile_Actor.Add(TargetTile, FloatingActor);
			}
		}
	}
}

void AHexagonTile::CollapseLevel1And2(int CollapseLevel)
{
	double CollapseValue{};
	if (CollapseLevel == 1) CollapseValue = 2.5f;
	else CollapseValue = 1.5f;

	{ // 중간 타일 설정
		TArray<UStaticMeshComponent*> MiddleCandidate;

		for(UStaticMeshComponent* tile : Tiles )
		{
			if(UKismetMathLibrary::InRange_FloatFloat(
				(tile->GetRelativeLocation() - CurrentMiddleTile->GetRelativeLocation()).Length(),
				offset * 0.5,
				offset * 1.5))
			{
				MiddleCandidate.Add(tile);
			}
		}
		int32 newIndex = UKismetMathLibrary::RandomIntegerInRange(0, MiddleCandidate.Num() - 1);
		CurrentMiddleTile = MiddleCandidate[newIndex];
	}

	{ // 육각타일 파괴 및 해당 육각타일 아래 건물/부유타일 파괴
		for(int32 i = 0; i<Tiles.Num(); ++i)
		{
			
			FVector SpawnLoc = Tiles[i]->GetRelativeLocation();
			if ((Tiles[i]->GetRelativeLocation() - CurrentMiddleTile->GetRelativeLocation()).Length() > offset * CollapseValue)
			{
				if(Tile_Actor.Contains(Tiles[i]))
				{
					AActor* targetActor = *(Tile_Actor.Find(Tiles[i]));
					IMapCollapseInterface* Child_Actor = Cast<IMapCollapseInterface>(targetActor);
					if(Child_Actor)
					{
						Child_Actor->DoCollapse();
						targetActor->SetLifeSpan(10.0f);
					}
				}
				Tile_Actor.Remove(Tiles[i]);
				Tiles[i]->DestroyComponent();
				Tiles[i] = nullptr;
				AActor* BrokenTile = GetWorld()->SpawnActor<AActor>(GC_TileBP, SpawnLoc,FRotator());
				BrokenTile->SetLifeSpan(10.0f);
				//SpawnGCComp(SpawnLoc);
			}
		}
		
	}

	{// 배열 Invalid 값 제거
		TArray<UStaticMeshComponent*> tempArray;
		for(int i=0; i<Tiles.Num(); ++i)
		{
			if(Tiles[i])
			{
				tempArray.Add(Tiles[i]);
			}
		}
		Tiles.Empty();
		for(int i = 0; i<tempArray.Num();++i)
		{
			Tiles.Add(tempArray[i]);
		}
		
	}
	
}

void AHexagonTile::CollapseLevel3()
{
	int index = UKismetMathLibrary::RandomIntegerInRange(0, Tiles.Num() - 1);
	FVector SpawnLoc = Tiles[index]->GetRelativeLocation();
	if (Tile_Actor.Contains(Tiles[index]))
	{
		AActor* targetActor = *(Tile_Actor.Find(Tiles[index]));
		IMapCollapseInterface* Child_Actor = Cast<IMapCollapseInterface>(targetActor);
		if (Child_Actor)
		{
			Child_Actor->DoCollapse();
			targetActor->SetLifeSpan(7.0f);
		}
	}
	Tile_Actor.Remove(Tiles[index]);
	Tiles[index]->DestroyComponent();
	Tiles[index] = nullptr;
	AActor* BrokenTile = GetWorld()->SpawnActor<AActor>(GC_TileBP, SpawnLoc, FRotator());
	BrokenTile->SetLifeSpan(7.0f);


	{// 배열 Invalid 값 제거
		TArray<UStaticMeshComponent*> tempArray;
		for (int i = 0; i < Tiles.Num(); ++i)
		{
			if (Tiles[i])
			{
				tempArray.Add(Tiles[i]);
			}
		}
		Tiles.Empty();
		for (int i = 0; i < tempArray.Num(); ++i)
		{
			Tiles.Add(tempArray[i]);
		}

	}
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

	static bool Check = false;
	
	if (GetWorld()->GetFirstPlayerController()->WasInputKeyJustPressed(EKeys::I))
	{
		if(!Check)
		{
			CollapseLevel1And2(1);
			Check = true;
		}else
		{
			CollapseLevel1And2(2);
			Check = false;
		}
		
	}

	if (GetWorld()->GetFirstPlayerController()->WasInputKeyJustPressed(EKeys::O))
	{
		CollapseLevel3();

	}
}

