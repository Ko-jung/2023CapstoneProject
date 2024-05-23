// Fill out your copyright notice in the Description page of Project Settings.


#include "SingleBuildingFloor.h"



// Sets default values
ASingleBuildingFloor::ASingleBuildingFloor()
{
 	// bCanEverTick
	PrimaryActorTick.bCanEverTick = false;

	// 건물에 대한 static mesh 생성 //TODO: geometry component에 대해서도 추가해줘야 함
	{
		CreateFloorStaticMeshes();
	}

	ConstructorHelpers::FClassFinder<AActor> GC_BuildingRef(TEXT("/Script/Engine.Blueprint'/Game/2019180031/MainGame/Map/Building/BP_GC_Building.BP_GC_Building_C'"));
	GC_BuildingClass = GC_BuildingRef.Class;
}


// Called when the game starts or when spawned
void ASingleBuildingFloor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASingleBuildingFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASingleBuildingFloor::DoCollapse()
{
	FTransform Transform{ GetActorRotation(),GetActorLocation() };
	AActor* NewGCTileActor = GetWorld()->SpawnActorDeferred<AActor>(GC_BuildingClass, Transform);
	if(NewGCTileActor)
	{
		NewGCTileActor->SetActorLocation(GetActorLocation());
		NewGCTileActor->SetActorRotation(GetActorRotation());
		NewGCTileActor->FinishSpawning(Transform);
	}

	Destroy();
}


