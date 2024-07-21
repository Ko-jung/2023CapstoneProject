// Fill out your copyright notice in the Description page of Project Settings.


#include "SingleBuildingFloor.h"

#include "Skyscraper/MainGame/Map/Furniture/Furniture.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"

// Sets default values
ASingleBuildingFloor::ASingleBuildingFloor()
{
	// bCanEverTick
	PrimaryActorTick.bCanEverTick = false;


	ConstructorHelpers::FClassFinder<AActor> GC_BuildingRef(TEXT("/Script/Engine.Blueprint'/Game/2019180031/MainGame/Map/Building/BP_GC_Building.BP_GC_Building_C'"));
	GC_BuildingClass = GC_BuildingRef.Class;

	ConstructorHelpers::FClassFinder<AActor> GCWindowActorRef(TEXT("/Script/Engine.Blueprint'/Game/2019180016/FractureMesh/BP_WindowGeometryCollection.BP_WindowGeometryCollection_C'"));
	BPGCWindowActorClass = GCWindowActorRef.Class;

	for (int i = 0; i < 6; i++)
	{

		// FString NewGCWindowString = "GC_map_3_window_00";
		// FString FilePath = "/Script/GeometryCollectionEngine.GeometryCollection'/Game/2019180016/FractureMesh/" + NewGCWindowString + FString::FromInt(i + 1) + "." + NewGCWindowString + FString::FromInt(i + 1) + "_C'";
		// //                  /Script/GeometryCollectionEngine.GeometryCollection'/Game/2019180016/FractureMesh/GC_map_3_window_001.GC_map_3_window_001'

		FString NewGCWindowString = "BP_GC_map_3_window_00";
		FString FilePath = "/Script/Engine.Blueprint'/Game/2019180016/FractureMesh/" + NewGCWindowString + FString::FromInt(i + 1) + "." + NewGCWindowString + FString::FromInt(i + 1) + "_C'";
		//					/Script/Engine.Blueprint'/Game/2019180016/FractureMesh/BP_GC_map_3_window_001.BP_GC_map_3_window_001'
		ConstructorHelpers::FClassFinder<AActor> GC_WindowRef(*FilePath);
		GC_WindowClass.Add(GC_WindowRef.Class);
	}

}


// Called when the game starts or when spawned
void ASingleBuildingFloor::BeginPlay()
{
	Super::BeginPlay();

	// 가구 액터 로드
	{
		if(UChildActorComponent* ChildActor = GetComponentByClass<UChildActorComponent>())
		{
			FurnitureActor = Cast<AFurniture>(ChildActor->GetChildActor());
			if (FurnitureActor)
			{
				UE_LOG(LogTemp, Warning, TEXT("load complete"));
			}
		}
		
	}
	
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
	if (NewGCTileActor)
	{
		NewGCTileActor->SetActorLocation(GetActorLocation());
		NewGCTileActor->SetActorRotation(GetActorRotation());
		NewGCTileActor->FinishSpawning(Transform);
	}

	Destroy();
}

