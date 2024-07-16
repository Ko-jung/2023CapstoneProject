// Fill out your copyright notice in the Description page of Project Settings.


#include "KatanaComponent.h"

#include "Skyscraper/MainGame/Component/Combat/CombatSystemComponent.h"

UKatanaComponent::UKatanaComponent()
{
	MeleeSelect = EMeleeSelect::EMS_Katana;

	AnimMontageKey = ECharacterAnimMontage::ECAM_KatanaAttack;


	AttackBlendOutTime.Add(0.1f);
	AttackBlendOutTime.Add(0.1f);
	AttackBlendOutTime.Add(0.1f);
	AttackBlendOutTime.Add(0.2f);

	WeaponSocketName = TEXT("KatanaSocket");

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> KatanaSkeletalMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/weapon/melee/katana.katana'"));
	WeaponMeshComponent->SetSkeletalMesh(KatanaSkeletalMeshRef.Object);


	static ConstructorHelpers::FObjectFinder<USkeletalMesh> KatanaSheathMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/weapon/melee/sheath.sheath'"));
	SubWeaponMeshComponent->SetSkeletalMesh(KatanaSheathMeshRef.Object);
}

void UKatanaComponent::BeginPlay()
{
	Super::BeginPlay();

	// 검집 왼손 소켓에 붙이기
	FAttachmentTransformRules AttachmentTransformRules{ EAttachmentRule::SnapToTarget,false };
	SubWeaponMeshComponent->AttachToComponent(OwnerCharacter->GetMesh(), AttachmentTransformRules, TEXT("KatanaSheathSocket"));
	SubWeaponMeshComponent->SetHiddenInGame(true);
	//KatanaSheathSocket
	//KatanaSheathSocket


	// 카타나 검집쪽에 배치시키기
	KatanaAttachToRightHand(false);
}

void UKatanaComponent::KatanaAttachToRightHand(bool bToRightHand)
{
	if (!WeaponMeshComponent) return;

	FAttachmentTransformRules AttachmentTransformRules{ EAttachmentRule::SnapToTarget,false };
	// 무기 검집 -> 오른손으로 옮기기
	if(bToRightHand)
	{
		WeaponMeshComponent->AttachToComponent(OwnerCharacter->GetMesh(), AttachmentTransformRules, WeaponSocketName);
	}
	// 오른손 -> 검집 옮기기
	else
	{
		WeaponMeshComponent->AttachToComponent(SubWeaponMeshComponent, AttachmentTransformRules, TEXT("katana_sheathSocket"));
	}
}

void UKatanaComponent::SetWeaponHiddenInGame(bool bNewHidden) const
{
	Super::SetWeaponHiddenInGame(bNewHidden);
}

void UKatanaComponent::SetInitialValue()
{
	Super::SetInitialValue();

	UCombatSystemComponent* CombatComponent{};
	if (OwnerCharacter)
		CombatComponent = OwnerCharacter->CombatSystemComponent;

	if (CombatComponent)
	{
		AttackTime = CombatComponent->KatanaAttackTime;
	}
}
