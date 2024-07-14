// Fill out your copyright notice in the Description page of Project Settings.


#include "Desk.h"

#include "Components/HierarchicalInstancedStaticMeshComponent.h"

// Sets default values
ADesk::ADesk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//HISM_Chair = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("HISM_Chair"));
	//HISM_Desk = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("HISM_Desk"));
	//HISM_Desktop = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("HISM_Desktop"));
	//HISM_Monitor = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("HISM_Monitor"));
	//HISM_Partition = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("HISM_Partition"));
}


// Called when the game starts or when spawned
void ADesk::BeginPlay()
{
	Super::BeginPlay();

	HISM_Chair = Cast<UHierarchicalInstancedStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("HISM_ChairComp")));
	HISM_Desk = Cast<UHierarchicalInstancedStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("HISM_DeskComp")));
	HISM_Desktop = Cast<UHierarchicalInstancedStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("HISM_DesktopComp")));
	HISM_Monitor = Cast<UHierarchicalInstancedStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("HISM_MonitorComp")));
	HISM_Partition = Cast<UHierarchicalInstancedStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("HISM_PartitionComp")));
	

}

// Called every frame
void ADesk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

