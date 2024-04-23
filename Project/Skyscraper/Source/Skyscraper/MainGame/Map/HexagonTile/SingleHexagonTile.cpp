// Fill out your copyright notice in the Description page of Project Settings.


#include "SingleHexagonTile.h"

// Sets default values
ASingleHexagonTile::ASingleHexagonTile()
{
 	//bCanEverTick
	PrimaryActorTick.bCanEverTick = false;

	// �߾� Ÿ�� ���� �ε�
	static ConstructorHelpers::FObjectFinder<UStaticMesh> HexagonTileStaticMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/2016180023/map/map_3_tile.map_3_tile'"));
	if (!HexagonTileStaticMeshRef.Succeeded()) return;

	// �߾� Ÿ�� ����ƽ �޽� ���۳�Ʈ ����
	HexagonTileStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HexagonTile"));
	HexagonTileStaticMesh->SetStaticMesh(HexagonTileStaticMeshRef.Object);
	SetRootComponent(HexagonTileStaticMesh);
}

// Called when the game starts or when spawned
void ASingleHexagonTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASingleHexagonTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

