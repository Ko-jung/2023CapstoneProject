// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingTile.h"
#include <Kismet/KismetMathLibrary.h>
#include "GeometryCollection/GeometryCollectionObject.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

// Sets default values
AFloatingTile::AFloatingTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TileAsset(TEXT("/Script/Engine.StaticMesh'/Game/2016180023/map_2/map_2_tile_00.map_2_tile_00'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> TileMaterial(TEXT("/Script/Engine.Material'/Engine/EngineDebugMaterials/MAT_LevelColorationLitLightmapUV.MAT_LevelColorationLitLightmapUV'"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloatingTile"));
	SetRootComponent(StaticMesh);
	StaticMesh->SetStaticMesh(TileAsset.Object);
	StaticMesh->SetMaterial(0,TileMaterial.Object);


	MovementOffset = FVector(0.0f, 0.0f, -3000.0f);

}

// Called when the game starts or when spawned
void AFloatingTile::BeginPlay()
{
	Super::BeginPlay();

	Speed = UKismetMathLibrary::RandomFloatInRange(0.5, 0.7);
	SetActorLocation(GetActorLocation() + FVector(0.0f, 0.0f, -200.0f));

	InitStartLocation = GetActorLocation();
	TargetLocation = InitEndLocation = GetActorLocation() + MovementOffset;
	MoveToEnd = true;

	UE_LOG(LogTemp, Warning, TEXT("시작함"));
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::DoCollapse, 5.0f, false);
	
}

// Called every frame
void AFloatingTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector ResultLoc = UKismetMathLibrary::VInterpTo(
		GetActorLocation(),
		TargetLocation,
		DeltaTime,
		Speed
	);

	SetActorLocation(ResultLoc);

	float DistanceToTarget = (TargetLocation - GetActorLocation()).Length();

	if(DistanceToTarget<50.0f)
	{
		if (MoveToEnd) TargetLocation = InitStartLocation;
		else TargetLocation = InitEndLocation;
		MoveToEnd = !MoveToEnd;
	}
}

void AFloatingTile::DoCollapse()
{
	UE_LOG(LogTemp, Warning, TEXT("실행됐음!!"));
	// 1. 틱 업데이트 중단
	SetActorTickEnabled(false);

	// 2. 스태틱 메시 가리기 및 콜리젼 비활성화
	StaticMesh->SetHiddenInGame(true);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 3. Geometry Collection 데이터 가져오기
	/*
	 https://dawnarc.com/2018/10/ue4lnk2019-unresolved-external-symbol-getprivatestaticclass/
	 UGeometryCollection을 사용할 경우,
	 UGeometryCollection - GetprivateStaticClass가 확인불가능 하다는 에러가 떠서 진행이 안됨,
	 Class로 UGeometryCollection을 받는 모든 부분에서 발생
	 해결책)
	 GeometryCollectionEngine 모듈이 존재하지 않았던 점이 문제(위 사이트 Case2)
	 */
	//static ConstructorHelpers::FObjectFinder<UGeometryCollection> GCAsset(TEXT("/Script/GeometryCollectionEngine.GeometryCollection'/Game/2019180031/Blueprints/Map/Tile/Tile_Geometry/Tile.Tile'"));
	// 위에 방식은 안되므로 아래 방식으로 진행
	FSoftObjectPath MyGCAsset(TEXT("/Script/GeometryCollectionEngine.GeometryCollection'/Game/2019180031/Blueprints/Map/Tile/Tile_Geometry/Tile.Tile'"));
	UGeometryCollection* MyGCData = Cast<UGeometryCollection>(MyGCAsset.ResolveObject());
	if (MyGCData == nullptr)
	{
		MyGCData = CastChecked<UGeometryCollection>(MyGCAsset.TryLoad());
	}
	
	UE_LOG(LogTemp, Warning, TEXT("여기까진 잘됨"));
	// 4. Geometry Collection Component 추가
	//UGeometryCollectionComponent* GeometryComp = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("GCComp"));
	// 위 방식이 안되므로 아래 방식으로 진행
	// https://forums.unrealengine.com/t/programmatically-spawned-geometrycollection-has-no-physics/645383/2 도움받은 링크
	UGeometryCollectionComponent* TargetGCComp;
	FTransform Transform;
	Transform.SetScale3D(FVector(0.9f, 0.9f, 0.9f));
	TargetGCComp = Cast<UGeometryCollectionComponent>(AddComponentByClass(UGeometryCollectionComponent::StaticClass(), false, Transform, true));
	TargetGCComp->SetRestCollection(MyGCData);
	FinishAddComponent(TargetGCComp, false, Transform);
	TargetGCComp->SetRestCollection(MyGCData);
	TargetGCComp->EditRestCollection(GeometryCollection::EEditUpdate::RestPhysicsDynamic, false);
	
	
	
	
}

