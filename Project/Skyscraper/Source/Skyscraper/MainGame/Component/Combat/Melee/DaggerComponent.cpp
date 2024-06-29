// Fill out your copyright notice in the Description page of Project Settings.


#include "DaggerComponent.h"
#include "Skyscraper/Enum/ECharacterAnimMontage.h"
#include "Skyscraper/MainGame/Component/Combat/CombatSystemComponent.h"

UDaggerComponent::UDaggerComponent()
{
	AnimMontageKey = ECharacterAnimMontage::ECAM_DaggerAttack;
	AttackBlendOutTime.Add(0.00f);
	AttackBlendOutTime.Add(0.00f);
	AttackBlendOutTime.Add(0.00f);
	AttackBlendOutTime.Add(0.00f);
	AttackBlendOutTime.Add(0.02f);

	// Skeletal Mesh 소켓 이름 설정
	WeaponSocketName = TEXT("DaggerRightSocket");

	// Skeletal Mesh 로드
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DaggerRightSkeletalMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/weapon/melee/dagger_right.dagger_right'"));
	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Dagger Right Weapon"));
	WeaponMeshComponent->SetSkeletalMesh(DaggerRightSkeletalMeshRef.Object);


	// Skeletal Mesh 소켓 이름 설정
	SubWeaponSocketName = TEXT("DaggerLeftSocket");

	// Skeletal Mesh 로드
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DaggerLeftSkeletalMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/weapon/melee/dagger_left.dagger_left'"));
	SubWeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Dagger Left Weapon"));
	SubWeaponMeshComponent->SetSkeletalMesh(DaggerLeftSkeletalMeshRef.Object);

	
	
}

void UDaggerComponent::BeginPlay()
{
	Super::BeginPlay();

	{ // 소유 캐릭터에게 서브 무기 부착
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

void UDaggerComponent::SetInitialValue()
{
	Super::SetInitialValue();
	UCombatSystemComponent* CombatComponent{};
	if (OwnerCharacter)
		CombatComponent = OwnerCharacter->CombatSystemComponent;

	if(CombatComponent)
	{
		AttackTime = CombatComponent->DaggerAttackTime;
	}
	

	
}
