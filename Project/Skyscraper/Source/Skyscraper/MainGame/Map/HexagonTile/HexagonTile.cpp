// Fill out your copyright notice in the Description page of Project Settings.


#include "HexagonTile.h"

#include "Kismet/KismetMathLibrary.h"
#include "Skyscraper/MainGame/Map/Building/Building.h"

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

	// �ر� ���� ����
	CollapseDirectionAngle = FMath::RandRange(0, 5);		// 0',60',120',180',240',300' �� �ر��Ǵ� ���⿡ ���� Angle ����

	// �ǹ� Ŭ���� �ε�
	static ConstructorHelpers::FClassFinder<AActor> BuildingClassRef(TEXT("/Script/Engine.Blueprint'/Game/2019180031/MainGame/Map/Building/SingleBuildingFloor.SingleBuildingFloor_C'"));
	BuildingClass = BuildingClassRef.Class;
	
	
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

	// �� ������ ���� �� ����Ÿ�� ����
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
					Building->FinishSpawning(FTransform{FRotator{},TargetTile->GetRelativeLocation() });
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

