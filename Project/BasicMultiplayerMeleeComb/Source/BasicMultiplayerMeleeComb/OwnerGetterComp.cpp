// Fill out your copyright notice in the Description page of Project Settings.


#include "OwnerGetterComp.h"

#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UOwnerGetterComp::UOwnerGetterComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UOwnerGetterComp::BeginPlay()
{
	Super::BeginPlay();

	OwnerClass = GetOwner()->GetClass();
	FString dn = OwnerClass->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s"),*dn);
	
	// ...
	
}


// Called every frame
void UOwnerGetterComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

APlayerController* UOwnerGetterComp::GetOwnerPlayerController()
{
	
	return nullptr;
}

UCameraComponent* UOwnerGetterComp::GetOwnerCameraComponent()
{
	return nullptr;
}

USkeletalMeshComponent* UOwnerGetterComp::GetCharacterMesh()
{
	return nullptr;
}

USpringArmComponent* UOwnerGetterComp::GetOwnerSpringArmComponent()
{
	return nullptr;
}

