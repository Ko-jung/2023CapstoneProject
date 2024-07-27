// Fill out your copyright notice in the Description page of Project Settings.


#include "HexagonTile.h"

#include "SingleHexagonTile.h"
#include "Kismet/KismetMathLibrary.h"
#include "Skyscraper/MainGame/Map/Building/Building.h"
#include "Skyscraper/MainGame/Map/FloatingTile/FloatingTile.h"
#include "Skyscraper/MainGame/Map/Building/SingleBuildingFloor.h"

#include "Kismet/GameplayStatics.h"
#include "Skyscraper/Enum/ETileImageType.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "Skyscraper/MainGame/Core/SkyscraperPlayerController.h"
#include "Skyscraper/MainGame/Widget/MiniMap/MiniMapWidget.h"
#include "Skyscraper/Network/MainGameMode.h"

#include "Skyscraper/MainGame/Actor/LootingItem/LootingItemActor.h"
#include "Skyscraper/Subsystem/SkyscraperEngineSubsystem.h"

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
	// 팀 리스폰 위치 빌딩 생성
	{
		// 붕괴 방향 설정 ( 0',60',120',180',240',300' )
		CollapseDirectionAngle = FMath::RandRange(0, 5);

		ATeamBuildings.Add(SpawnTeamBuilding(
			GetLineTileFromAngleAndDistance((CollapseDirectionAngle + 3) % 6, 3),
			3, FName("Section1")));
		ATeamBuildings.Add(SpawnTeamBuilding(
			GetLineTileFromAngleAndDistance((CollapseDirectionAngle + 3) % 6, 1),
			5, FName("Section3")));
		ATeamBuildings.Add(SpawnTeamBuilding(
			GetLineTileFromAngleAndDistance(CollapseDirectionAngle, 1),
			5, FName("Section3")));

		BTeamBuildings.Add(SpawnTeamBuilding(
			GetLineTileFromAngleAndDistance(CollapseDirectionAngle, 3),
			3, FName("Section1")));
	}

	// 각 구역별 빌딩 생성
	{
		SpawnBuildings(6, FName("Section1"), 3);
		SpawnBuildings(4, FName("Section2"), 4);

		SpawnBuildings(1, FName("MiddleTile"), 6);
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
			Tile_Actor.Add(Tiles[i], Building);
			break;
		}
		case (BYTE)ETILETYPE::FLOATINGTILE: // FLOATING TILE
		{
			// 부유타일 생성 및 추가
			AFloatingTile* FloatingTile = GetWorld()->SpawnActorDeferred<AFloatingTile>(AFloatingTile::StaticClass(), FTransform(), this);
			if (FloatingTile)
			{

				// Speed = UKismetMathLibrary::RandomFloatInRange(0.5, 0.7);		Speed = (500 + (i*i % 200))/100
				// 
				// MoveTime = UKismetMathLibrary::RandomFloatInRange(4.0, 7.0);		MoveTime = (400 + (i*i % 300))/100
				// WaitTime = UKismetMathLibrary::RandomFloatInRange(1.0, 2.0);		WaitTime = (100 + (i*i % 100))/100


				FloatingTile->Initialize(FVector(0.0f, 0.0f, MoveZOffset));
				FloatingTile->InitializeProperty(	((double)500 + ((i * i) % 200)) / 100,
													((float)400 + ((i * i) % 300)) / 100,
													((float)100 + ((i * i) % 100)) / 100);
				FloatingTile->FinishSpawning(FTransform{ FRotator{},Tiles[i]->GetRelativeLocation() * GetActorScale3D() });
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
}

void AHexagonTile::Init()
{
	AMainGameMode* GameMode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode || !GameMode->GetIsConnected())
	{
		InitialSettings();
	}
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
			continue;
		}

		Building = Cast<ABuilding>(*TileActor);
		if (!Building)
		{
			continue;
		}

		if (!Building->Building_Floors.IsValidIndex(Items[i].Floor)) continue;

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

			ItemMap.Add({ ItemSerial, LootingActor });
			
			if (TileActorItem.Find(ItemSerial))
			{
			}
			else
			{
				TileActorItem.Add({ ItemSerial, Items[i].TileIndex });
			}

			++ItemSerial;
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

		TileActorItem.Remove(SerialNum);
	}
}

