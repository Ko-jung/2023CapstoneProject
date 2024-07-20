#include "Furniture.h"

#include "Desk.h"
#include "Components/BoxComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Components/SpotLightComponent.h"
#include "Skyscraper/Enum/EFurnitureType.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "Skyscraper/MainGame/Map/Building/Building.h"
#include "Skyscraper/MainGame/Map/Building/SingleBuildingFloor.h"

// Sets default values
AFurniture::AFurniture()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	FurnitureDissolveTime = 10.0f;
	DissolveTickTime = 0.053f;

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

	{
		static ConstructorHelpers::FObjectFinder<UMaterial> M_Dissolve_ChairRef(TEXT("/Script/Engine.Material'/Game/2019180031/MainGame/Material/FurnitureDissolve/M_Dissolve_Chair.M_Dissolve_Chair'"));
		if(M_Dissolve_ChairRef.Succeeded())
		{
			FurnitureDissolveMaterial.Add(TEXT("Chair"), M_Dissolve_ChairRef.Object);
		}

		static ConstructorHelpers::FObjectFinder<UMaterial> M_Dissolve_DeskRef(TEXT("/Script/Engine.Material'/Game/2019180031/MainGame/Material/FurnitureDissolve/M_Dissolve_Desk.M_Dissolve_Desk'"));
		if (M_Dissolve_DeskRef.Succeeded())
		{
			FurnitureDissolveMaterial.Add(TEXT("Desk"), M_Dissolve_DeskRef.Object);
		}

		static ConstructorHelpers::FObjectFinder<UMaterial> M_Dissolve_FlowerPotRef(TEXT("/Script/Engine.Material'/Game/2019180031/MainGame/Material/FurnitureDissolve/M_Dissolve_FlowerPot.M_Dissolve_FlowerPot'"));
		if (M_Dissolve_FlowerPotRef.Succeeded())
		{
			FurnitureDissolveMaterial.Add(TEXT("FlowerPot"), M_Dissolve_FlowerPotRef.Object);
		}

		static ConstructorHelpers::FObjectFinder<UMaterial> M_Dissolve_PCRef(TEXT("/Script/Engine.Material'/Game/2019180031/MainGame/Material/FurnitureDissolve/M_Dissolve_PC.M_Dissolve_PC'"));
		if (M_Dissolve_PCRef.Succeeded())
		{
			FurnitureDissolveMaterial.Add(TEXT("PC"), M_Dissolve_PCRef.Object);
		}

		static ConstructorHelpers::FObjectFinder<UMaterial> M_Dissolve_SofaTableRef(TEXT("/Script/Engine.Material'/Game/2019180031/MainGame/Material/FurnitureDissolve/M_Dissolve_Sofa_Table.M_Dissolve_Sofa_Table'"));
		if (M_Dissolve_SofaTableRef.Succeeded())
		{
			FurnitureDissolveMaterial.Add(TEXT("SofaAndTable"), M_Dissolve_SofaTableRef.Object);
		}
	}
	
}