void ASingleBuildingFloor::DoCollapseWindow(UStaticMeshComponent* Target, FVector ForceDirection)
{
	FString WindowString = Target->GetName();
	int Index = FCString::Atoi(&(*WindowString.rbegin()));

	FTransform Transform{ Target->GetComponentRotation(), Target->GetComponentLocation() };
	AActor* NewGCWindowMesh = GetWorld()->SpawnActorDeferred<AActor>(GC_WindowClass[Index], Transform);
	if (NewGCWindowMesh)
	{
		NewGCWindowMesh->SetActorLocation(GetActorLocation());
		NewGCWindowMesh->SetActorRotation(GetActorRotation());
		NewGCWindowMesh->FinishSpawning(Transform);

		NewGCWindowMesh->SetLifeSpan(5.0f);
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("NewGCWindowMesh is nullptr!"));
	}

	// AActor* NewGCWindowMesh = GetWorld()->SpawnActorDeferred<AActor>(GC_WindowClass[Index], Transform);
	// if (NewGCWindowMesh)
	// {
	// 	NewGCWindowMesh->SetActorLocation(GetActorLocation());
	// 	NewGCWindowMesh->SetActorRotation(GetActorRotation());
	// 	NewGCWindowMesh->FinishSpawning(Transform);
	// 
	// 	NewGCWindowMesh->SetLifeSpan(5.0f);
	// }
	Target->DestroyComponent();



	//for (const auto& pWindow : WindowStaticMeshes)
	//{
	//	if (pWindow == Target)
	//	{
	//		// /Script/GeometryCollectionEngine.GeometryCollection'/Game/2019180016/FractureMesh/GC_map_3_window_001.GC_map_3_window_001'

	//		FString WindowString = pWindow->GetName();
	//		int Index = (*WindowString.rbegin());

	//		FTransform Transform{ pWindow->GetComponentRotation(), pWindow->GetComponentLocation() };
	//		auto NewGCWindowMesh = GetWorld()->SpawnActorDeferred<UGeometryCollection>(GC_WindowClass[Index], Transform);
	//		if (NewGCWindowMesh)
	//		{
	//			NewGCWindowMesh->Location(GetActorLocation());
	//			NewGCWindowMesh->SetActorRotation(GetActorRotation());
	//			NewGCWindowMesh->FinishSpawning(Transform);
	//		}
	//		pWindow->DestroyComponent();
	//		

	//		//FString NewGCWindowString = FString("GC_") + WindowString;
	//		//FString FilePath = "/Script/GeometryCollectionEngine.GeometryCollection'/Game/2016180016/FractureMesh/" + NewGCWindowString + "." + NewGCWindowString + "'";
	//		//
	//		//ConstructorHelpers::FObjectFinder<AGeometryCollectionActor>WindowMeshRef(*FilePath);
	//		//if (WindowMeshRef.Succeeded())
	//		//{
	//		//}
	//		//else
	//		//{
	//		//	UE_LOG(LogClass, Warning, TEXT("WindowMeshRef Cant find"));
	//		//}

	//		break;
	//	}
	//}
}
#include "Kismet/KismetStringLibrary.h"
void ASingleBuildingFloor::DoCollapseWindow(UHierarchicalInstancedStaticMeshComponent* Target, int32 TargetIndex, FVector ForceDirection)
{
	if (!Target->PerInstanceSMData.IsValidIndex(TargetIndex)) return;

	FVector Translation = Target->PerInstanceSMData[TargetIndex].Transform.GetOrigin();
	FVector Scale = Target->PerInstanceSMData[TargetIndex].Transform.GetScaleVector();
	FQuat Rotation = FQuat(Target->PerInstanceSMData[TargetIndex].Transform);
	//FRotator Rotation = Target->PerInstanceSMData[TargetIndex].Transform.Rotator();
	
	//auto M = Target->PerInstanceSMData[TargetIndex].Transform.M;
	//UE_LOG(LogTemp, Warning, TEXT("===== Break Window Matrix ====="));
	//UE_LOG(LogTemp, Warning, TEXT("%lf, %lf, %lf, %lf"), M[0][0], M[1][0], M[2][0], M[3][0]);
	//UE_LOG(LogTemp, Warning, TEXT("%lf, %lf, %lf, %lf"), M[0][1], M[1][1], M[2][1], M[3][1]);
	//UE_LOG(LogTemp, Warning, TEXT("%lf, %lf, %lf, %lf"), M[0][2], M[1][2], M[2][2], M[3][2]);
	//UE_LOG(LogTemp, Warning, TEXT("%lf, %lf, %lf, %lf"), M[0][3], M[1][3], M[2][3], M[3][3]);
	//UE_LOG(LogTemp, Warning, TEXT("Index Is %d"), TargetIndex);

	FTransform Transform{ Rotation, Translation, Scale };
	UE_LOG(LogTemp, Warning, TEXT("Transform is %s"), *UKismetStringLibrary::Conv_TransformToString(Transform));
	AActor* NewGCWindowMesh = GetWorld()->SpawnActorDeferred<AActor>(GC_WindowClass[3], Transform);
	if (NewGCWindowMesh)
	{
		//NewGCWindowMesh->SetActorLocation(GetActorLocation());
		//NewGCWindowMesh->SetActorRotation(GetActorRotation());
		NewGCWindowMesh->SetActorTransform(Transform);
		NewGCWindowMesh->FinishSpawning(Transform);
	
		NewGCWindowMesh->SetLifeSpan(5.0f);

		NewGCWindowMesh->AttachToComponent(Target, FAttachmentTransformRules::KeepRelativeTransform);
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("NewGCWindowMesh is nullptr!"));
	}
	Target->RemoveInstance(TargetIndex); 
}
