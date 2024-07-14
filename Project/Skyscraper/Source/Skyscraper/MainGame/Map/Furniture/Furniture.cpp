// Fill out your copyright notice in the Description page of Project Settings.


#include "Furniture.h"

#include "Desk.h"
#include "Components/BoxComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Components/SpotLightComponent.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"

// Sets default values
AFurniture::AFurniture()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Sofa + Table + Flowerpot + Desk([Desk, Chair, Monitor, Partition, Desktop], 7 desks, 5 group)
	int NumberOfFurniture = 5 + 2 + 4 + (5 * 7 * 5);
	for(int i =0; i<NumberOfFurniture; ++i)
	{
		FString NameString = "PhysicsStaticMesh" + FString::FromInt(i);
		UStaticMeshComponent* TempStaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(FName(NameString));
		TempStaticMeshComp->SetMobility(EComponentMobility::Type::Movable);
		TempStaticMeshComp->SetupAttachment(GetRootComponent());
		TempStaticMeshComp->SetHiddenInGame(true);
		DummyStaticMeshComp.Add(TempStaticMeshComp);
	}
}


void AFurniture::ChangeHISMToPhysicsSM(UHierarchicalInstancedStaticMeshComponent* HISM, int Index)
{
	int CurrentLastIndex = DummyStaticMeshComp.Num() - 1;
	UStaticMeshComponent* SMComp = DummyStaticMeshComp[CurrentLastIndex];
	DummyStaticMeshComp.RemoveAt(CurrentLastIndex);

	FTransform Transform{};
	HISM->GetInstanceTransform(Index, Transform);
	HISM->RemoveInstance(Index);
	
	SMComp->SetStaticMesh(HISM->GetStaticMesh());
	SMComp->SetWorldLocation(HISM->GetComponentLocation() + Transform.GetLocation());
	SMComp->SetRelativeRotation(Transform.GetRotation());
	SMComp->SetHiddenInGame(false);
	SMComp->SetSimulatePhysics(true);
	PhysicsFurniture.Add(SMComp);
}

void AFurniture::AllHISMToPhysicsSM(UHierarchicalInstancedStaticMeshComponent* HISM)
{
	int InstanceCount = HISM->GetInstanceCount();

	for(int i =0; i< InstanceCount; ++i)
	{
		ChangeHISMToPhysicsSM(HISM, 0);
	}

	HISM->DestroyComponent();
}

void AFurniture::DoCollapse()
{
	// 모든 HISM 오브젝트
	AllHISMToPhysicsSM(HISM_Sofa);
	AllHISMToPhysicsSM(HISM_Table);
	AllHISMToPhysicsSM(HISM_Flowerpot);

	// 책상 액터
	for(ADesk* DeskActor : DeskActors)
	{
		AllHISMToPhysicsSM(DeskActor->HISM_Chair);
		AllHISMToPhysicsSM(DeskActor->HISM_Desk);
		AllHISMToPhysicsSM(DeskActor->HISM_Desktop);
		AllHISMToPhysicsSM(DeskActor->HISM_Monitor);
		AllHISMToPhysicsSM(DeskActor->HISM_Partition);
	}
}

void AFurniture::SettingSpotLight()
{
	bool NewHiddenInGame = true;
	if(!InsidePlayers.IsEmpty())
	{
		NewHiddenInGame = false;
	}

	for (USpotLightComponent* SpotLightComponent : SpotLights)
	{
		SpotLightComponent->SetHiddenInGame(NewHiddenInGame);
	}
}


void AFurniture::BoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!InsidePlayers.Contains(OtherActor))
	{
		if(ASkyscraperCharacter* Character = Cast<ASkyscraperCharacter>(OtherActor))
		{
			InsidePlayers.Add(Character);
		}
	}

	SettingSpotLight();
	
}

void AFurniture::BoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if(InsidePlayers.Contains(OtherActor))
	{
		InsidePlayers.Remove(OtherActor);
	}
	SettingSpotLight();
}

void AFurniture::FindStartOverlapActors()
{
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	BoxCollision->GetOverlappingActors(InsidePlayers, ASkyscraperCharacter::StaticClass());
	SettingSpotLight();
}


// Called when the game starts or when spawned
void AFurniture::BeginPlay()
{
	Super::BeginPlay();

	// 컴퍼넌트 로드
	{
		// 가구 static mesh
		HISM_Sofa = Cast<UHierarchicalInstancedStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("HISM_Sofa1")));
		HISM_Table = Cast<UHierarchicalInstancedStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("HISM_Table1")));
		HISM_Flowerpot = Cast<UHierarchicalInstancedStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("HISM_Flowerpot1")));

		SpotLights.Add(Cast<USpotLightComponent>(GetDefaultSubobjectByName(TEXT("SpotLight1"))));
		SpotLights.Add(Cast<USpotLightComponent>(GetDefaultSubobjectByName(TEXT("SpotLight2"))));

		BoxCollision = (Cast<UBoxComponent>(GetDefaultSubobjectByName(TEXT("Box"))));
		BoxCollision->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::BoxBeginOverlap);
		BoxCollision->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::BoxEndOverlap);

		// 책상 child actor component
		{
			TArray<TObjectPtr<UChildActorComponent>> DeskChildActorComponents; GetComponents<UChildActorComponent>(DeskChildActorComponents);
			for (UChildActorComponent* ChildComp : DeskChildActorComponents)
			{
				if (ADesk* Desktop = Cast<ADesk>(ChildComp->GetChildActor()))
				{
					DeskActors.Add(Desktop);
				}
			}
		}
	}

	GetWorld()->GetTimerManager().SetTimer(StartOverlapTimerHandle, this, &ThisClass::FindStartOverlapActors, 0.1f, false, 0.2f);
}

// Called every frame
void AFurniture::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

