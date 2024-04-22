// Fill out your copyright notice in the Description page of Project Settings.


#include "HexagonTile.h"

#include "Kismet/KismetMathLibrary.h"
#include "Skyscraper/MainGame/Map/Building/Building.h"

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

	// 붕괴 방향 설정
	CollapseDirectionAngle = FMath::RandRange(0, 5);		// 0',60',120',180',240',300' 로 붕괴되는 방향에 대한 Angle 설정

	// 건물 클래스 로드
	static ConstructorHelpers::FClassFinder<AActor> BuildingClassRef(TEXT("/Script/Engine.Blueprint'/Game/2019180031/MainGame/Map/Building/SingleBuildingFloor.SingleBuildingFloor_C'"));
	BuildingClass = BuildingClassRef.Class;
	
	
}

FVector AHexagonTile::CalculateRelativeLocation(int32 AngleCount, int32 Distance)
{
	// 주어진 각도와 거리(구역1~4) 에 따라 적합한 RelativeLocation을 반환하는 함수
	float TileDistance = offset * Distance;

	float sin = UKismetMathLibrary::DegSin(AngleCount * 60 + 30);
	float cos = UKismetMathLibrary::DegCos(AngleCount * 60 + 30);

	return FVector(TileDistance * sin, TileDistance * cos, 0.0f);
}

void AHexagonTile::InitialSettings()
{
	// 팀 리스폰 위치 빌딩 생성

	// 각 구역별 빌딩 및 부유타일 생성
	{
		SpawnBuildings(8, FName("Section1"), 3);
		SpawnBuildings(4, FName("Section2"), 5);
		SpawnBuildings(2, FName("Section3"), 7);
		SpawnBuildings(1, FName("MiddleTile"), 9);
	}

	

}

void AHexagonTile::SpawnBuildings(int32 SpawnCount, FName TileTag, int32 Floor)
{
	/*
	 SpawnCount - 설치될 건물의 갯수 / TileTag - 설치될 타일 섹션 (Section1~3) / Floor - 설치될 건물의 층 수
	 */
	TArray<UChildActorComponent*> SectionTiles;	// 특정 섹션의 타일들이 저장되는 배열
	TObjectPtr<UChildActorComponent> TargetTile; // 건물이 설치될 타일

	{ // 해당 섹션 타일 구하기
		for (const auto& pTile : Tiles)
		{
			// TileTag 태그를 가진 타일들을 추출한다.
			if(pTile && pTile->ComponentHasTag(TileTag))
			{
				SectionTiles.Add(pTile);
			}
		}
	}

	{ // 빌딩 배치하기
		int BuildingCount = 0;
		while(BuildingCount < SpawnCount)
		{
			// 건물이 생성 될 타일 구하기
			int index = FMath::RandRange(0, SectionTiles.Num() - 1);
			TargetTile = SectionTiles[index];
			// 해당 타일에 건물이 설치되지 않았다면, 건물을 생성하여 설치
			if(!Tile_Actor.Contains(TargetTile))
			{
				// 빌딩 생성 및 추가
				ABuilding* Building = GetWorld()->SpawnActorDeferred<ABuilding>(ABuilding::StaticClass(), FTransform(), this);
				if (Building)
				{
					Building->Initialize(Floor);
					Building->FinishSpawning(FTransform{FRotator{},TargetTile->GetRelativeLocation() });
					//Building->SetActorLocation();
				}
				Tile_Actor.Add(TargetTile, Building);

				// 해당 섹션 타일을 사용했으니 선택지에서 제거
				SectionTiles.Remove(TargetTile);

				++BuildingCount;
			}
		}
	}


	
}

void AHexagonTile::SpawnFloatingTiles(int32 SpawnCount, FName TileTag, FVector MovementOffset)
{
}



// Called when the game starts or when spawned
void AHexagonTile::BeginPlay()
{
	Super::BeginPlay();

	InitialSettings();
}

// Called every frame
void AHexagonTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

}

