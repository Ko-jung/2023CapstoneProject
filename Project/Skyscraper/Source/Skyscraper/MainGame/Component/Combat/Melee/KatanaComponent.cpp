// Fill out your copyright notice in the Description page of Project Settings.


#include "KatanaComponent.h"

UKatanaComponent::UKatanaComponent()
{
	AnimMontageKey = ECharacterAnimMontage::ECAM_KatanaAttack;

	AttackTime.Add(0.9f);
	AttackTime.Add(0.9f);
	AttackTime.Add(1.2f);
	AttackTime.Add(0.9f);

	WeaponSocketName = TEXT("KatanaSocket");

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> RifleSkeletalMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/weapon/melee/katana.katana'"));
	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Katana Weapon"));
	WeaponMeshComponent->SetSkeletalMesh(RifleSkeletalMeshRef.Object);
}

void UKatanaComponent::BeginPlay()
{
	Super::BeginPlay();
}