// ==========================================================
// 생성자에서 사용되는 함수
// ==========================================================
void ASingleBuildingFloor::CreateFloorStaticMeshes()
{
	/* 모든 static mesh 파일 로드에서 static 을 사용하지 않은 이유)
	 * static mesh내 로컬 좌표로 배치에 대한 편의성을 증가시켜
	 * static mesh 종류별로 여러가지 존재하는데,
	 * 해당 메쉬들에 대해 이름으로 i번쨰 접근하지 않고 모두 코드로 작성하면
	 * 무수히 길어져 하나하나 만드는 방식으로 진행했으며,

	 주요 이유)
	 * 생성자는 게임 시작 당시(에디터 오픈 당시) 한번 만 작용하므로 
	 * static으로 굳이 메모리를 할당하고 있을 필요가 없다고 느낌
	 */
	// 바닥
	{
		UStaticMeshComponent* FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Floor"));
		SetRootComponent(FloorMesh);
		ConstructorHelpers::FObjectFinder<UStaticMesh> FloorMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/2016180023/map/map_3_floor_002.map_3_floor_002'"));
		if(FloorMeshRef.Succeeded())
		{
			FloorMesh->SetStaticMesh(FloorMeshRef.Object);
		}
		SetRootComponent(FloorMesh);
		FloorStaticMeshes.Add(FloorMesh);
		
	}
	// 기둥 3개
	for (int i = 0; i < 3; ++i)
	{
		UStaticMeshComponent* PillarStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Pillar" + FString::FromInt(i)));
		PillarStaticMesh->SetupAttachment(GetRootComponent());

		FString FileName = "map_3_pillar00" + FString::FromInt(i+1);
		FString FilePath = "/Script/Engine.StaticMesh'/Game/2016180023/map/" + FileName + "." + FileName +"'";
		ConstructorHelpers::FObjectFinder<UStaticMesh> PillarMeshRef(*FilePath);
		if (PillarMeshRef.Succeeded())
		{
			PillarStaticMesh->SetStaticMesh(PillarMeshRef.Object);
		}

		FloorStaticMeshes.Add(PillarStaticMesh);
	}
	// 에어컨 2개
	for (int i = 0; i < 2; ++i)
	{
		UStaticMeshComponent* AirconStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("AirCon" + FString::FromInt(i)));
		AirconStaticMesh->SetupAttachment(GetRootComponent());

		FString FileName = "map_3_airCon00" + FString::FromInt(i+1);
		FString FilePath = "/Script/Engine.StaticMesh'/Game/2016180023/map/" + FileName + "." + FileName + "'";
		ConstructorHelpers::FObjectFinder<UStaticMesh> AirconMeshRef(*FilePath);
		if (AirconMeshRef.Succeeded())
		{
			AirconStaticMesh->SetStaticMesh(AirconMeshRef.Object);
		}

		FloorStaticMeshes.Add(AirconStaticMesh);
	}
	// 조명 6개
	for (int i = 0; i < 6; ++i)
	{
		UStaticMeshComponent* LightStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Light" + FString::FromInt(i)));
		LightStaticMesh->SetupAttachment(GetRootComponent());

		FString FileName = "map_3_light00" + FString::FromInt(i+1);
		FString FilePath = "/Script/Engine.StaticMesh'/Game/2016180023/map/" + FileName + "." + FileName + "'";
		ConstructorHelpers::FObjectFinder<UStaticMesh> LightMeshRef(*FilePath);
		if (LightMeshRef.Succeeded())
		{
			LightStaticMesh->SetStaticMesh(LightMeshRef.Object);
		}

		FloorStaticMeshes.Add(LightStaticMesh);
	}
	// 송풍기
	{
		UStaticMeshComponent* ventilatorMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("ventilator"));
		ventilatorMesh->SetupAttachment(GetRootComponent());

		ConstructorHelpers::FObjectFinder<UStaticMesh> VentilatorMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/2016180023/map/map_3_ventilator001.map_3_ventilator001'"));
		if (VentilatorMeshRef.Succeeded())
		{
			ventilatorMesh->SetStaticMesh(VentilatorMeshRef.Object);
		}

		FloorStaticMeshes.Add(ventilatorMesh);
	}
	// 계단
	{
		UStaticMeshComponent* StairMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Stair"));
		StairMesh->SetupAttachment(GetRootComponent());
		
		ConstructorHelpers::FObjectFinder<UStaticMesh> StairMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/2016180023/map/map_3_stair.map_3_stair'"));
		if (StairMeshRef.Succeeded())
		{
			StairMesh->SetStaticMesh(StairMeshRef.Object);
		}

		FloorStaticMeshes.Add(StairMesh);
	}
	// 계단 방향 벽
	{
		UStaticMeshComponent* StairWallMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StairWall"));
		StairWallMesh->SetupAttachment(GetRootComponent());

		ConstructorHelpers::FObjectFinder<UStaticMesh> StairWallMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/2016180023/map/map_3_stair_wall.map_3_stair_wall'"));
		if (StairWallMeshRef.Succeeded())
		{
			StairWallMesh->SetStaticMesh(StairWallMeshRef.Object);
		}

		FloorStaticMeshes.Add(StairWallMesh);
	}

	// 3면의 유리창 벽에 대하여 유리창 추가
	{
		// 유리 벽면 3개
		for (int WallCount = 0; WallCount < 3; ++WallCount)
		{
			UStaticMeshComponent* WindowWallStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wall" + FString::FromInt(WallCount)));
			WindowWallStaticMesh->SetupAttachment(GetRootComponent());
			WindowWallStaticMesh->SetRelativeRotation(FRotator(0.0f, 90.0f * WallCount, 0.0f));

			ConstructorHelpers::FObjectFinder<UStaticMesh> WindowWallMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/2016180023/map/map_3_wall.map_3_wall'"));
			if (WindowWallMeshRef.Succeeded())
			{
				WindowWallStaticMesh->SetStaticMesh(WindowWallMeshRef.Object);
			}

			FloorStaticMeshes.Add(WindowWallStaticMesh);

			for (int WindowCount = 0; WindowCount < 6; ++WindowCount)
			{
				UStaticMeshComponent* WindowStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Window_Wall" + FString::FromInt(WallCount) + "_" + FString::FromInt(WindowCount)));
				WindowStaticMesh->SetupAttachment(WindowWallStaticMesh);

				FString FileName = "map_3_window_00" + FString::FromInt(WindowCount+1);
				FString FilePath = "/Script/Engine.StaticMesh'/Game/2016180023/map/" + FileName + "." + FileName + "'";
				ConstructorHelpers::FObjectFinder<UStaticMesh> WindowMeshRef(*FilePath);
				if (WindowMeshRef.Succeeded())
				{
					WindowStaticMesh->SetStaticMesh(WindowMeshRef.Object);
				}

				WindowStaticMeshes.Add(WindowStaticMesh);
			}
		}
	}
}