// Fill out your copyright notice in the Description page of Project Settings.


#include "HexagonTile.h"

#include "SingleHexagonTile.h"
#include "Kismet/KismetMathLibrary.h"
#include "Skyscraper/MainGame/Map/Building/Building.h"
#include "Skyscraper/MainGame/Map/FloatingTile/FloatingTile.h"

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

	// 건물 클래스 로드
	static ConstructorHelpers::FClassFinder<AActor> BuildingClassRef(TEXT("/Script/Engine.Blueprint'/Game/2019180031/MainGame/Map/Building/SingleBuildingFloor.SingleBuildingFloor_C'"));
	BuildingClass = BuildingClassRef.Class;

	// 붕괴 타일 클래스 로드
	ConstructorHelpers::FClassFinder<AActor> GC_TileRef(TEXT("/Script/Engine.Blueprint'/Game/2019180031/MainGame/Map/HexagonTile/BP_GC_Tile.BP_GC_Tile_C'"));
	GC_Tile = GC_TileRef.Class;
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
	{
		// 붕괴 방향 설정 ( 0',60',120',180',240',300' )
		CollapseDirectionAngle = FMath::RandRange(0, 5);

		ATeamBuildings.Add(SpawnTeamBuilding(
			GetLineTileFromAngleAndDistance((CollapseDirectionAngle + 3) % 6, 3),
			3, FName("Section1"))) ;
		ATeamBuildings.Add(SpawnTeamBuilding(
			GetLineTileFromAngleAndDistance((CollapseDirectionAngle + 3) % 6, 1),
			7, FName("Section3")));
		ATeamBuildings.Add(SpawnTeamBuilding(
			GetLineTileFromAngleAndDistance(CollapseDirectionAngle, 1),
			7, FName("Section3")));
		
		BTeamBuildings.Add(SpawnTeamBuilding(
			GetLineTileFromAngleAndDistance(CollapseDirectionAngle, 3),
			3, FName("Section1")));
		
	}

	// 각 구역별 빌딩 생성
	{
		SpawnBuildings(6, FName("Section1"), 3);
		SpawnBuildings(4, FName("Section2"), 5);
		
		SpawnBuildings(1, FName("MiddleTile"), 9);
	}

	// 각 구역별 부유 타일 생성
	{
		SpawnFloatingTiles(4, FName("Section1"), FVector(0.0f, 0.0f, -2500.0f));
		SpawnFloatingTiles(2, FName("Section2"), FVector(0.0f, 0.0f, -4500.0f));
		SpawnFloatingTiles(1, FName("Section3"), FVector(0.0f, 0.0f, -6500.0f));
	}

}

UChildActorComponent* AHexagonTile::GetLineTileFromAngleAndDistance(int32 FindAngle, int32 FindDistance, FVector FindTileLocation)
{
	// (0, 0, 좌표) 입력시 해당 좌표의 타일 반환
	// (1, 3) 입력시 60도 방면의 Section1 타일 반환
		// 
	if (FindDistance != 0)
	{
		FindTileLocation = CalculateRelativeLocation(FindAngle, FindDistance);
	}

	for(UChildActorComponent* Tile : Tiles)
	{
		// 모든 타일 중 해당 타일과의 거리를 비교하여 찾기
		if(UKismetMathLibrary::Vector_DistanceSquared(Tile->GetRelativeLocation(), FindTileLocation) < 100.0f)
		{
			return Tile;
		}
	}

	return nullptr;
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
					Building->FinishSpawning(FTransform{FRotator{0.0f,120.0f* FMath::RandRange(0, 2),0.0f},TargetTile->GetRelativeLocation() * GetActorScale3D()});
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
	/*
	 SpawnCount - 설치될 부유타일 갯수 / TileTag - 설치될 타일 섹션 (Section1~3) / MovementOffset - 생성될 부유타일의 움직임 오프셋
	 */
	TArray<UChildActorComponent*> SectionTiles;	// 특정 섹션의 타일들이 저장되는 배열
	TObjectPtr<UChildActorComponent> TargetTile; // 건물이 설치될 타일

	{ // 해당 섹션 타일 구하기
		for (const auto& pTile : Tiles)
		{
			// TileTag 태그를 가진 타일들을 추출한다.
			if (pTile && pTile->ComponentHasTag(TileTag))
			{
				SectionTiles.Add(pTile);
			}
		}
	}

	{ // 부유 타일 배치하기
		int FloatingTileCount = 0;
		while (FloatingTileCount < SpawnCount)
		{
			// 부유타일이 생성 될 타일 구하기
			int index = FMath::RandRange(0, SectionTiles.Num() - 1);
			TargetTile = SectionTiles[index];
			// 해당 타일에 건물/부유타일이 설치되지 않았다면, 건물을 생성하여 설치
			if (!Tile_Actor.Contains(TargetTile))
			{
				// 부유타일 생성 및 추가
				AFloatingTile* FloatingTile = GetWorld()->SpawnActorDeferred<AFloatingTile>(AFloatingTile::StaticClass(), FTransform(), this);
				if (FloatingTile)
				{
					FloatingTile->Initialize(MovementOffset);
					FloatingTile->FinishSpawning(FTransform{ FRotator{},TargetTile->GetRelativeLocation() * GetActorScale3D() });
				}
				Tile_Actor.Add(TargetTile, FloatingTile);

				// 해당 섹션 타일을 사용했으니 선택지에서 제거
				SectionTiles.Remove(TargetTile);

				++FloatingTileCount;
			}
		}
	}
}

