// Fill out your copyright notice in the Description page of Project Settings.


#include "HexagonTile.h"
#include <Kismet/KismetMathLibrary.h>



// Sets default values
AHexagonTile::AHexagonTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	offset = 3030.0f;

	// 타일 static mesh와 material 로드
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TileAsset(TEXT("/Script/Engine.StaticMesh'/Game/2016180023/map_2/map_2_tile_00.map_2_tile_00'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> TileMaterial(TEXT("/Script/Engine.Material'/Game/2019180031/Material/M_Test.M_Test'"));

	for(int i=0; i<37; ++i)
		Tiles.AddDefaulted();

	if(TileAsset.Succeeded() && TileMaterial.Succeeded())
	{	//중앙 육각 타일 배치
		Tiles[0] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MiddleTile"));
		Tiles[0]->SetStaticMesh(TileAsset.Object);
		Tiles[0]->SetMaterial(0, TileMaterial.Object);
		Tiles[0]->ComponentTags.Add(TEXT("Middle"));

		CurrentMiddleTile = Tiles[0];
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
				Tiles[tilecount]->SetRelativeLocation(RelatLoc);
				Tiles[tilecount]->ComponentTags.Add(FName(tag));
				++tilecount;
				
			}

		}
		
	}
	
	
}

FVector AHexagonTile::CalculateRelativeLocation(int32 AngleCount, int32 Distance)
{
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

