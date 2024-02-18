// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"

#include "GeometryCollection/GeometryCollectionComponent.h"
#include "GeometryCollection/GeometryCollectionObject.h"
#include "Kismet/KismetMathLibrary.h"

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
}

// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();

	CurrentFloor = Floor;
	
}

// Called every frame
void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void ABuilding::CollapseBuilding(int32 CollapseStartFloor)
{
	for(int i= CollapseStartFloor; i<CurrentFloor; ++i)
	{
		SwapStaticToGeometry(Building_Floor[i], BuildingComposition::Floor);
		SwapStaticToGeometry(Building_Wall1[i], BuildingComposition::Wall1);
		SwapStaticToGeometry(Building_Wall2[i], BuildingComposition::Wall2);
		SwapStaticToGeometry(Building_Wall3[i], BuildingComposition::Wall3);
		SwapStaticToGeometry(Building_Wall4[i], BuildingComposition::Wall4);
	}
	CurrentFloor = CollapseStartFloor-1;
}

void ABuilding::SwapStaticToGeometry(UStaticMeshComponent* Target, BuildingComposition Composition)
{
	// Geometry Collection 생성 위치
	FVector GCPos = GetActorLocation();
	GCPos.Z += Target->GetRelativeLocation().Z;

	// 해당 SMComp 소멸
	Target->DestroyComponent();

	switch (Composition)
	{
	case BuildingComposition::Floor:
		GetWorld()->SpawnActor<AActor>(GC_Floor, GCPos, FRotator(0.0f, 0.0f, 0.0f));
		break;
	case BuildingComposition::Wall1:
		GetWorld()->SpawnActor<AActor>(GC_Wall01, GCPos, FRotator(0.0f, 0.0f, 0.0f));
		break;
	case BuildingComposition::Wall2:
		GetWorld()->SpawnActor<AActor>(GC_Wall02, GCPos, FRotator(0.0f, 0.0f, 0.0f));
		break;
	case BuildingComposition::Wall3:
		GetWorld()->SpawnActor<AActor>(GC_Wall03, GCPos, FRotator(0.0f, 0.0f, 0.0f));
		break;
	case BuildingComposition::Wall4:
		GetWorld()->SpawnActor<AActor>(GC_Wall04, GCPos, FRotator(0.0f, 0.0f, 0.0f));
		break;
	default:
		break;
	}
	//// Geometry Comp 로드
	//static FSoftObjectPath MyGCPath_Floor(TEXT("/Script/GeometryCollectionEngine.GeometryCollection'/Game/2019180031/Blueprints/Map/Building/GeometryComp/GeoComp_Floor.GeoComp_Floor'"));
	//static UGeometryCollection* MyGC_Floor = Cast<UGeometryCollection>(MyGCPath_Floor.ResolveObject());
	//if (!MyGC_Floor) MyGC_Floor = CastChecked<UGeometryCollection>(MyGCPath_Floor.TryLoad());

	//static FSoftObjectPath MyGCPath_Wall01(TEXT("/Script/GeometryCollectionEngine.GeometryCollection'/Game/2019180031/Blueprints/Map/Building/GeometryComp/GeoComp_wall1.GeoComp_wall1'"));
	//static UGeometryCollection* MyGC_Wall01 = Cast<UGeometryCollection>(MyGCPath_Wall01.ResolveObject());
	//if (!MyGC_Wall01) MyGC_Wall01 = CastChecked<UGeometryCollection>(MyGCPath_Wall01.TryLoad());

	//static FSoftObjectPath MyGCPath_Wall02(TEXT("/Script/GeometryCollectionEngine.GeometryCollection'/Game/2019180031/Blueprints/Map/Building/GeometryComp/GeoComp_wall2.GeoComp_wall2'"));
	//static UGeometryCollection* MyGC_Wall02 = Cast<UGeometryCollection>(MyGCPath_Wall02.ResolveObject());
	//if (!MyGC_Wall02) MyGC_Wall02 = CastChecked<UGeometryCollection>(MyGCPath_Wall02.TryLoad());

	//static FSoftObjectPath MyGCPath_Wall03(TEXT("/Script/GeometryCollectionEngine.GeometryCollection'/Game/2019180031/Blueprints/Map/Building/GeometryComp/GeoComp_wall3.GeoComp_wall3'"));
	//static UGeometryCollection* MyGC_Wall03 = Cast<UGeometryCollection>(MyGCPath_Wall03.ResolveObject());
	//if (!MyGC_Wall03) MyGC_Wall03 = CastChecked<UGeometryCollection>(MyGCPath_Wall03.TryLoad());

	//static FSoftObjectPath MyGCPath_Wall04(TEXT("/Script/GeometryCollectionEngine.GeometryCollection'/Game/2019180031/Blueprints/Map/Building/GeometryComp/GeoComp_wall4.GeoComp_wall4'"));
	//static UGeometryCollection* MyGC_Wall04 = Cast<UGeometryCollection>(MyGCPath_Wall04.ResolveObject());
	//if (!MyGC_Wall04) MyGC_Wall04 = CastChecked<UGeometryCollection>(MyGCPath_Wall04.TryLoad());
	//
	//
	//static int testcount = 0;
	//{ // 해당하는 Geometry Collection 생성
	//	UGeometryCollectionComponent* TargetGCComp;
	//	FString Testname = FString("GCtest") + FString::FromInt(testcount++);
	//	FTransform Transform;
	//	Transform.SetLocation(GCPos);
	//	Transform.SetScale3D(FVector(1.0f, 1.0f, 1.0f));
	//	TargetGCComp = Cast<UGeometryCollectionComponent>(AddComponentByClass(UGeometryCollectionComponent::StaticClass(), false, Transform, true));
	//	

	//	switch(Composition)
	//	{
	//	case BuildingComposition::Floor:
	//		TargetGCComp->SetRestCollection(MyGC_Floor);
	//		break;
	//	case BuildingComposition::Wall1:
	//		TargetGCComp->SetRestCollection(MyGC_Wall01);
	//		break;
	//	case BuildingComposition::Wall2:
	//		TargetGCComp->SetRestCollection(MyGC_Wall02);
	//		break;
	//	case BuildingComposition::Wall3:
	//		TargetGCComp->SetRestCollection(MyGC_Wall03);
	//		break;
	//	case BuildingComposition::Wall4:
	//		TargetGCComp->SetRestCollection(MyGC_Wall04);
	//		break;
	//	default:
	//		break;
	//	}
	//	TargetGCComp->EditRestCollection(GeometryCollection::EEditUpdate::RestPhysicsDynamic, false);
	//	FinishAddComponent(TargetGCComp, false, Transform);
	//}
}

void ABuilding::DoCollapse()
{
	CollapseBuilding(0);
}

