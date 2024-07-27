// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGBullet.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

#include "GameFramework/Character.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Skyscraper/MainGame/Component/Damage/DamageComponent.h"

#include "Skyscraper/Network/MainGameMode.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Skyscraper/MainGame/Map/Building/SingleBuildingFloor.h"
#include "Skyscraper/MainGame/Map/Furniture/Desk.h"
#include "Skyscraper/MainGame/Map/Furniture/Furniture.h"
#include "Skyscraper/Subsystem/SkyscraperEngineSubsystem.h"

#include "Skyscraper/MainGame/Actor/SkillActor/Shield.h"

typedef UHierarchicalInstancedStaticMeshComponent UHISM;

// Sets default values
ARPGBullet::ARPGBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BulletStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
	BulletStaticMesh->SetupAttachment(GetRootComponent());
	BulletStaticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Overlap);

	NS_RPG = CreateDefaultSubobject<UNiagaraComponent>(TEXT("RPGNiagaraSystem"));
	NS_RPG->SetupAttachment(BulletStaticMesh);

	{
		static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_ExplosionRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/2019180031/MainGame/Fbx/Explosion/NS_Explosion.NS_Explosion'"));
		NS_Explosion = NS_ExplosionRef.Object;
	}
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	
	ProjectileMovementComponent->InitialSpeed = 3250.0f;
	ProjectileMovementComponent->MaxSpeed = 10000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bInitialVelocityInLocalSpace = true;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.001;

	EffectiveDistance = 8000.0f;
	CurrentDistance = 0.0f;


}

void ARPGBullet::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ARPGBullet::Initialize(AActor* getFireCharacter, FVector getInitVelocity, float getInitSpeed, float getDamage)
{
	FireCharacter = getFireCharacter;
	InitVelocity = getInitVelocity;
	InitSpeed = getInitSpeed;
	Damage = getDamage;
}



// Called when the game starts or when spawned
void ARPGBullet::BeginPlay()
{
	Super::BeginPlay();

	BulletStaticMesh->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OverlapExplode);
	BulletStaticMesh->OnComponentHit.AddDynamic(this, &ThisClass::HitExplode);

	ProjectileMovementComponent->Velocity = InitVelocity * InitSpeed;
}

