// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"

// Sets default values
ABuilding::ABuilding()
{
 	// bCanEverTick
	PrimaryActorTick.bCanEverTick = false;

	// �⺻ �� ����
	FloorDistance = 1000.0f;
	CurrentFloor = InitialFloor;
	InitialFloor = 5;

	// �ֻ�� õ�� ��ġ
	Building_Ceiling = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ceiling"));
	SetRootComponent(Building_Ceiling);

	// �ǹ� ���� ���� ���� Ŭ���� �ε�
	static ConstructorHelpers::FClassFinder<AActor> SingleBuildingFloorRef(TEXT("/Script/Engine.Blueprint'/Game/2019180031/MainGame/Map/Building/SingleBuildingFloor.SingleBuildingFloor_C'"));

	if (!SingleBuildingFloorRef.Succeeded()) return;

	// �ǹ� �� �� child actor ��ġ
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

