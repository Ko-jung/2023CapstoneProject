// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "Skyscraper/MainGame/Actor/Bullet/RPGBullet.h"

URPGComponent::URPGComponent()
{
	FireAnimMontageKey = ECharacterAnimMontage::ECAM_RPGFire;
	ReloadAnimMontageKey = ECharacterAnimMontage::ECAM_RPGReload;

	

	ReloadMaxCoolTime = 5.0f;
	BulletMaxCount = 5;
	FireMaxCoolTime = 1.0f;
	ReloadSpeedTime = 5.0f;

	RecoilAboveAmount = 1.0f;
	RecoilBesideAmount = 0.5f;
	RecoilTime = 0.1f;
	RecoilSpeed = 20.0f;

	static ConstructorHelpers::FClassFinder<ARPGBullet> RPGBulletBPRef(TEXT("/Script/Engine.Blueprint'/Game/2019180031/MainGame/Actor/BP_RPGBullet.BP_RPGBullet_C'"));
	RPGBulletBPClass = RPGBulletBPRef.Class;
	
}

void URPGComponent::Fire(float fBaseDamage)
{
	if (!GetOwnerPlayerController()) return;
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

		BulletActor->Initialize(Direction, 5000.0f, fBaseDamage);
		BulletActor->FinishSpawning(SpawnTransform);
	}
	//UBlueprint* BulletObject = Cast<UBlueprint>()
}
