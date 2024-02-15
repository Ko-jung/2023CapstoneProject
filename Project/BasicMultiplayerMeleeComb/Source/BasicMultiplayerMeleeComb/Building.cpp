// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"

// Sets default values
ABuilding::ABuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FloorDistance = -501.0f;
	WallOffset = 11.0f;
	// 타일 static mesh와 material 로드
	static ConstructorHelpers::FObjectFinder<UStaticMesh> FloorAsset(TEXT("/Script/Engine.StaticMesh'/Game/2019180031/Blueprints/Map/Building/building_floor.building_floor'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Wall01Asset(TEXT("/Script/Engine.StaticMesh'/Game/2019180031/Blueprints/Map/Building/building_wall001.building_wall001'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Wall02Asset(TEXT("/Script/Engine.StaticMesh'/Game/2019180031/Blueprints/Map/Building/building_wall002.building_wall002'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Wall03Asset(TEXT("/Script/Engine.StaticMesh'/Game/2019180031/Blueprints/Map/Building/building_wall003.building_wall003'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Wall04Asset(TEXT("/Script/Engine.StaticMesh'/Game/2019180031/Blueprints/Map/Building/building_wall004.building_wall004'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> TileMaterial(TEXT("/Script/Engine.Material'/Game/2019180031/Material/M_Test.M_Test'"));
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(DefaultSceneRoot);
	for(int i=0; i<Floor; ++i)
	{
		UE_LOG(LogTemp, Warning, TEXT("%d"), i);
		{ // 바닥
			FString title = "floor" + FString::FromInt(i);
			TObjectPtr<UStaticMeshComponent> FloorSMComp;
			
			FloorSMComp = CreateDefaultSubobject<UStaticMeshComponent>(FName(title));
			FloorSMComp->SetStaticMesh(FloorAsset.Object);
			FloorSMComp->SetupAttachment(RootComponent);
			FloorSMComp->SetRelativeLocation(FVector(0.0f, 0.0f, i * FloorDistance - 500.0f));
			Building_Floor.Add(FloorSMComp);

		}

		{ // 벽 4개
			
			for(int j=0; j<4; ++j)
			{
				UE_LOG(LogTemp, Warning, TEXT("%d %d"), i, j);
				FString title = "wall" + FString::FromInt(i) + FString::FromInt(j);
				TObjectPtr<UStaticMeshComponent> WallSMComp;

				WallSMComp = CreateDefaultSubobject<UStaticMeshComponent>(FName(title));
				WallSMComp->SetupAttachment(RootComponent);
				switch(j)
				{
				case 0:
					WallSMComp->SetStaticMesh(Wall01Asset.Object);
					WallSMComp->SetRelativeLocation(FVector(0.0f,-WallOffset, i * FloorDistance));
					WallSMComp->SetMaterial(0,TileMaterial.Object);
					Building_Wall1.Add(WallSMComp);
					break;
				case 1:
					WallSMComp->SetStaticMesh(Wall02Asset.Object);
					WallSMComp->SetRelativeLocation(FVector(WallOffset,0.0f, i * FloorDistance));
					Building_Wall2.Add(WallSMComp);
					break;
				case 2:
					WallSMComp->SetStaticMesh(Wall03Asset.Object);
					WallSMComp->SetRelativeLocation(FVector(0.0f, WallOffset, i * FloorDistance));
					Building_Wall3.Add(WallSMComp);
					break;
				case 3:
					WallSMComp->SetStaticMesh(Wall04Asset.Object);
					WallSMComp->SetRelativeLocation(FVector(-WallOffset,0.0f, i * FloorDistance));
					Building_Wall4.Add(WallSMComp);
					break;
				default:
					break;
				}
			}
			
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("%d층 생김"), Floor);

}

// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

