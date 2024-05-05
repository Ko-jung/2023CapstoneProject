// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "Skyscraper/MainGame/Actor/Bullet/RPGBullet.h"

URPGComponent::URPGComponent()
{
	AnimMontageKey = ECharacterAnimMontage::ECAM_RPG;

	

	ReloadMaxCoolTime = 5.0f;
	BulletMaxCount = 5;
	FireMaxCoolTime = 1.0f;
	ReloadSpeedTime = 5.0f;

	RecoilAboveAmount = 1.0f;
	RecoilBesideAmount = 0.5f;
	RecoilTime = 0.1f;
	RecoilSpeed = 20.0f;

	{ // �Ѿ� ���� �ε�s
		static ConstructorHelpers::FClassFinder<ARPGBullet> RPGBulletBPRef(TEXT("/Script/Engine.Blueprint'/Game/2019180031/MainGame/Actor/BP_RPGBullet.BP_RPGBullet_C'"));
		RPGBulletBPClass = RPGBulletBPRef.Class;
	}
	
	{ // ���� ���� �ε� 
		WeaponSocketName = TEXT("RPGSocket");
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> RPGSkeletalMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/weapon/gun/rpg.rpg'"));
		WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RPG Weapon"));
		WeaponMeshComponent->SetSkeletalMesh(RPGSkeletalMeshRef.Object);
	}

	
	
	
}

void URPGComponent::Fire(float fBaseDamage)
{
	if (!GetOwnerPlayerController()) return;

	UseBullet();

	fBaseDamage *= OwnerCharacter->GetPowerBuffValue();

	FVector SpawnLocation = OwnerCharacter->GetActorLocation();

	FVector BulletDestination = GetOwnerPlayerController()->GetControlRotation().Vector() * 8000.0f  
								+ OwnerCharacter->GetCameraBoom()->GetComponentLocation();

	FVector Direction = (BulletDestination - OwnerCharacter->GetActorLocation());
	Direction.Normalize();
	FVector Location = OwnerCharacter->GetActorLocation() + 
						Direction * 100;
	

	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	//AActor* BulletActor = GetWorld()->SpawnActor<ARPGBullet>(RPGBulletBPClass,Location, Rotation, SpawnInfo);
	FTransform SpawnTransform{};
	SpawnTransform.SetLocation(Location);
	SpawnTransform.SetRotation(Rotation.Quaternion());
	SpawnTransform.SetScale3D(FVector(1.0f, 1.0f, 1.0f));

	ARPGBullet* BulletActor = GetWorld()->SpawnActorDeferred<ARPGBullet>(RPGBulletBPClass, SpawnTransform);
	if(BulletActor)
	{

		BulletActor->Initialize(OwnerCharacter, Direction, 5000.0f, fBaseDamage);
		BulletActor->FinishSpawning(SpawnTransform);
	}
	//UBlueprint* BulletObject = Cast<UBlueprint>()
}
