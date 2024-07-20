// Fill out your copyright notice in the Description page of Project Settings.


#include "Shield.h"

// Sets default values
AShield::AShield()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShield::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShield::GetDamage(float Damage)
{
	if(SpawnCharacter)
		SpawnCharacter->GetShieldDamage(Damage);
}

void AShield::SetSpawnCharacter(AShieldCharacter* Character)
{
	SpawnCharacter = Character; 

	if (Tags.IsEmpty())
	{
		Tags.Add(SpawnCharacter->Tags[0]);
	}
}
