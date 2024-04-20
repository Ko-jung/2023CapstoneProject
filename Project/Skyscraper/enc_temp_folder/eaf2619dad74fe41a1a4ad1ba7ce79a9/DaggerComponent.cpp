// Fill out your copyright notice in the Description page of Project Settings.


#include "DaggerComponent.h"
#include "Skyscraper/Enum/ECharacterAnimMontage.h"

UDaggerComponent::UDaggerComponent()
{
	AnimMontageKey = ECharacterAnimMontage::ECAM_DaggerAttack;

	AttackTime.Add(0.4f);
	AttackTime.Add(0.4f);
	AttackTime.Add(0.4f);
	AttackTime.Add(0.6f);
	AttackTime.Add(0.4f);

	// Skeletal Mesh ���� �̸� ����
	WeaponSocketName = TEXT("DaggerRightSocket");

	// Skeletal Mesh �ε�
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DaggerRightSkeletalMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/weapon/melee/dagger_right.dagger_right'"));
	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Dagger Right Weapon"));
	WeaponMeshComponent->SetSkeletalMesh(DaggerRightSkeletalMeshRef.Object);


	// Skeletal Mesh ���� �̸� ����
	WeaponSocketName = TEXT("DaggerLeftSocket");

	// Skeletal Mesh �ε�
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DaggerLeftSkeletalMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/weapon/melee/dagger_left.dagger_left'"));
	SubWeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Dagger Left Weapon"));
	SubWeaponMeshComponent->SetSkeletalMesh(DaggerLeftSkeletalMeshRef.Object);

	
	
}

void UDaggerComponent::BeginPlay()
{
	Super::BeginPlay();

	{ // ���� ĳ���Ϳ��� ���� ���� ����
		FAttachmentTransformRules AttachmentTransformRules{ EAttachmentRule::SnapToTarget,false };
		SubWeaponMeshComponent->AttachToComponent(OwnerCharacter->GetMesh(), AttachmentTransformRules, SubWeaponSocketName);
		SubWeaponMeshComponent->SetHiddenInGame(true);
	}
}

void UDaggerComponent::SetWeaponHiddenInGame(bool bNewHidden) const
{
	Super::SetWeaponHiddenInGame(bNewHidden);
	SubWeaponMeshComponent->SetHiddenInGame(bNewHidden);

}
