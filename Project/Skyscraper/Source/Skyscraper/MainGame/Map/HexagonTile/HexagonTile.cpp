// Fill out your copyright notice in the Description page of Project Settings.


#include "HexagonTile.h"

#include "SingleHexagonTile.h"
#include "Kismet/KismetMathLibrary.h"
#include "Skyscraper/MainGame/Map/Building/Building.h"
#include "Skyscraper/MainGame/Map/FloatingTile/FloatingTile.h"

#include "Kismet/GameplayStatics.h"
#include "Skyscraper/Enum/ETileImageType.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "Skyscraper/MainGame/Core/SkyscraperPlayerController.h"
#include "Skyscraper/MainGame/Widget/MiniMap/MiniMapWidget.h"
#include "Skyscraper/Network/MainGameMode.h"

#include "Skyscraper/MainGame/Actor/LootingItem/LootingItemActor.h"

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

	TileDropLevel = 0;

	ATeamBuildings.Init(nullptr, 2);
	BTeamBuildings.Init(nullptr, 2);
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
	UE_LOG(LogClass, Warning, TEXT("AHexagonTile::InitialSettings()"));
	// 팀 리스폰 위치 빌딩 생성
	{
		// 붕괴 방향 설정 ( 0',60',120',180',240',300' )
		CollapseDirectionAngle = FMath::RandRange(0, 5);

		ATeamBuildings.Add(SpawnTeamBuilding(
			GetLineTileFromAngleAndDistance((CollapseDirectionAngle + 3) % 6, 3),
			3, FName("Section1")));
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

	for (UChildActorComponent* Tile : Tiles)
	{
		// 모든 타일 중 해당 타일과의 거리를 비교하여 찾기
		if (UKismetMathLibrary::Vector_DistanceSquared(Tile->GetRelativeLocation(), FindTileLocation) < 100.0f)
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
			if (pTile && pTile->ComponentHasTag(TileTag))
			{
				SectionTiles.Add(pTile);
			}
		}
	}

	{ // 빌딩 배치하기
		int BuildingCount = 0;
		while (BuildingCount < SpawnCount)
		{
			// 건물이 생성 될 타일 구하기
			int index = FMath::RandRange(0, SectionTiles.Num() - 1);
			TargetTile = SectionTiles[index];
			// 해당 타일에 건물이 설치되지 않았다면, 건물을 생성하여 설치
			if (!Tile_Actor.Contains(TargetTile))
			{
				// 빌딩 생성 및 추가
				ABuilding* Building = GetWorld()->SpawnActorDeferred<ABuilding>(ABuilding::StaticClass(), FTransform(), this);
				if (Building)
				{
					Building->Initialize(Floor);
					Building->FinishSpawning(FTransform{ FRotator{0.0f,120.0f * FMath::RandRange(0, 2),0.0f},TargetTile->GetRelativeLocation() * GetActorScale3D() });
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
	if (!TargetTile->ComponentHasTag(TileTag))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s %d"), *TargetTile->GetName(), CollapseDirectionAngle);

	}
	{ // 빌딩 배치하기
		if (!Tile_Actor.Contains(TargetTile))
		{
			// 빌딩 생성 및 추가
			ABuilding* Building = GetWorld()->SpawnActorDeferred<ABuilding>(ABuilding::StaticClass(), FTransform(), this);
			if (Building)
			{
				Building->Initialize(Floor);
				Building->FinishSpawning(FTransform{ FRotator{0.0f,120.0f * (Floor % 3),0.0f},TargetTile->GetRelativeLocation() * GetActorScale3D() });
				//Building->SetActorLabel(FString(L"SpawnBuilding"));
			}
			else
			{
				UE_LOG(LogClass, Warning, TEXT("SpawnBuilding Is NULLPTR!"));
			}
			Tile_Actor.Add(TargetTile, Building);
			return Building;
		}
		else
		{
			UE_LOG(LogClass, Warning, TEXT("Building is Already Exist!"));
		}
	}

	return nullptr;
}




// Called when the game starts or when spawned
void AHexagonTile::BeginPlay()
{
	Super::BeginPlay();

	// Move to Init()
	//InitialSettings();

	ItemMap.Reserve(10);
	ItemSerial = 0;
}

// Called every frame
void AHexagonTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

void AHexagonTile::InitialSettings(BYTE* BuildingInfo, uint8 Size)
{
	memcpy(BuildInfo, BuildingInfo, sizeof(BuildInfo));

	for (int i = 0; i < Size; i++)
	{
		if (!Tiles[i]) continue;

		int Floor;
		float MoveZOffset;
		int Distance;
		FName Name;

		if (Tiles[i]->ComponentHasTag("Section3"))
		{
			Name = FName("Section3");
			Floor = 7;
			MoveZOffset = -6500.0f;
			Distance = 1;
		}
		else if (Tiles[i]->ComponentHasTag("Section2"))
		{
			Name = FName("Section2");
			Floor = 5;
			MoveZOffset = -4500.0f;
			Distance = 2;
		}
		else if (Tiles[i]->ComponentHasTag("Section1"))
		{
			Name = FName("Section1");
			Floor = 3;
			MoveZOffset = -2500.0f;
			Distance = 3;
		}
		else
		{
			Name = FName("MiddleTile");
			Floor = 9;
			MoveZOffset = -.0f;
			Distance = 0;
		}


		switch (BuildInfo[i])
		{
		case (BYTE)ETILETYPE::BUILDING:	// BUILDING
		{
			// 빌딩 생성 및 추가
			ABuilding* Building = GetWorld()->SpawnActorDeferred<ABuilding>(ABuilding::StaticClass(), FTransform(), this);
			if (Building)
			{
				Building->Initialize(Floor);
				Building->FinishSpawning(FTransform{ FRotator{0.0f,120.0f * (i % 3),0.0f},Tiles[i]->GetRelativeLocation() * GetActorScale3D() });
				//Building->SetActorLocation();
			}
			else
			{
				UE_LOG(LogClass, Warning, TEXT("%d: Building Is NULLPTR!"), i);
			}
			Tile_Actor.Add(Tiles[i], Building);
			break;
		}
		case (BYTE)ETILETYPE::FLOATINGTILE: // FLOATING TILE
		{
			// 부유타일 생성 및 추가
			AFloatingTile* FloatingTile = GetWorld()->SpawnActorDeferred<AFloatingTile>(AFloatingTile::StaticClass(), FTransform(), this);
			if (FloatingTile)
			{
				FloatingTile->Initialize(FVector(0.0f, 0.0f, MoveZOffset));
				FloatingTile->FinishSpawning(FTransform{ FRotator{},Tiles[i]->GetRelativeLocation() * GetActorScale3D() });
			}
			else
			{
				UE_LOG(LogClass, Warning, TEXT("%d: FloatingTile Is NULLPTR!"), i);
			}
			Tile_Actor.Add(Tiles[i], FloatingTile);
			break;
		}
		case (BYTE)ETILETYPE::SPAWNBUILDING_A:
		{
			if (Name == "Section1")
				ATeamBuildings[1] = SpawnTeamBuilding(Tiles[i], Floor, Name);
			else
				ATeamBuildings[0] = SpawnTeamBuilding(Tiles[i], Floor, Name);
			break;
		}
		case (BYTE)ETILETYPE::SPAWNBUILDING_B:
		{
			if (Name == "Section1")
				BTeamBuildings[1] = SpawnTeamBuilding(Tiles[i], Floor, Name);
			else
				BTeamBuildings[0] = SpawnTeamBuilding(Tiles[i], Floor, Name);
			break;
		}
		default:
			break;
		}

	}

	//BYTE Middle = BuildingInfo[0];
	//BYTE Section3[(BYTE)ESectionCount::SECTION3];
	//BYTE Section2[(BYTE)ESectionCount::SECTION2];
	//BYTE Section1[(BYTE)ESectionCount::SECTION1];
	//
	//const int CountSection3 = (BYTE)ESectionCount::SECTION3;
	//const int CountSection2 = (BYTE)ESectionCount::SECTION2;
	//const int CountSection1 = (BYTE)ESectionCount::SECTION1;
	//
	//memcpy(Section3, BuildingInfo + 1, CountSection3);
	//memcpy(Section2, BuildingInfo + 1 + CountSection3, CountSection2);
	//memcpy(Section1, BuildingInfo + 1 + CountSection3 + CountSection2, CountSection1);
	//
	//TArray<UChildActorComponent*> SectionTiles = GetTilesWithTag(FName("Section3"));
	//for (int i = 0; i < CountSection3; i++)
	//{
	//	switch (Section3[i])
	//	{
	//	case (BYTE)ETILETYPE::FLOATINGTILE: // FLOATING TILE
	//	{
	//		// 부유타일 생성 및 추가
	//		AFloatingTile* FloatingTile = GetWorld()->SpawnActorDeferred<AFloatingTile>(AFloatingTile::StaticClass(), FTransform(), this);
	//		if (FloatingTile)
	//		{
	//			FloatingTile->Initialize(FVector(0.0f, 0.0f, -6500.0f));
	//			FloatingTile->FinishSpawning(FTransform{ FRotator{},SectionTiles[i]->GetRelativeLocation() * GetActorScale3D()});
	//		}
	//		Tile_Actor.Add(SectionTiles[i], FloatingTile);
	//		break;
	//	}
	//	case (BYTE)ETILETYPE::SPAWNBUILDING_A:
	//	{
	//		ATeamBuildings.Add(SpawnTeamBuilding(GetLineTileFromAngleAndDistance(i, 1), 7, FName("Section3")));
	//		break;
	//	}
	//	case (BYTE)ETILETYPE::SPAWNBUILDING_B:
	//	{
	//		BTeamBuildings.Add(SpawnTeamBuilding(GetLineTileFromAngleAndDistance(i, 1), 7, FName("Section3")));
	//		break;
	//	}
	//	default:
	//		break;
	//	}
	//}
	//
	//SectionTiles = GetTilesWithTag(FName("Section2"));
	//for (int i = 0; i < CountSection2; i++)
	//{
	//	switch (Section2[i])
	//	{
	//	case 1:	// BUILDING
	//	{
	//		// 빌딩 생성 및 추가
	//		ABuilding* Building = GetWorld()->SpawnActorDeferred<ABuilding>(ABuilding::StaticClass(), FTransform(), this);
	//		if (Building)
	//		{
	//			Building->Initialize(5);
	//			Building->FinishSpawning(FTransform{ FRotator{0.0f,120.0f * (i % 3),0.0f},SectionTiles[i]->GetRelativeLocation() * GetActorScale3D()});
	//			//Building->SetActorLocation();
	//		}
	//		Tile_Actor.Add(SectionTiles[i], Building);
	//		break;
	//	}
	//	case 2: // FLOATING TILE
	//	{
	//		// 부유타일 생성 및 추가
	//		AFloatingTile* FloatingTile = GetWorld()->SpawnActorDeferred<AFloatingTile>(AFloatingTile::StaticClass(), FTransform(), this);
	//		if (FloatingTile)
	//		{
	//			FloatingTile->Initialize(FVector(0.0f, 0.0f, -4500.0f));
	//			FloatingTile->FinishSpawning(FTransform{ FRotator{},SectionTiles[i]->GetRelativeLocation() * GetActorScale3D() });
	//		}
	//		Tile_Actor.Add(SectionTiles[i], FloatingTile);
	//		break;
	//	}
	//	default:
	//		break;
	//	}
	//}
	//
	//SectionTiles = GetTilesWithTag(FName("Section1"));
	//for (int i = 0; i < CountSection1; i++)
	//{
	//	switch (Section1[i])
	//	{
	//	case (BYTE)ETILETYPE::BUILDING:	// BUILDING
	//	{
	//		// 빌딩 생성 및 추가
	//		ABuilding* Building = GetWorld()->SpawnActorDeferred<ABuilding>(ABuilding::StaticClass(), FTransform(), this);
	//		if (Building)
	//		{
	//			Building->Initialize(5);
	//			Building->FinishSpawning(FTransform{ FRotator{0.0f,120.0f * (i % 3),0.0f},SectionTiles[i]->GetRelativeLocation() * GetActorScale3D() });
	//			//Building->SetActorLocation();
	//		}
	//		Tile_Actor.Add(SectionTiles[i], Building);
	//		break;
	//	}
	//	case (BYTE)ETILETYPE::FLOATINGTILE: // FLOATING TILE
	//	{
	//		// 부유타일 생성 및 추가
	//		AFloatingTile* FloatingTile = GetWorld()->SpawnActorDeferred<AFloatingTile>(AFloatingTile::StaticClass(), FTransform(), this);
	//		if (FloatingTile)
	//		{
	//			FloatingTile->Initialize(FVector(0.0f, 0.0f, -4500.0f));
	//			FloatingTile->FinishSpawning(FTransform{ FRotator{},SectionTiles[i]->GetRelativeLocation() * GetActorScale3D() });
	//		}
	//		Tile_Actor.Add(SectionTiles[i], FloatingTile);
	//		break;
	//	}
	//	case (BYTE)ETILETYPE::SPAWNBUILDING_A:
	//	{
	//		ATeamBuildings.Add(SpawnTeamBuilding(GetLineTileFromAngleAndDistance(i, 3), 3, FName("Section1")));
	//		break;
	//	}
	//	case (BYTE)ETILETYPE::SPAWNBUILDING_B:
	//	{
	//		BTeamBuildings.Add(SpawnTeamBuilding(GetLineTileFromAngleAndDistance(i, 3), 3, FName("Section1")));
	//		break;
	//	}
	//	default:
	//		break;
	//	}
	//}
}

void AHexagonTile::Init()
{	
	AMainGameMode* GameMode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(this));
	if(!GameMode->GetIsConnected())
		InitialSettings();
}

void AHexagonTile::SpawnItem(PItemInfo* Items, const uint8 SpawnCount)
{
	//int SpawnCount = 5 - (TileDropLevel * 2);
	ABuilding* Building = nullptr;
	for (int i = 0; i < SpawnCount; i++)
	{
		volatile auto IndexActorComponent = Tiles[Items[i].TileIndex];
		volatile auto TileActor = Tile_Actor.Find(IndexActorComponent);
		if (!TileActor)
		{
			UE_LOG(LogClass, Warning, TEXT("AHexagonTile::SpawnItem TileActor Is nullptr"));
			continue;
		}

		Building = Cast<ABuilding>(*TileActor);
		if (!Building)
		{
			UE_LOG(LogClass, Warning, TEXT("AHexagonTile::SpawnItem Building Is nullptr"));
			continue;
		}

		FVector BuildingLocation = (*Building->Building_Floors[Items[i].Floor]).GetActorLocation();
		BuildingLocation.X += 100.f;
		BuildingLocation.Y += 100.f;
		BuildingLocation.Z -= 800.f;

		// 임시 아이템 스폰 장소, 후에 건물내에 스폰할 위치를 넣어서
		FHitResult Result;
		GetWorld()->LineTraceSingleByChannel(Result, BuildingLocation,
			FVector{ BuildingLocation.X, BuildingLocation.Y, BuildingLocation.Z - 2000.f },
			ECollisionChannel::ECC_WorldStatic);

		ALootingItemActor* LootingActor = GetWorld()->SpawnActorDeferred<ALootingItemActor>(ALootingItemActor::StaticClass(),
			FTransform(FRotator(), Result.Location), this);
		if (LootingActor)
		{
			LootingActor->Initialize((EItemEffect)Items[i].Effect, (EItemRareLevel)Items[i].ItemLevel);
			LootingActor->FinishSpawning(FTransform(FRotator(), Result.Location));

			ItemMap.Add({ ItemSerial++, LootingActor });
		}
	}
}

void AHexagonTile::RemoveItem(BYTE SerialNum)
{
	if (ItemMap.Find(SerialNum))
	{
	//	int Index = ItemMap[SerialNum]->
		ItemMap[SerialNum]->Destroy();
		ItemMap.Remove(SerialNum);
	}
}

BYTE AHexagonTile::FindItemSerialNum(const AActor* LootingActor)
{
	for (int i = 0; i < ItemMap.Num(); i++)
	{
		if (ItemMap[i] == LootingActor)
		{
			return i;
		}
	}
	return (BYTE)(-1);
}

TArray<UChildActorComponent*> AHexagonTile::GetTilesWithTag(FName tag)
{
	TArray<UChildActorComponent*> SectionTiles;
	for (const auto& pTile : Tiles)
	{
		// TileTag 태그를 가진 타일들을 추출한다.
		if (pTile && pTile->ComponentHasTag(tag))
		{
			SectionTiles.Add(pTile);
		}
	}
	return SectionTiles;
}

FVector AHexagonTile::GetSpawnLocation(bool IsTeamA)
{
	if (ATeamBuildings.IsEmpty() || BTeamBuildings.IsEmpty()) return FVector();

	int TileDropIndex = TileDropLevel == 0 ? 1 : 0;
	ABuilding* Building = nullptr;
	if(IsTeamA)
	{
		Building = Cast<ABuilding>(ATeamBuildings[TileDropIndex]);

	}
	else
	{
		Building = Cast<ABuilding>(BTeamBuildings[TileDropIndex]);
	}

	if (Building)
	{
		FVector ReturnVector = (*Building->Building_Floors.rbegin())->GetActorLocation();
		ReturnVector.Z -= Building->FloorDistance * 0.8f;
		return ReturnVector;
	}

	return FVector();
}

void AHexagonTile::CollapseTilesAndActors(int CollapseLevel, int CenterIndex)
{
	IncreaseTileDropLevel();

	float CollapseRemainDistance{};
	// CollapseLevel에 따라 파괴되지 않는 영역 길이 설정
	{
		if (CollapseLevel == 1) CollapseRemainDistance = 2.5f;
		else CollapseRemainDistance = 1.5f;
	}

	CurrentMiddleTile = Tiles[CenterIndex];

	// 파괴 영역에 해당하는 육각타일 파괴 및 해당 육각타일 아래 건물 / 부유타일 삭제
	// 삭제 후 GeometryComponent에 해당하는 타일 생성
	{
		//for (UChildActorComponent* Tile : Tiles)
		for(int i =0; i<Tiles.Num(); ++i)
		{
			float TileDistance = UKismetMathLibrary::Vector_Distance(Tiles[i]->GetRelativeLocation(), CurrentMiddleTile->GetRelativeLocation());
			// 파괴 영역 체크
			if (TileDistance > offset * CollapseRemainDistance)
			{
				CollapseTile(i);
				i -= 1;
			} 
		}
	}
}

FVector2D AHexagonTile::GetTileWidgetAlignment(int index) const
{
	if (index >= Tiles.Num()) return FVector2D{};
	FVector TileLocation = Tiles[index]->GetRelativeLocation();
	FVector2D WidgetAlignment{};

	// x축 업 -> y축 업 // y축 업 -> x축 다운
	WidgetAlignment = FVector2D(-TileLocation.Y / offset*0.88f, TileLocation.X / offset);

	// 위젯 중앙정렬로 인한 0.5f 0.5f 초기값 더하기
	WidgetAlignment.X += 0.5f; WidgetAlignment.Y += 0.5f;

	return WidgetAlignment;
}



ETileImageType AHexagonTile::GetTileImageType(int index)
{
	if (index >= Tiles.Num()) return ETileImageType::ETIT_Normal;

	{//  TODO: 만약 해당 타일 자식이 아이템을 가지고 있다면 아이템 으로 반환시키기

	}
	
	if(Tile_Actor.Contains(Tiles[index]))
	{
		AActor* ChildActor = *Tile_Actor.Find(Tiles[index]);
		if(Cast<ABuilding>(ChildActor))
		{
			return ETileImageType::ETIT_Building;
		}
		if(Cast<AFloatingTile>(ChildActor))
		{
			return ETileImageType::ETIT_FloatTile;
		}
	}

	return ETileImageType::ETIT_Normal;
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
		//for (UChildActorComponent* Tile : Tiles)
		for(volatile int i =0; i<Tiles.Num(); ++i)
		{
			float TileDistance = UKismetMathLibrary::Vector_Distance(Tiles[i]->GetRelativeLocation(), CurrentMiddleTile->GetRelativeLocation());
			// 파괴 영역 체크
			if (TileDistance > offset * CollapseRemainDistance)
			{
				CollapseTile(i);
				i -= 1;
			}
		}
	}

}

