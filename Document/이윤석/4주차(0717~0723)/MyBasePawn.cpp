// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBasePawn.h"

#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AMyBasePawn::AMyBasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

// Called when the game starts or when spawned
void AMyBasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyBasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyBasePawn::RotateTurret(FVector LookAtTarget) const
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(),
		LookAtRotation,
		UGameplayStatics::GetWorldDeltaSeconds(this),
		10.0f));
}

void AMyBasePawn::Fire()
{
	//DrawDebugSphere(
	//	GetWorld(), 
	//	ProjectileSpawnPoint->GetComponentLocation(),
	//	10.0f, 16,
	//	FColor::Red,
	//	false,
	//	3.0f
	//);

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileClass,
		ProjectileSpawnPoint->GetComponentLocation(),
		ProjectileSpawnPoint->GetComponentRotation()
	);
	Projectile->SetOwner(this);
}