UStaticMeshComponent* AFurniture::ChangeHISMToPhysicsSM(UHierarchicalInstancedStaticMeshComponent* HISM, int Index)
{
	int CurrentLastIndex = DummyStaticMeshComp.Num() - 1;
	UStaticMeshComponent* SMComp = DummyStaticMeshComp[CurrentLastIndex];
	DummyStaticMeshComp.RemoveAt(CurrentLastIndex);

	FTransform Transform{};
	HISM->GetInstanceTransform(Index, Transform);
	HISM->RemoveInstance(Index);
	
	SMComp->SetStaticMesh(HISM->GetStaticMesh());
	if(HISM->GetOwner()->IsA<ADesk>())
	{
		SMComp->SetWorldLocation(HISM->GetComponentLocation()  + Transform.GetLocation());
	}else
	{
		SMComp->SetWorldLocation(GetActorLocation() + Transform.GetLocation().RotateAngleAxis(GetActorRotation().Yaw, FVector{ 0.0f,0.0f,1.0f }));
	}
	
	SMComp->SetRelativeRotation(Transform.GetRotation());
	SMComp->SetHiddenInGame(false);
	SMComp->SetSimulatePhysics(true);
	if(HISM->ComponentTags.IsValidIndex(0))
	{
		SMComp->ComponentTags.Add(HISM->ComponentTags[0]);
	}
	PhysicsFurniture.Add(SMComp);

	AddToSimulateStaticMeshData(SMComp, HISM->ComponentTags);

	return SMComp;
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

bool AFurniture::CollapseByTileCollapseItem(ASkyscraperCharacter* TargetCharacter)
{
	if(IsCharacterInHere(TargetCharacter))
	{
		if(OwnerBuilding)
		{
			OwnerBuilding->CollapseBuilding(Floor);
			return true;
		}
	}
	return false;
}

void AFurniture::SetBuildingFloorInfo(ABuilding* GetBuilding, int GetFloor)
{
	OwnerBuilding = GetBuilding;
	Floor = GetFloor;
}

void AFurniture::ChangeHISMToPhysicsSMAndAddForce(UHierarchicalInstancedStaticMeshComponent* HISM, int index,
	const FVector& ForceStartLocation)
{
	UStaticMeshComponent* SimulatedMesh = ChangeHISMToPhysicsSM(HISM, index);
	if(SimulatedMesh)
	{
		FVector ForceDirection = (GetActorLocation() + SimulatedMesh->GetRelativeLocation()) - ForceStartLocation;
		ForceDirection.Normalize();
		ForceDirection *= 7000000.0f;
		SimulatedMesh->AddForce(ForceDirection);
		UE_LOG(LogTemp, Warning, TEXT("Apply Force"));
	}
}

bool AFurniture::IsCharacterInHere(ASkyscraperCharacter* TargetCharacter) const
{
	return InsidePlayers.Contains(TargetCharacter);
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

	if(ASingleBuildingFloor* SingleBuilding = Cast<ASingleBuildingFloor>(GetOwner()))
	{
		UE_LOG(LogTemp, Warning, TEXT("correct   1"));
		if(ABuilding* Building = Cast<ABuilding>(SingleBuilding->GetOwner()))
		{
			UE_LOG(LogTemp, Warning, TEXT("correct   2"));
		}
	}
	
	

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
				if (ADesk* DeskActor = Cast<ADesk>(ChildComp->GetChildActor()))
				{
					DeskActors.Add(DeskActor);
					DeskActor->SetOwner(this);
					
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

void AFurniture::DissolveFurniture()
{
	TArray<UStaticMeshComponent*> RemoveMeshes;

	for(TPair<TObjectPtr<UStaticMeshComponent>, float>& SimulatedMesh : SimulatedStaticMeshes)
	{
		if(SimulatedMesh.Key->GetRelativeLocation().Z <= -10000.0f)
		{
			RemoveMeshes.Add(SimulatedMesh.Key);
			continue;
		}
		SimulatedMesh.Value += DissolveTickTime;
		if(SimulatedMesh.Value >= FurnitureDissolveTime - 3)
		{
			// 해당 초를 넘겼다면 오브젝트 삭제 및 한개도 없다면 타이머 종료
			if (SimulatedMesh.Value >= FurnitureDissolveTime)
			{
				RemoveMeshes.Add(SimulatedMesh.Key);
				continue;
			}

			// 사라지기 전 2초가 되는 타이밍에 머테리얼 변경
			if (SimulatedMesh.Value - DissolveTickTime < FurnitureDissolveTime - 3)
			{
				if (SimulatedMesh.Key->ComponentTags.IsValidIndex(0))
				{
					if (FurnitureDissolveMaterial.Contains(SimulatedMesh.Key->ComponentTags[0]))
					{
						UMaterial* Material = *FurnitureDissolveMaterial.Find(SimulatedMesh.Key->ComponentTags[0]);
						SimulatedMesh.Key->CreateDynamicMaterialInstance(0, Material);
					}
				}
			}

			// material parameter 전달
			Cast<UMaterialInstanceDynamic>(SimulatedMesh.Key->GetMaterial(0))->SetScalarParameterValue(TEXT("DissolveValue"),  (1.0f-(FurnitureDissolveTime - SimulatedMesh.Value)/3.0f));
		}
	}

	// 지울 메쉬 지우기
	if(!RemoveMeshes.IsEmpty())
	{
		for(UStaticMeshComponent* RemoveMesh : RemoveMeshes)
		{
			if(SimulatedStaticMeshes.Contains(RemoveMesh))
			{
				SimulatedStaticMeshes.Remove(RemoveMesh);
				RemoveMesh->DestroyComponent();
			}
		}
	}


	// 만약 simulate중인 메쉬가 1개도 없다면 종료
	if(SimulatedStaticMeshes.IsEmpty())
	{
		if(FurnitureDissolveTimerHandle.IsValid())
		{
			GetWorld()->GetTimerManager().ClearTimer(FurnitureDissolveTimerHandle);
		}
	}
}

void AFurniture::AddToSimulateStaticMeshData(UStaticMeshComponent* TargetStaticMesh, TArray<FName> HISM_Tags)
{
	SimulatedStaticMeshes.Add(TargetStaticMesh, 0);

	if (!SimulatedStaticMeshes.IsEmpty())
	{
		if (!FurnitureDissolveTimerHandle.IsValid())
		{
			GetWorld()->GetTimerManager().SetTimer(FurnitureDissolveTimerHandle, this, &ThisClass::DissolveFurniture, DissolveTickTime, true, DissolveTickTime);
		}
	}
	
}
