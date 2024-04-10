// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGBullet.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ARPGBullet::ARPGBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BulletStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
	BulletStaticMesh->SetupAttachment(GetRootComponent());
	BulletStaticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Overlap);

	FireParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireParticle"));
	FireParticleComponent->SetupAttachment(BulletStaticMesh);
	SteamParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SteamParticle"));
	SteamParticleComponent->SetupAttachment(FireParticleComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	
	ProjectileMovementComponent->InitialSpeed = 3250.0f;
	ProjectileMovementComponent->MaxSpeed = 10000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bInitialVelocityInLocalSpace = true;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.001;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleRef(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	ExplodeParticle = ParticleRef.Object;

	
}

void ARPGBullet::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ARPGBullet::Initialize(FVector getInitVelocity, float getInitSpeed, float getDamage)
{
	InitVelocity = getInitVelocity;
	InitSpeed = getInitSpeed;
	Damage = getDamage;
}

// Called when the game starts or when spawned
void ARPGBullet::BeginPlay()
{
	Super::BeginPlay();

	BulletStaticMesh->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::Explode);

	ProjectileMovementComponent->Velocity = InitVelocity * InitSpeed;
}

void ARPGBullet::Explode(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TArray<AActor*> IgnoreActors;

	// == TODO: Add Self And Team Characters
	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), 100.0f, nullptr, IgnoreActors);

	// == TODO: Spawn Damage Spawner 

	// == TODO: Delete Debug Later
	DrawDebugSphere(GetWorld(), GetActorLocation(), 100.0f, 10, FColor::Black, true, 3.0f, 0, 3);

	Destroy();

}

// Called every frame
void ARPGBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

