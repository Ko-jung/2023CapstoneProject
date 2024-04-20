// Fill out your copyright notice in the Description page of Project Settings.


#include "GreatSwordComponent.h"

UGreatSwordComponent::UGreatSwordComponent()
{
	// �ִϸ��̼� ��Ÿ�� Ű ����
	AnimMontageKey = ECharacterAnimMontage::ECAM_GreatSwordAttack;
	
	// �޺� ������ �ִϸ��̼� ��� �ð�
	AttackTime.Add(0.8f);
	AttackTime.Add(1.0f);
	AttackTime.Add(0.8f);
	
	// Skeletal Mesh ���� �̸� ����
	WeaponSocketName = TEXT("KatanaSocket");

	// Skeletal Mesh �ε�
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SwordSkeletalMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/weapon/melee/sword.sword'"));
	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Sword Weapon"));
	WeaponMeshComponent->SetSkeletalMesh(SwordSkeletalMeshRef.Object);
}

void UGreatSwordComponent::BeginPlay()
{
	Super::BeginPlay();
}
