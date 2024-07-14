// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"

#include "SingleBuildingFloor.h"
#include "Skyscraper/MainGame/Map/Furniture/Furniture.h"

// Sets default values
ABuilding::ABuilding()
{
 	// bCanEverTick
	PrimaryActorTick.bCanEverTick = false;

	// 기본 값 설정
	FloorDistance = 1000.0f;
	CurrentFloor = InitialFloor;
	InitialFloor = 5;

	// 최상단 천장 배치
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CeilingRef(TEXT("/Script/Engine.StaticMesh'/Game/2016180023/map/map_refine/map_4_floor_re000.map_4_floor_re000'"));
	if (CeilingRef.Succeeded()) {
		Building_Ceiling = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ceiling"));
		Building_Ceiling->SetStaticMesh(CeilingRef.Object);
	}
	SetRootComponent(Building_Ceiling);

	// 건물 층에 대한 액터 클래스 로드
	//static ConstructorHelpers::FClassFinder<ASingleBuildingFloor> SingleBuildingFloorRef(TEXT("/Script/Engine.Blueprint'/Game/2019180031/MainGame/Map/Building/SingleBuildingFloor.SingleBuildingFloor_C'"));
	//if (SingleBuildingFloorRef.Succeeded()) SingleBuildingClass = SingleBuildingFloorRef.Class;

	
	static ConstructorHelpers::FClassFinder<AActor> SingleBuildingFloorRef(TEXT("/Script/Engine.Blueprint'/Game/2019180031/MainGame/Map/Building/SingleBuildingFloor.SingleBuildingFloor_C'"));
	if (SingleBuildingFloorRef.Succeeded())
	{
		SingleBuildingClass = SingleBuildingFloorRef.Class;
	}

	static ConstructorHelpers::FClassFinder<AActor> FurnitureRef(TEXT("/Script/Engine.Blueprint'/Game/2019180031/MainGame/Map/Furniture/BP_Furnitures.BP_Furnitures_C'"));
	FurnitureClass = FurnitureRef.Class;
	
}

void ABuilding::Initialize(int32 GetFloor)
{
	CurrentFloor = InitialFloor = GetFloor;
}



// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();

	// 건물 층 들 child actor 배치
	for (int i = 0; i < InitialFloor; ++i)
	{
		FString title = "Floor" + FString::FromInt(i);
		ASingleBuildingFloor* NewFloorActor = Cast<ASingleBuildingFloor>(GetWorld()->SpawnActor(SingleBuildingClass));
		if(NewFloorActor)
		{
			NewFloorActor->SetActorLocation(FVector(GetActorLocation().X,GetActorLocation().Y, -FloorDistance * i));
			NewFloorActor->SetActorRotation(GetActorRotation());
		}
		Building_Floors.Add(NewFloorActor);

		// 가구 추가 배치
		AFurniture* NewFurnitureActor = Cast<AFurniture>(GetWorld()->SpawnActor(FurnitureClass));
		if(NewFurnitureActor)
		{
			NewFurnitureActor->SetActorLocation(NewFloorActor->GetActorLocation());
			NewFurnitureActor->SetActorRotation(GetActorRotation());
		}
		FurnitureActors.Add(NewFurnitureActor);
	}
}

void ABuilding::CollapseBuilding(int CollapseStartFloor)
{
	Building_Ceiling->DestroyComponent();
	for (int i = CollapseStartFloor; i < CurrentFloor; ++i)
	{
		Building_Floors[i]->DoCollapse();
		FurnitureActors[i]->DoCollapse();
	}
	CurrentFloor = CollapseStartFloor - 1;
}

// Called every frame
void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABuilding::DoCollapse()
{
	CollapseBuilding(0);
}

