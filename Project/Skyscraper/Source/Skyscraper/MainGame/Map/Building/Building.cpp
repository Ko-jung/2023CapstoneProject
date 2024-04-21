// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"

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
	Building_Ceiling = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ceiling"));
	SetRootComponent(Building_Ceiling);

	// 건물 층에 대한 액터 클래스 로드
	static ConstructorHelpers::FClassFinder<AActor> SingleBuildingFloorRef(TEXT("/Script/Engine.Blueprint'/Game/2019180031/MainGame/Map/Building/SingleBuildingFloor.SingleBuildingFloor_C'"));

	if (!SingleBuildingFloorRef.Succeeded()) return;

	// 건물 층 들 child actor 배치
	for(int i =0; i<InitialFloor; ++i)
	{
		FString title = "Floor" + FString::FromInt(i);
		UChildActorComponent* NewChildFloorActor = CreateDefaultSubobject<UChildActorComponent>(FName(title));
		NewChildFloorActor->SetChildActorClass(SingleBuildingFloorRef.Class);
		NewChildFloorActor->SetupAttachment(GetRootComponent());
		NewChildFloorActor->SetRelativeLocation(FVector(0.0f, 0.0f, - FloorDistance * i));
		Building_Floors.Add(NewChildFloorActor);
	}
	
}

void ABuilding::Initialize(int32 GetFloor)
{
	CurrentFloor = InitialFloor = GetFloor;
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

