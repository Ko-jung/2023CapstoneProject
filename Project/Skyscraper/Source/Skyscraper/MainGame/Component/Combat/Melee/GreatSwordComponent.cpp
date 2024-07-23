// Fill out your copyright notice in the Description page of Project Settings.


#include "GreatSwordComponent.h"

#include "Skyscraper/MainGame/Component/Combat/CombatSystemComponent.h"

UGreatSwordComponent::UGreatSwordComponent()
{
	MeleeSelect = EMeleeSelect::EMS_GreatSword;

	AttackSound = TEXT("SwordAttack");
	FinalAttackSound = TEXT("SwordAttack");

	DamagedSound = TEXT("SwordHit");
	FinalDamagedSound = TEXT("SwordHit_last");

	// 애니메이션 몽타쥬 키 설정
	AnimMontageKey = ECharacterAnimMontage::ECAM_GreatSwordAttack;
	

	AttackBlendOutTime.Add(0.0f);
	AttackBlendOutTime.Add(0.0f);
	AttackBlendOutTime.Add(0.02f);
	
	// Skeletal Mesh 소켓 이름 설정
	WeaponSocketName = TEXT("SwordSocket");

	// Skeletal Mesh 로드
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SwordSkeletalMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/weapon/melee/sword.sword'"));
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