void AHexagonTile::CollapseLevel3(uint8 CenterIndex)
{
	CollapseTile(CenterIndex);
}

FVector2D AHexagonTile::GetAlignmentByLocation(const FVector& ActorLocation)
{
	FVector2D WidgetAlignment{};

	// x축 업 -> y축 업 // y축 업 -> x축 다운
	WidgetAlignment = FVector2D(-ActorLocation.Y / offset * 0.88f, ActorLocation.X / offset);

	// 위젯 중앙정렬로 인한 0.5f 0.5f 초기값 더하기
	WidgetAlignment.X += 0.5f; WidgetAlignment.Y += 0.5f;

	return WidgetAlignment;
}

void AHexagonTile::CollapseLevel3()
{
	int index = UKismetMathLibrary::RandomIntegerInRange(0, Tiles.Num() - 1);

	CollapseTile(index);
}

void AHexagonTile::CollapseTile(int CollapseTargetIndex)
{
	if (CollapseTargetIndex >= Tiles.Num()) return;

	FVector GeometrySpawnLocation = Tiles[CollapseTargetIndex]->GetRelativeLocation();
	if (Tile_Actor.Contains(Tiles[CollapseTargetIndex]))
	{
		AActor* TargetActor = *(Tile_Actor.Find(Tiles[CollapseTargetIndex]));
		ICollapsible* Child_Actor = Cast<ICollapsible>(TargetActor);
		if (Child_Actor)
		{
			Child_Actor->DoCollapse();
			TargetActor->SetLifeSpan(20.0f);

		}
		Tile_Actor.Remove(Tiles[CollapseTargetIndex]);
	}
	Tiles[CollapseTargetIndex]->DestroyComponent();
	Tiles.RemoveAt(CollapseTargetIndex);

	// 타일 GeometryCollection 생성
	AActor* NewGCTileActor = GetWorld()->SpawnActor(GC_Tile);
	NewGCTileActor->SetActorLocation(GeometrySpawnLocation);
	NewGCTileActor->SetLifeSpan(30.0f);

	auto c = GetWorld()->GetFirstPlayerController();
	auto b = Cast<ASkyscraperPlayerController>(c);
	b->GetMiniMapWidget()->CollapseTileImage(CollapseTargetIndex);

	//{// 모든 플레이어 컨트롤러에게 이미지를 바꾸도록 요구
	//	FConstPlayerControllerIterator PCIter =  GetWorld()->GetPlayerControllerIterator();
	//	for(int i =0; i< GetWorld()->GetNumPlayerControllers(); ++i)
	//	{
	//		//Cast<ASkyscraperPlayerController>(*PCIter)->GetMiniMapWidget()->SetTileImage(CollapseTargetIndex, ETileImageType::ETIT_Collapse);
	//		Cast<ASkyscraperPlayerController>(*PCIter)->GetMiniMapWidget()->CollapseTileImage(CollapseTargetIndex);
	//	}
	//	
	//}
}
