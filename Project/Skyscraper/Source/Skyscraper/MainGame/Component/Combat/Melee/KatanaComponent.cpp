// Fill out your copyright notice in the Description page of Project Settings.


#include "KatanaComponent.h"

UKatanaComponent::UKatanaComponent()
{
	AnimMontageKey = ECharacterAnimMontage::ECAM_KatanaAttack;

	AttackTime.Add(0.6f);
	AttackTime.Add(0.6f);
	AttackTime.Add(1.8f);
	AttackTime.Add(0.6f);

	WeaponSocketName = TEXT("KatanaSocket");

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> KatanaSkeletalMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/weapon/melee/katana.katana'"));
	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Katana Weapon"));
	WeaponMeshComponent->SetSkeletalMesh(KatanaSkeletalMeshRef.Object);
}

void UKatanaComponent::BeginPlay()
{
	Super::BeginPlay();
}
