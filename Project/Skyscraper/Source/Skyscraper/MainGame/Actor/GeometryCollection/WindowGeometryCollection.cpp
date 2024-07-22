// Fill out your copyright notice in the Description page of Project Settings.


#include "Skyscraper/MainGame/Actor/GeometryCollection/WindowGeometryCollection.h"
#include "GeometryCollection/GeometryCollectionObject.h"
#include "Kismet/GameplayStatics.h"
#include "Skyscraper/Subsystem/SkyscraperEngineSubsystem.h"

//TArray<UObject*> AWindowGeometryCollection::GC_WindowObject;

AWindowGeometryCollection::AWindowGeometryCollection()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MaterialInterface = nullptr;

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
	//UGeometryCollection* GeometryCollectionObject = LoadObject<UGeometryCollection>(nullptr,
	//	TEXT("/Script/GeometryCollectionEngine.GeometryCollection'/Game/2019180016/FractureMesh/GC_map_3_window_001.GC_map_3_window_001'"));

	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	GCWindow = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("WindowGeometryCollection"));
	GCWindow->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	// GCWindow->SetupAttachment(RootComponent);
}

#include "Field/FieldSystemObjects.h"
void AWindowGeometryCollection::Init(uint8 WindowNum)
{
	UGeometryCollection* GC = Cast<UGeometryCollection>(GC_WindowObject[WindowNum]);
	if (GC)
	{
		GCWindow->SetRestCollection(GC);

		GCWindow->SetSimulatePhysics(true);
		GCWindow->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		GCWindow->SetCollisionProfileName(TEXT("BlockAllDynamic"));
		GCWindow->SetCollisionObjectType(ECollisionChannel::ECC_Destructible);

		GCWindow->SetPhysMaterialOverride(nullptr);

		//UFieldNodeBase FNB;
		//GCWindow->ApplyPhysicsField(true, EGeometryCollectionPhysicsTypeEnum::Chaos_LinearVelocity, nullptr, );
	}
	else
		UE_LOG(LogClass, Warning, TEXT("GC is NULLPTR"));
}

// Called when the game starts or when spawned
void AWindowGeometryCollection::BeginPlay()
{
	Super::BeginPlay();

	//2019180031
	if (USkyscraperEngineSubsystem* Subsystem = GEngine->GetEngineSubsystem<USkyscraperEngineSubsystem>())
	{
		if (USoundBase* Sound = Subsystem->GetSkyscraperSound(TEXT("WindowBreak")))
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, GetActorLocation());
		}
	}
}

// Called every frame
void AWindowGeometryCollection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWindowGeometryCollection::SetWindowObject(uint8 WindowNum)
{
	if (GC_WindowObject.IsValidIndex(WindowNum))
	{
		UGeometryCollection* GC = Cast<UGeometryCollection>(GC_WindowObject[WindowNum]);
		if (GC)
		{
			GCWindow->InitializeComponent();
			GCWindow->SetRestCollection(GC);
		}
		else
		{
			UE_LOG(LogClass, Warning, TEXT("Cast<UGeometryCollection>(GC_WindowObject[WindowNum]) Cast Failed"));
		}
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("AWindowGeometryCollection::SetWindowObject(uint8 WindowNum) IsValidIndex ERROR"));
	}
}

void AWindowGeometryCollection::AddForce(FVector Direction)
{
	GCWindow->AddForce(Direction);
}