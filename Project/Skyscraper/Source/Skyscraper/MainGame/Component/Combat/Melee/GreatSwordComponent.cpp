// Fill out your copyright notice in the Description page of Project Settings.


#include "GreatSwordComponent.h"

UGreatSwordComponent::UGreatSwordComponent()
{
	AnimMontageKeys.Add(ECharacterAnimMontage::ECAM_GreatSwordAttack1);
	AnimMontageKeys.Add(ECharacterAnimMontage::ECAM_GreatSwordAttack2);
	AnimMontageKeys.Add(ECharacterAnimMontage::ECAM_GreatSwordAttack3);
	

	AttackTime.Add(1.2f);
	AttackTime.Add(1.5f);
	AttackTime.Add(1.2f);
}

void UGreatSwordComponent::BeginPlay()
{
	Super::BeginPlay();
}
