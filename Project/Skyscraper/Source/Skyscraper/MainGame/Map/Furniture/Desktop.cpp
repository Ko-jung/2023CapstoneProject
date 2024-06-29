// Fill out your copyright notice in the Description page of Project Settings.


#include "Desktop.h"

// Sets default values
ADesktop::ADesktop()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ADesktop::BeginPlay()
{
	Super::BeginPlay();

	GetComponents<UStaticMeshComponent>(Desktops);	
}

// Called every frame
void ADesktop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

