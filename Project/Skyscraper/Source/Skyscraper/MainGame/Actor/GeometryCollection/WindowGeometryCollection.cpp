// Fill out your copyright notice in the Description page of Project Settings.


#include "Skyscraper/MainGame/Actor/GeometryCollection/WindowGeometryCollection.h"

TArray<UObject*> AWindowGeometryCollection::GC_WindowObject;

AWindowGeometryCollection::AWindowGeometryCollection()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (GC_WindowObject.IsEmpty())
	{
		for (int i = 0; i < 6; i++)
		{
			FString NewGCWindowString = "GC_map_3_window_00";
			FString FilePath = "/Script/GeometryCollectionEngine.GeometryCollection'/Game/2019180016/FractureMesh/" + NewGCWindowString + FString::FromInt(i + 1) + "." + NewGCWindowString + FString::FromInt(i + 1) + "'";
			//                  /Script/GeometryCollectionEngine.GeometryCollection'/Game/2019180016/FractureMesh/GC_map_3_window_001.GC_map_3_window_001'

			// Geometry Collection 로드
			ConstructorHelpers::FObjectFinder<UObject> GC_WindowRef(*FilePath);
			if (GC_WindowRef.Succeeded())
			{
				TObjectPtr<UObject> object = GC_WindowRef.Object;
				if (object)
				{
					GC_WindowObject.Add(object);
				}
				else
				{
					UE_LOG(LogClass, Warning, TEXT("Geometry Collection 로드 실패: %s"), *FilePath);
				}
			}
			else
			{
				UE_LOG(LogClass, Warning, TEXT("Geometry Collection 로드 실패: %s"), *FilePath);
			}
		}
	}

	GCWindow = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("WindowGeometryCollection"));
}

// Called when the game starts or when spawned
void AWindowGeometryCollection::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWindowGeometryCollection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWindowGeometryCollection::SetWindowObject(uint8 WindowNum)
{
	if (0 <= WindowNum  && WindowNum < GC_WindowObject.Num())
	{
		GCWindow = Cast<UGeometryCollectionComponent>(GC_WindowObject[WindowNum]);
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("AWindowGeometryCollection::SetWindowObject(uint8 WindowNum) 범위 ERROR"));
	}
}

