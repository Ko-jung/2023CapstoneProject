// Fill out your copyright notice in the Description page of Project Settings.


#include "GreatSwordComponent.h"

#include "Skyscraper/MainGame/Component/Combat/CombatSystemComponent.h"

UGreatSwordComponent::UGreatSwordComponent()
{
	// 애니메이션 몽타쥬 키 설정
	AnimMontageKey = ECharacterAnimMontage::ECAM_GreatSwordAttack;
	

	AttackBlendOutTime.Add(0.2f);
	AttackBlendOutTime.Add(0.1f);
	AttackBlendOutTime.Add(0.1f);
	
	// Skeletal Mesh 소켓 이름 설정
	WeaponSocketName = TEXT("SwordSocket");

	// Skeletal Mesh 로드
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SwordSkeletalMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/weapon/melee/sword.sword'"));
	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Sword Weapon"));
	WeaponMeshComponent->SetSkeletalMesh(SwordSkeletalMeshRef.Object);
}

void UGreatSwordComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UGreatSwordComponent::SetInitialValue()
{
	Super::SetInitialValue();
	

	UCombatSystemComponent* CombatComponent{};
	if (OwnerCharacter)
		CombatComponent = OwnerCharacter->CombatSystemComponent;

	if (CombatComponent)
	{
		AttackTime = CombatComponent->SwordAttackTime;
	}
}