BYTE AHexagonTile::FindItemSerialNum(const AActor* LootingActor)
{
	for (const auto& Item : ItemMap)
	{
		if (Item.Value == LootingActor)
		{
			return Item.Key;
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
				CollapseTileIndexes.Add(i);
				//CollapseTile(i);
				//i -= 1;
			}
		}

		// 붕괴할 타일이 있다면 타이머를 진행
		if(!CollapseTileIndexes.IsEmpty())
		{
			if(!CollapseTileTimerHandle.IsValid())
			{
				GetWorld()->GetTimerManager().SetTimer(CollapseTileTimerHandle, this, &ThisClass::CollapseTileOnDelay, CollapseDelaySeconds, true);
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
		for (const auto& TAI : TileActorItem)
		{
			if (TAI.Value == index) return ETileImageType::ETIT_Item;
		}
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

const int8 AHexagonTile::GetItemTileIndex(int SerialNum)
{
	if (!TileActorItem.Find(SerialNum)) return -1;
	return TileActorItem[SerialNum];
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
		for(int i =0; i<Tiles.Num(); ++i)
		{
			float TileDistance = UKismetMathLibrary::Vector_Distance(Tiles[i]->GetRelativeLocation(), CurrentMiddleTile->GetRelativeLocation());
			// 파괴 영역 체크
			if (TileDistance > offset * CollapseRemainDistance)
			{
				CollapseTileIndexes.Add(i);
				//CollapseTile(i);
				//i -= 1;
			}
		}

		// 붕괴할 타일이 있다면 타이머를 진행
		if (!CollapseTileIndexes.IsEmpty())
		{
			if (!CollapseTileTimerHandle.IsValid())
			{
				GetWorld()->GetTimerManager().SetTimer(CollapseTileTimerHandle, this, &ThisClass::CollapseTileOnDelay, CollapseDelaySeconds, true,0.0f);
			}
		}
	}

}


void AHexagonTile::CollapseTileOnDelay()
{
	if (CollapseTileIndexes.IsEmpty())
	{
		GetWorld()->GetTimerManager().ClearTimer(CollapseTileTimerHandle);
	}

	// 기존에는 15초마다 바로 붕괴시켰으나,
	// 5초의 붕괴 알림을 나타내는 이미지를 위해 해당 부분에선 미니맵의 이미지 머테리얼만 변경하고
	// 5초 후에 실질적인 붕괴가 일어나도록 구현
	ASkyscraperPlayerController* PlayerController = Cast<ASkyscraperPlayerController>(GetWorld()->GetFirstPlayerController());
	for (int i = 0; i < 3; ++i)
	{
		if (CollapseTileIndexes.IsEmpty())
		{
			break;
		}
		int Index = 0;// FMath::Rand() % CollapseTileIndexes.Num();
		int TileIndex = CollapseTileIndexes[Index];
		CollapseTileIndexes.Remove(TileIndex);
		CollapseAfterNotificationIndex.Add(TileIndex);
		PlayerController->GetMiniMapWidget()->SetTileImageToCollapseNotification(TileIndex);
	}

	if(!CollapseAfterNotificationIndex.IsEmpty())
	{
		GetWorld()->GetTimerManager().SetTimer(CollapseTileAfterNotificationTimerHandle, this, &ThisClass::CollapseTileAfterNotification, CollapseAfterNotificationTime, false, CollapseAfterNotificationTime);
	}
}

void AHexagonTile::CollapseTileAfterNotification()
{
	if(!CollapseAfterNotificationIndex.IsEmpty())
	{
		// 건물이 붕괴하므로 소리 재생
		if (USkyscraperEngineSubsystem* Subsystem = GEngine->GetEngineSubsystem<USkyscraperEngineSubsystem>())
		{
			// 부스트 시작 소리 실행
			if (USoundBase* Sound = Subsystem->GetSkyscraperSound(TEXT("TileCollapse")))
			{
				UGameplayStatics::PlaySound2D(GetWorld(), Sound);
			}
		}
	}

	for(int i = 0; i < CollapseAfterNotificationIndex.Num(); ++i)
	{
		int TileIndex = CollapseAfterNotificationIndex[i];
		CollapseTile(TileIndex);

		// 건물 붕괴 후 기존에 있던 인덱스 들이 줄어드므로 붕괴된 건물 수 만큼 값을 줄여줘야함.

		for(int& Index : CollapseAfterNotificationIndex)
		{
			if(Index >= TileIndex)
			{
				Index -= 1;
			}
		}

		for (int& Index : CollapseTileIndexes)
		{
			if (Index >= TileIndex)
			{
				Index -= 1;
			}
		}
	}
	CollapseAfterNotificationIndex.Empty();
}

void AHexagonTile::CollapseLevel3(uint8 CenterIndex)
{
	int Index = FMath::Rand() % Tiles.Num();
	CollapseTileIndexes.Add(Index);
	// 붕괴할 타일이 있다면 타이머를 진행
	if (!CollapseTileIndexes.IsEmpty())
	{
		if (!CollapseTileTimerHandle.IsValid())
		{
			GetWorld()->GetTimerManager().SetTimer(CollapseTileTimerHandle, this, &ThisClass::CollapseTileOnDelay, CollapseDelaySeconds, true, 0.0f);
		}
	}
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
	int Index = FMath::Rand() % Tiles.Num();
	CollapseTileIndexes.Add(Index);
	// 붕괴할 타일이 있다면 타이머를 진행
	if (!CollapseTileIndexes.IsEmpty())
	{
		if (!CollapseTileTimerHandle.IsValid())
		{
			GetWorld()->GetTimerManager().SetTimer(CollapseTileTimerHandle, this, &ThisClass::CollapseTileOnDelay, CollapseDelaySeconds, true, 0.0f);
		}
	}
}

void AHexagonTile::CollapseTile(int CollapseTargetIndex)
{
	if (CollapseTargetIndex >= Tiles.Num()) return;

	for (auto& Item : TileActorItem)
	{
		if (Item.Value == CollapseTargetIndex)
		{
			TileActorItem.Remove(Item.Key);
			break;
		}		
	}

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
	//		//Cast<ASkyscraperPlayerController>(*PCIter)->GetMiniMapWidget()->
	// (CollapseTargetIndex, ETileImageType::ETIT_Collapse);
	//		Cast<ASkyscraperPlayerController>(*PCIter)->GetMiniMapWidget()->CollapseTileImage(CollapseTargetIndex);
	//	}
	//	
	//}
}
