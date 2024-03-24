// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystemComponent.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"

// Sets default values for this component's properties
UCombatSystemComponent::UCombatSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCombatSystemComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ASkyscraperCharacter>(GetOwner());

	// ...
	
}


// Called every frame
void UCombatSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

