// Fill out your copyright notice in the Description page of Project Settings.


#include "Furniture.h"

#include "Desktop.h"

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
		GetComponents<UStaticMeshComponent>(FurnitureObjects);

		// 책상 child actor component
		{
			TArray<TObjectPtr<UChildActorComponent>> DeskChildActorComponents; GetComponents<UChildActorComponent>(DeskChildActorComponents);
			for (UChildActorComponent* ChildComp : DeskChildActorComponents)
			{
				if (ADesktop* Desktop = Cast<ADesktop>(ChildComp->GetChildActor()))
				{
					DeskActors.Add(Desktop);
				}
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("가구 갯수: %d"), FurnitureObjects.Num());
	UE_LOG(LogTemp, Warning, TEXT("데스크톱 개수: %d"), DeskActors.Num());
	
}

// Called every frame
void AFurniture::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

