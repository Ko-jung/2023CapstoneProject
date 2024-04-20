// Fill out your copyright notice in the Description page of Project Settings.


#include "KatanaComponent.h"

UKatanaComponent::UKatanaComponent()
{
	AnimMontageKey = ECharacterAnimMontage::ECAM_KatanaAttack;

	AttackTime.Add(0.6f);
	AttackTime.Add(0.6f);
	AttackTime.Add(0.8f);
	AttackTime.Add(1.0f);

	AttackBlendOutTime.Add(0.17f);
	AttackBlendOutTime.Add(0.11f);
	AttackBlendOutTime.Add(0.17f);
	AttackBlendOutTime.Add(0.3f);

	WeaponSocketName = TEXT("KatanaSocket");

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> KatanaSkeletalMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/weapon/melee/katana.katana'"));
	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Katana Weapon"));
	WeaponMeshComponent->SetSkeletalMesh(KatanaSkeletalMeshRef.Object);


	static ConstructorHelpers::FObjectFinder<USkeletalMesh> KatanaSheathMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/weapon/melee/sheath.sheath'"));
	KatanaSheathComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Katana Sheath"));
	KatanaSheathComponent->SetSkeletalMesh(KatanaSheathMeshRef.Object);
}

void UKatanaComponent::BeginPlay()
{
	Super::BeginPlay();

	// ���� �޼� ���Ͽ� ���̱�
	FAttachmentTransformRules AttachmentTransformRules{ EAttachmentRule::SnapToTarget,false };
	KatanaSheathComponent->AttachToComponent(OwnerCharacter->GetMesh(), AttachmentTransformRules, TEXT("KatanaSheathSocket"));
	//KatanaSheathSocket
	//KatanaSheathSocket


	// īŸ�� �����ʿ� ��ġ��Ű��
	KatanaAttachToRightHand(false);
}

void UKatanaComponent::KatanaAttachToRightHand(bool bToRightHand)
{
	if (!WeaponMeshComponent) return;

	FAttachmentTransformRules AttachmentTransformRules{ EAttachmentRule::SnapToTarget,false };
	// ���� ���� -> ���������� �ű��
	if(bToRightHand)
	{
		WeaponMeshComponent->AttachToComponent(OwnerCharacter->GetMesh(), AttachmentTransformRules, WeaponSocketName);
	}
	// ������ -> ���� �ű��
	else
	{
		WeaponMeshComponent->AttachToComponent(KatanaSheathComponent, AttachmentTransformRules, TEXT("katana_sheathSocket"));
	}
}

void UKatanaComponent::SetWeaponHiddenInGame(bool bNewHidden) const
{
	Super::SetWeaponHiddenInGame(bNewHidden);

	KatanaSheathComponent->SetHiddenInGame(bNewHidden);
}
