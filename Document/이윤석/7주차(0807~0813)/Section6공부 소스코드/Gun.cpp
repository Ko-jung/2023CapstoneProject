// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	GunMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	GunMeshComponent->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGun::PullTrigger()
{
	UE_LOG(LogTemp, Warning, TEXT("You've been Shot"));

	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, GunMeshComponent, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, GunMeshComponent, TEXT("MuzzleFlashSocket"));
	FHitResult HitResult;
	FVector ShotDirection;
	bool bIsHit = GunTrace(HitResult, ShotDirection);
	if(bIsHit)
	{
		//DrawDebugPoint(GetWorld(), HitResult.Location, 20, FColor::Red, true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitFlash, HitResult.Location, ShotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, HitResult.Location,FRotator(0),0.5);
		if(HitResult.GetActor())
		{
			FPointDamageEvent DamageEvent(Damage, HitResult, ShotDirection, nullptr);
			TObjectPtr<AController> OwnerController = GetOwnerController();
			HitResult.GetActor()->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
	

	//DrawDebugCamera(GetWorld(), Location,Rotation, 90.0f, 2.0f, FColor::Red,true );
}


// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGun::GunTrace(FHitResult& OutHitResult, FVector& ShotDirection)
{
	TObjectPtr<AController> OwnerController = GetOwnerController();
	if (!OwnerController) return false;
	FVector Location = GetActorLocation();
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	ShotDirection = -Rotation.Vector();

	FVector End = Location + Rotation.Vector() * MaxRange;
	//TODO: LineTrace
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	
	
	return GetWorld()->LineTraceSingleByChannel(OutHitResult, Location, End, ECC_GameTraceChannel1, Params);
}

TObjectPtr<AController> AGun::GetOwnerController() const
{
	TObjectPtr<APawn> OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return nullptr;
	AController* OwnerController = OwnerPawn->GetController();
	return OwnerController;
}
