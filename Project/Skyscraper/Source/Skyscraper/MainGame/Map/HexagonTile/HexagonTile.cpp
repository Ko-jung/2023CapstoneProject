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

	// ������ �ʱ�ȭ
	offset = 3465.0f;

	// Ÿ�� static mesh �ε�
	static ConstructorHelpers::FClassFinder<AActor> SingleHexagonTileClass(TEXT("/Script/Engine.Blueprint'/Game/2019180031/MainGame/Map/HexagonTile/SingleHexagonTile.SingleHexagonTile_C'"));
	if (!(SingleHexagonTileClass.Succeeded())) return;

	UClass* TileClass = SingleHexagonTileClass.Class;

	for (int i = 0; i < 37; ++i)
		Tiles.AddDefaulted();
	
	{	//�߾� ���� Ÿ�� ��ġ
		Tiles[0] = CreateDefaultSubobject<UChildActorComponent>(TEXT("MiddleTile"));
		Tiles[0]->SetChildActorClass(TileClass);
		Tiles[0]->ComponentTags.Add(TEXT("MiddleTile"));
		CurrentMiddleTile = Tiles[0];
		SetRootComponent(Tiles[0]);
	}


	int tilecount = 1;
	for (int angle = 0; angle < 6; ++angle)	// ���� 6�κ� Ÿ�Ͽ� ����
	{
		for (int distance = 1; distance < 4; ++distance)	// �߾� Ÿ�Ϸκ����� �Ÿ�
		{
			FString tag = "Section" + FString::FromInt((distance - 2) * -1 + 2);
			{//60�� ��� ��ġ�� StaticMesh �߰�
				FString name = tag + "_" + FString::FromInt(tilecount);
				Tiles[tilecount] = CreateDefaultSubobject<UChildActorComponent>(FName(name));
				Tiles[tilecount]->SetChildActorClass(TileClass);
				Tiles[tilecount]->SetupAttachment(Tiles[0]);
				Tiles[tilecount]->SetRelativeLocation(CalculateRelativeLocation(angle, distance));
				Tiles[tilecount]->ComponentTags.Add(FName(tag));
				++tilecount;
			}

			// 60�� ��� ���� ��ġ�� Static Mesh �߰�
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

	// �ǹ� Ŭ���� �ε�
	static ConstructorHelpers::FClassFinder<AActor> BuildingClassRef(TEXT("/Script/Engine.Blueprint'/Game/2019180031/MainGame/Map/Building/SingleBuildingFloor.SingleBuildingFloor_C'"));
	BuildingClass = BuildingClassRef.Class;

	// �ر� Ÿ�� Ŭ���� �ε�
	ConstructorHelpers::FClassFinder<AActor> GC_TileRef(TEXT("/Script/Engine.Blueprint'/Game/2019180031/MainGame/Map/HexagonTile/BP_GC_Tile.BP_GC_Tile_C'"));
	GC_Tile = GC_TileRef.Class;
}

FVector AHexagonTile::CalculateRelativeLocation(int32 AngleCount, int32 Distance)
{
	// �־��� ������ �Ÿ�(����1~4) �� ���� ������ RelativeLocation�� ��ȯ�ϴ� �Լ�
	float TileDistance = offset * Distance;

	float sin = UKismetMathLibrary::DegSin(AngleCount * 60 + 30);
	float cos = UKismetMathLibrary::DegCos(AngleCount * 60 + 30);

	return FVector(TileDistance * sin, TileDistance * cos, 0.0f);
}

void AHexagonTile::InitialSettings()
{
	// �� ������ ��ġ ���� ����
	{
		// �ر� ���� ���� ( 0',60',120',180',240',300' )
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

	// �� ������ ���� ����
	{
		SpawnBuildings(6, FName("Section1"), 3);
		SpawnBuildings(4, FName("Section2"), 5);
		
		SpawnBuildings(1, FName("MiddleTile"), 9);
	}

	// �� ������ ���� Ÿ�� ����
	{
		SpawnFloatingTiles(4, FName("Section1"), FVector(0.0f, 0.0f, -2500.0f));
		SpawnFloatingTiles(2, FName("Section2"), FVector(0.0f, 0.0f, -4500.0f));
		SpawnFloatingTiles(1, FName("Section3"), FVector(0.0f, 0.0f, -6500.0f));
	}

}

UChildActorComponent* AHexagonTile::GetLineTileFromAngleAndDistance(int32 FindAngle, int32 FindDistance, FVector FindTileLocation)
{
	// (0, 0, ��ǥ) �Է½� �ش� ��ǥ�� Ÿ�� ��ȯ
	// (1, 3) �Է½� 60�� ����� Section1 Ÿ�� ��ȯ
		// 
	if (FindDistance != 0)
	{
		FindTileLocation = CalculateRelativeLocation(FindAngle, FindDistance);
	}

	for(UChildActorComponent* Tile : Tiles)
	{
		// ��� Ÿ�� �� �ش� Ÿ�ϰ��� �Ÿ��� ���Ͽ� ã��
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
	 SpawnCount - ��ġ�� �ǹ��� ���� / TileTag - ��ġ�� Ÿ�� ���� (Section1~3) / Floor - ��ġ�� �ǹ��� �� ��
	 */
	TArray<UChildActorComponent*> SectionTiles;	// Ư�� ������ Ÿ�ϵ��� ����Ǵ� �迭
	TObjectPtr<UChildActorComponent> TargetTile; // �ǹ��� ��ġ�� Ÿ��

	{ // �ش� ���� Ÿ�� ���ϱ�
		for (const auto& pTile : Tiles)
		{
			// TileTag �±׸� ���� Ÿ�ϵ��� �����Ѵ�.
			if(pTile && pTile->ComponentHasTag(TileTag))
			{
				SectionTiles.Add(pTile);
			}
		}
	}

	{ // ���� ��ġ�ϱ�
		int BuildingCount = 0;
		while(BuildingCount < SpawnCount)
		{
			// �ǹ��� ���� �� Ÿ�� ���ϱ�
			int index = FMath::RandRange(0, SectionTiles.Num() - 1);
			TargetTile = SectionTiles[index];
			// �ش� Ÿ�Ͽ� �ǹ��� ��ġ���� �ʾҴٸ�, �ǹ��� �����Ͽ� ��ġ
			if(!Tile_Actor.Contains(TargetTile))
			{
				// ���� ���� �� �߰�
				ABuilding* Building = GetWorld()->SpawnActorDeferred<ABuilding>(ABuilding::StaticClass(), FTransform(), this);
				if (Building)
				{
					Building->Initialize(Floor);
					Building->FinishSpawning(FTransform{FRotator{0.0f,120.0f* FMath::RandRange(0, 2),0.0f},TargetTile->GetRelativeLocation() * GetActorScale3D()});
					//Building->SetActorLocation();
				}
				Tile_Actor.Add(TargetTile, Building);

				// �ش� ���� Ÿ���� ��������� ���������� ����
				SectionTiles.Remove(TargetTile);

				++BuildingCount;
			}
		}
	}
}

void AHexagonTile::SpawnFloatingTiles(int32 SpawnCount, FName TileTag, FVector MovementOffset)
{
	/*
	 SpawnCount - ��ġ�� ����Ÿ�� ���� / TileTag - ��ġ�� Ÿ�� ���� (Section1~3) / MovementOffset - ������ ����Ÿ���� ������ ������
	 */
	TArray<UChildActorComponent*> SectionTiles;	// Ư�� ������ Ÿ�ϵ��� ����Ǵ� �迭
	TObjectPtr<UChildActorComponent> TargetTile; // �ǹ��� ��ġ�� Ÿ��

	{ // �ش� ���� Ÿ�� ���ϱ�
		for (const auto& pTile : Tiles)
		{
			// TileTag �±׸� ���� Ÿ�ϵ��� �����Ѵ�.
			if (pTile && pTile->ComponentHasTag(TileTag))
			{
				SectionTiles.Add(pTile);
			}
		}
	}

	{ // ���� Ÿ�� ��ġ�ϱ�
		int FloatingTileCount = 0;
		while (FloatingTileCount < SpawnCount)
		{
			// ����Ÿ���� ���� �� Ÿ�� ���ϱ�
			int index = FMath::RandRange(0, SectionTiles.Num() - 1);
			TargetTile = SectionTiles[index];
			// �ش� Ÿ�Ͽ� �ǹ�/����Ÿ���� ��ġ���� �ʾҴٸ�, �ǹ��� �����Ͽ� ��ġ
			if (!Tile_Actor.Contains(TargetTile))
			{
				// ����Ÿ�� ���� �� �߰�
				AFloatingTile* FloatingTile = GetWorld()->SpawnActorDeferred<AFloatingTile>(AFloatingTile::StaticClass(), FTransform(), this);
				if (FloatingTile)
				{
					FloatingTile->Initialize(MovementOffset);
					FloatingTile->FinishSpawning(FTransform{ FRotator{},TargetTile->GetRelativeLocation() * GetActorScale3D() });
				}
				Tile_Actor.Add(TargetTile, FloatingTile);

				// �ش� ���� Ÿ���� ��������� ���������� ����
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
	{ // ���� ��ġ�ϱ�
		if (!Tile_Actor.Contains(TargetTile))
		{
			// ���� ���� �� �߰�
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
	// CollapseLevel�� ���� �ı����� �ʴ� ���� ���� ����
	{
		if (CollapseLevel == 1) CollapseRemainDistance = 2.5f;
		else CollapseRemainDistance = 1.5f;
	}

	// ���� �ı� �� ���� Ÿ���� �߾� Ÿ�� ���ϱ�
	{
		FVector NewMiddleTileLocation = CurrentMiddleTile->GetRelativeLocation();
		NewMiddleTileLocation.X += (offset * UKismetMathLibrary::DegSin(CollapseDirectionAngle * 60 + 30));
		NewMiddleTileLocation.Y += (offset * UKismetMathLibrary::DegCos(CollapseDirectionAngle * 60 + 30));

		CurrentMiddleTile = GetLineTileFromAngleAndDistance(0, 0, NewMiddleTileLocation);
	}

	// �ı� ������ �ش��ϴ� ����Ÿ�� �ı� �� �ش� ����Ÿ�� �Ʒ� �ǹ� / ����Ÿ�� ����
	// ���� �� GeometryComponent�� �ش��ϴ� Ÿ�� ����
	{
		for (UChildActorComponent* Tile : Tiles)
		{
			float TileDistance = UKismetMathLibrary::Vector_Distance(Tile->GetRelativeLocation(), CurrentMiddleTile->GetRelativeLocation());
			FVector GeometrySpawnLocation = Tile->GetRelativeLocation();

			// �ı� ���� üũ
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

				// Ÿ�� GeometryCollection ����
				AActor* NewGCTileActor = GetWorld()->SpawnActor(GC_Tile);
				
				NewGCTileActor->SetActorLocation(GeometrySpawnLocation);
			}
		}
	}

	{ // �迭 �� Invalid �� ����
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