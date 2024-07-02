// Fill out your copyright notice in the Description page of Project Settings.


#include "Furniture.h"

#include "Desk.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Components/SpotLightComponent.h"

// Sets default values
AFurniture::AFurniture()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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
}

// Called every frame
void AFurniture::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

