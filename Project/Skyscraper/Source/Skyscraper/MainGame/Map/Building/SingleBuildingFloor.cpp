// Fill out your copyright notice in the Description page of Project Settings.


#include "SingleBuildingFloor.h"

#include "Skyscraper/MainGame/Map/Furniture/Furniture.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"

// Play Sound
#include "Kismet/GameplayStatics.h"
#include "Skyscraper/Subsystem/SkyscraperEngineSubsystem.h"

// Sets default values
ASingleBuildingFloor::ASingleBuildingFloor()
{
	// bCanEverTick
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(SceneComponent);
	

	ConstructorHelpers::FClassFinder<AActor> GC_BuildingRef(TEXT("/Script/Engine.Blueprint'/Game/2019180031/MainGame/Map/Building/BP_GC_Building.BP_GC_Building_C'"));
	GC_BuildingClass = GC_BuildingRef.Class;

	for (int i = 0; i < 6; i++)
	{
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
	Target->DestroyComponent();
}

#include "Kismet/KismetStringLibrary.h"
void ASingleBuildingFloor::DoCollapseWindow(UHierarchicalInstancedStaticMeshComponent* Target, int32 TargetIndex, FVector ForceDirection)
{
	if (!Target->PerInstanceSMData.IsValidIndex(TargetIndex)) return;

	FVector Translation = Target->PerInstanceSMData[TargetIndex].Transform.GetOrigin();
	FVector Scale = Target->PerInstanceSMData[TargetIndex].Transform.GetScaleVector();
	FQuat Rotation = FQuat(Target->PerInstanceSMData[TargetIndex].Transform);
	
	//auto M = Target->PerInstanceSMData[TargetIndex].Transform.M;
	//UE_LOG(LogTemp, Warning, TEXT("===== Break Window Matrix ====="));
	//UE_LOG(LogTemp, Warning, TEXT("%lf, %lf, %lf, %lf"), M[0][0], M[1][0], M[2][0], M[3][0]);
	//UE_LOG(LogTemp, Warning, TEXT("%lf, %lf, %lf, %lf"), M[0][1], M[1][1], M[2][1], M[3][1]);
	//UE_LOG(LogTemp, Warning, TEXT("%lf, %lf, %lf, %lf"), M[0][2], M[1][2], M[2][2], M[3][2]);
	//UE_LOG(LogTemp, Warning, TEXT("%lf, %lf, %lf, %lf"), M[0][3], M[1][3], M[2][3], M[3][3]);
	//UE_LOG(LogTemp, Warning, TEXT("Index Is %d"), TargetIndex);

	FTransform Transform{ Rotation, Translation, Scale };
	UE_LOG(LogTemp, Warning, TEXT("Transform is %s"), *UKismetStringLibrary::Conv_TransformToString(Transform));
	AActor* NewGCWindowMesh = GetWorld()->SpawnActorDeferred<AActor>(GC_WindowClass[0], Transform);
	if (NewGCWindowMesh)
	{
		NewGCWindowMesh->SetActorTransform(Transform);
		NewGCWindowMesh->FinishSpawning(Transform);
	
		NewGCWindowMesh->SetLifeSpan(5.0f);

		NewGCWindowMesh->AttachToComponent(Target, FAttachmentTransformRules::KeepRelativeTransform);

		//2019180031
		if (USkyscraperEngineSubsystem* Subsystem = GEngine->GetEngineSubsystem<USkyscraperEngineSubsystem>())
		{
			if (USoundBase* Sound = Subsystem->GetSkyscraperSound(TEXT("WindowBreak")))
			{
				if (USoundAttenuation* SoundAttenuation = Subsystem->GetSkyscraperSoundAttenuation())
				{
					UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, GetActorLocation(), FRotator{}, 1, 1, 0, SoundAttenuation);
				}
			}
		}
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("NewGCWindowMesh is nullptr!"));
	}
	Target->RemoveInstance(TargetIndex); 
}
