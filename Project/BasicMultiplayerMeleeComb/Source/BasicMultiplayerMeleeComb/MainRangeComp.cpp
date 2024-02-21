// Fill out your copyright notice in the Description page of Project Settings.


#include "MainRangeComp.h"
#include "OwnerGetterComp.h"


// Sets default values for this component's properties
UMainRangeComp::UMainRangeComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//OwnerGetterComp = NewObject<UOwnerGetterComp>(this, UOwnerGetterComp::StaticClass(), FName("OwnerGetterComp"));

	// ...
}


// Called when the game starts
void UMainRangeComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMainRangeComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