AActor* AHexagonTile::SpawnTeamBuilding(UChildActorComponent* TargetTile, int32 Floor, FName TileTag)
{
	if(!TargetTile->ComponentHasTag(TileTag))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s %d"), *TargetTile->GetName(),CollapseDirectionAngle);
		
	}
	{ // 빌딩 배치하기
		if (!Tile_Actor.Contains(TargetTile))
		{
			// 빌딩 생성 및 추가
			ABuilding* Building = GetWorld()->SpawnActorDeferred<ABuilding>(ABuilding::StaticClass(), FTransform(), this);
			if (Building)
			{
				Building->Initialize(Floor);
				Building->FinishSpawning(FTransform{ FRotator{0.0f,120.0f * FMath::RandRange(0, 2),0.0f},TargetTile->GetRelativeLocation() * GetActorScale3D() });
			}
			Tile_Actor.Add(TargetTile, Building);
			return Building;
		}
	}

	return nullptr;
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


void AHexagonTile::CollapseTilesAndActors(int CollapseLevel)
{
	float CollapseRemainDistance{};
	// CollapseLevel에 따라 파괴되지 않는 영역 길이 설정
	{
		if (CollapseLevel == 1) CollapseRemainDistance = 2.5f;
		else CollapseRemainDistance = 1.5f;
	}

	// 지형 파괴 후 남은 타일의 중앙 타일 구하기
	{
		FVector NewMiddleTileLocation = CurrentMiddleTile->GetRelativeLocation();
		NewMiddleTileLocation.X += (offset * UKismetMathLibrary::DegSin(CollapseDirectionAngle * 60 + 30));
		NewMiddleTileLocation.Y += (offset * UKismetMathLibrary::DegCos(CollapseDirectionAngle * 60 + 30));

		CurrentMiddleTile = GetLineTileFromAngleAndDistance(0, 0, NewMiddleTileLocation);
	}

	// 파괴 영역에 해당하는 육각타일 파괴 및 해당 육각타일 아래 건물 / 부유타일 삭제
	// 삭제 후 GeometryComponent에 해당하는 타일 생성
	{
		for (UChildActorComponent* Tile : Tiles)
		{
			float TileDistance = UKismetMathLibrary::Vector_Distance(Tile->GetRelativeLocation(), CurrentMiddleTile->GetRelativeLocation());
			FVector GeometrySpawnLocation = Tile->GetRelativeLocation();

			// 파괴 영역 체크
			if (TileDistance > offset * CollapseRemainDistance)
			{
				if (Tile_Actor.Contains(Tile))
				{
					AActor* TargetActor = *(Tile_Actor.Find(Tile));
					ICollapsible* Child_Actor = Cast<ICollapsible>(TargetActor);
					if (Child_Actor)
					{
						Child_Actor->DoCollapse();
						TargetActor->SetLifeSpan(20.0f);

					}
					Tile_Actor.Remove(Tile);
				}
				
				Tile->DestroyComponent();
				Tile = nullptr;

				// 타일 GeometryCollection 생성
				AActor* NewGCTileActor = GetWorld()->SpawnActor(GC_Tile);
				
				NewGCTileActor->SetActorLocation(GeometrySpawnLocation);
			}
		}
	}

	{ // 배열 내 Invalid 값 제거
		TArray<UChildActorComponent*> TempArray;
		for (UChildActorComponent* Tile : Tiles)
		{
			if (Tile)
			{
				TempArray.Add(Tile);
			}
		}
		Tiles.Empty();
		for (UChildActorComponent* TempTile : TempArray)
		{
			Tiles.Add(TempTile);
		}
	}

}