void ARPGBullet::BulletExplode()
{
	TArray<AActor*> IgnoreActors;
	// == TODO: Add Self And Team Characters

	IgnoreActors.Add(FireCharacter);

	//UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), 100.0f, nullptr, IgnoreActors);

	AMainGameMode* GameMode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(this));

	TArray<FHitResult> Hits;
	bool IsHit = UKismetSystemLibrary::SphereTraceMulti(this, GetActorLocation(), GetActorLocation(), 350.f,
		UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Pawn), false, IgnoreActors, EDrawDebugTrace::None, Hits, true);

	bool IsHitShield{ false };
	TArray<AActor*> UniqueActors;
	for (const auto& HitResult : Hits)
	{
		AActor* HitActor = HitResult.GetActor();
		if (Cast<ASkyscraperCharacter>(FireCharacter)->IsAlliance(HitActor)) continue;

		if (HitActor->IsA(ACharacter::StaticClass()) && !UniqueActors.Contains(HitActor))
		{
			UniqueActors.Add(HitActor);
			continue;
		}
		else if (AShield* Shield = Cast<AShield>(HitActor))
		{
			GameMode->SendDamagedSkillActor(FireCharacter, Shield->SpawnCharacter, ESkillActor::BP_Shield, Shield);
			IsHitShield = true;
		}
	}

	if (!IsHitShield)
	{
		int i = 0;
		for (const auto& a : UniqueActors)
		{
			if (GameMode)
			{
				GameMode->SendTakeDamage(FireCharacter, a);
			}

			if (ASkyscraperCharacter* Character = Cast<ASkyscraperCharacter>(a))
			{
				FVector DownDirVector{};
				DownDirVector = Character->GetActorLocation() - GetActorLocation();
				//2019180031 DownDirection은 normal vector
				DownDirVector.Normalize();
				Character->DoDown(FireCharacter, DownDirVector);

				// == Spawn Damage (Local)
				{
					if (GetWorld()->GetFirstPlayerController()->GetPawn() == FireCharacter)
					{
						FTransform SpawnTransform{};
						SpawnTransform.SetLocation(Character->GetActorLocation());
						if (!Character->IsCharacterGodMode())
						{
							UDamageComponent* DamageComp = Cast<UDamageComponent>(Character->AddComponentByClass(UDamageComponent::StaticClass(), true, SpawnTransform, false));
							if (DamageComp)
							{
								DamageComp->InitializeDamage(Damage);
							}
						}
					
					}

				}
			}
		}
	}



	TArray<FHitResult> UniqueOutHitsComponent;		// To Break Window
	TArray<UPrimitiveComponent*> OutHitComponent;
	TArray<int32> HISMIndex;
	bool IsComponentHit = UKismetSystemLibrary::SphereTraceMulti(this, GetActorLocation(), GetActorLocation(), 350.f,
		UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_WorldDynamic), false, IgnoreActors, EDrawDebugTrace::None, Hits, true);

	for (const auto& HitResult : Hits)
	{
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		if (HitComponent->IsA(UHISM::StaticClass())
			//&& !OutHitComponent.Contains(HitComponent)
			&& HitComponent->GetName() == ("HISM_Window"))
		{
			OutHitComponent.Add(HitComponent);

			if (GameMode)
			{
				GameMode->SendBreakObject(FireCharacter, HitComponent, HitResult.Item, EObjectType::Window);
			}
			else
			{
				//HISMWindow->RemoveInstance(HISMIndex[i]);
			}
		}

		// 2019180031
		// 가구가 바주카포에 맞을 경우 simulate 되도록
		if (UHierarchicalInstancedStaticMeshComponent* HISM = Cast<UHierarchicalInstancedStaticMeshComponent>(HitResult.GetComponent()))
		{
			if(AFurniture* HitFurnitureActor = Cast<AFurniture>(HitResult.GetActor()))
			{
				HitFurnitureActor->ChangeHISMToPhysicsSMAndAddForce(HISM, HitResult.Item, GetActorLocation());
			}
			else if(ADesk* DeskActor = Cast<ADesk>(HitResult.GetActor()))
			{
				AFurniture* FurnitureActor = Cast<AFurniture>(DeskActor->GetOwner());
				FurnitureActor->ChangeHISMToPhysicsSMAndAddForce(HISM, HitResult.Item, GetActorLocation());
			}
			continue;
		}

		// 만약 simulate 되는 오브젝트일 경우 또다시 addforce 되도록
		if(UStaticMeshComponent* SM = Cast<UStaticMeshComponent>(HitResult.GetComponent()))
		{
			if (SM->GetOwner()->IsA(AShield::StaticClass()) ||						// Ignore Shield Mesh
				SM->GetOwner()->IsA(ASkyscraperCharacter::StaticClass())) return;	// Ignore Skirt Mesh

			FVector ForceDirection = (HitResult.GetActor()->GetActorLocation() + SM->GetRelativeLocation()) - GetActorLocation();
			ForceDirection.Normalize();
			ForceDirection *= 7000000.0f;
			SM->AddForce(ForceDirection);
		}
		
	}

	{
		if(NS_Explosion)
		{
			InitVelocity.Normalize();
			UNiagaraComponent* FX = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
				GetWorld(), NS_Explosion,
				GetActorLocation(), GetActorRotation(), GetActorScale()*5);

			
		}
	}


	if (USkyscraperEngineSubsystem* Subsystem = GEngine->GetEngineSubsystem<USkyscraperEngineSubsystem>())
	{
		if (USoundBase* Sound = Subsystem->GetSkyscraperSound(TEXT("RPG_Explosion")))
		{
			if (USoundAttenuation* SoundAttenuation = Subsystem->GetSkyscraperSoundAttenuation())
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, GetActorLocation(), FRotator{}, 1, 1, 0, SoundAttenuation);
			}
		}
	}

	Destroy();
}

void ARPGBullet::OverlapExplode(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 서버 TODO : 적군 캐릭터에만 되도록 수정 바람
	// ->	UniqueActor 배열 제작하면서 
	//		if (Cast<ASkyscraperCharacter>(FireCharacter)->IsAlliance(HitActor)) continue;
	//		으로 적군만 추가하게끔 수정

	if(OtherActor->IsA<ASkyscraperCharacter>())
	{
		BulletExplode();
	}
	
}

void ARPGBullet::HitExplode(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	BulletExplode();
}

// Called every frame
void ARPGBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CurrentDistance += DeltaTime * GetVelocity().Length();
	FVector Direction = GetVelocity();
	Direction.Normalize();
	NS_RPG->SetVariableVec3(TEXT("Direction"), Direction);
	if(CurrentDistance >= EffectiveDistance)
	{
		BulletExplode();
	}
}

