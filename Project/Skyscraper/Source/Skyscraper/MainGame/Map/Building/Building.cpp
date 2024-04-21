// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"

#include "SingleBuildingFloor.h"

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
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CeilingRef(TEXT("/Script/Engine.StaticMesh'/Game/2016180023/map/map_3_floor_001.map_3_floor_001'"));
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
	
}

void ABuilding::Initialize(int32 GetFloor)
{
	CurrentFloor = InitialFloor = GetFloor;
	UE_LOG(LogTemp, Warning, TEXT("222"));
}

// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();

	// 건물 층 들 child actor 배치
	for (int i = 0; i < InitialFloor; ++i)
	{
		FString title = "Floor" + FString::FromInt(i);
		//UChildActorComponent* NewChildFloorActor = NewObject<UChildActorComponent>(this);
		//	//CreateDefaultSubobject<UChildActorComponent>(FName(title));
		//NewChildFloorActor->RegisterComponent();
		//NewChildFloorActor->SetChildActorClass(SingleBuildingClass);
		//NewChildFloorActor->SetupAttachment(GetRootComponent());
		//NewChildFloorActor->SetRelativeLocation(FVector(0.0f, 0.0f, -FloorDistance * i));
		AActor* NewFloorActor = GetWorld()->SpawnActor(SingleBuildingClass);
		if(NewFloorActor)
		{
			NewFloorActor->SetActorLocation(FVector(0.0f, 0.0f, -FloorDistance * i));
		}else
		{
			UE_LOG(LogTemp, Warning, TEXT("???"));
		}
		
		Building_Floors.Add(NewFloorActor);
	}
}


// Called every frame
void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

