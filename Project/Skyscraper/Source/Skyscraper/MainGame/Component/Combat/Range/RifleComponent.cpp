// Fill out your copyright notice in the Description page of Project Settings.


#include "RifleComponent.h"

URifleComponent::URifleComponent()
{
	AnimMontageKey = ECharacterAnimMontage::ECAM_Rifle;
	

	ReloadMaxCoolTime = 5.0f;
	BulletMaxCount = 20;
	FireMaxCoolTime = 0.3f;
	ReloadSpeedTime = 3.0f;

	RecoilAboveAmount = 1.0f;
	RecoilBesideAmount = 0.5f;
	RecoilTime = 0.1f;
	RecoilSpeed = 20.0f;

	
	
	
	WeaponSocketName = TEXT("RifleSocket");

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> RifleSkeletalMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/weapon/gun/ar.ar'"));
	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Rifle Weapon"));
	WeaponMeshComponent->SetSkeletalMesh(RifleSkeletalMeshRef.Object);
}

void URifleComponent::BeginPlay()
{
	Super::BeginPlay();
}
