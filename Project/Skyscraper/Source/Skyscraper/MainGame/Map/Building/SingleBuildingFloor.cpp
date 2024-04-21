// Fill out your copyright notice in the Description page of Project Settings.


#include "SingleBuildingFloor.h"



// Sets default values
ASingleBuildingFloor::ASingleBuildingFloor()
{
 	// bCanEverTick
	PrimaryActorTick.bCanEverTick = false;

	// �ǹ��� ���� static mesh ���� //TODO: geometry component�� ���ؼ��� �߰������ ��
	{
		CreateFloorStaticMeshes();
	}
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


// ==========================================================
// �����ڿ��� ���Ǵ� �Լ�
// ==========================================================
void ASingleBuildingFloor::CreateFloorStaticMeshes()
{
	/* ��� static mesh ���� �ε忡�� static �� ������� ���� ����)
	 * static mesh�� ���� ��ǥ�� ��ġ�� ���� ���Ǽ��� ��������
	 * static mesh �������� �������� �����ϴµ�,
	 * �ش� �޽��鿡 ���� �̸����� i���� �������� �ʰ� ��� �ڵ�� �ۼ��ϸ�
	 * ������ ����� �ϳ��ϳ� ����� ������� ����������,

	 �ֿ� ����)
	 * �����ڴ� ���� ���� ���(������ ���� ���) �ѹ� �� �ۿ��ϹǷ� 
	 * static���� ���� �޸𸮸� �Ҵ��ϰ� ���� �ʿ䰡 ���ٰ� ����
	 */
	// �ٴ�
	{
		UStaticMeshComponent* FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Floor"));
		SetRootComponent(FloorMesh);
		ConstructorHelpers::FObjectFinder<UStaticMesh> FloorMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/2016180023/map/map_3_floor_002.map_3_floor_002'"));
		if(FloorMeshRef.Succeeded())
		{
			FloorMesh->SetStaticMesh(FloorMeshRef.Object);
		}
		FloorStaticMeshes.Add(FloorMesh);
	}
	// ��� 3��
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
	// ������ 2��
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
	// ���� 6��
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
	// ��ǳ��
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
	// ���
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
	// ��� ���� ��
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

	// 3���� ����â ���� ���Ͽ� ����â �߰�
	{
		// ���� ���� 3��
		for (int WallCount = 0; WallCount < 3; ++WallCount)
		{
			UStaticMeshComponent* WindowWallStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Window_Wall" + FString::FromInt(WallCount)));
			WindowWallStaticMesh->SetupAttachment(GetRootComponent());
			WindowWallStaticMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f * WallCount));

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