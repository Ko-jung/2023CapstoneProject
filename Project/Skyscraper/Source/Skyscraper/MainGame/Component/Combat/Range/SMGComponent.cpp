// Fill out your copyright notice in the Description page of Project Settings.


#include "SMGComponent.h"

#include "Skyscraper/MainGame/Component/Combat/CombatSystemComponent.h"

USMGComponent::USMGComponent()
{
	AnimMontageKey = ECharacterAnimMontage::ECAM_SMG;
	
	ReloadMaxCoolTime = 5.0f;
	BulletMaxCount = 50;
	FireMaxCoolTime = 0.2f;
	ReloadSpeedTime = 1.0f;

	RecoilAboveAmount = 1.0f;
	RecoilBesideAmount = 0.5f;
	RecoilTime = 0.1f;
	RecoilSpeed = 20.0f;

	WeaponSocketName = TEXT("SMGSocket");

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SMGSkeletalMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/weapon/gun/smg.smg'"));
	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SMG Weapon"));
	WeaponMeshComponent->SetSkeletalMesh(SMGSkeletalMeshRef.Object);
}

void USMGComponent::SetInitialValue()
{
	Super::SetInitialValue();

	UCombatSystemComponent* CombatComponent{};
	if (OwnerCharacter)
		CombatComponent = OwnerCharacter->CombatSystemComponent;

	if (CombatComponent)
	{
		FireMaxCoolTime = CombatComponent->SMG_FireTime;
		ReloadSpeedTime = CombatComponent->SMG_ReloadTime;
		EffectiveDistance = CombatComponent->SMG_EffectiveDistance;
	}
}
