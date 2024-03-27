// Fill out your copyright notice in the Description page of Project Settings.


#include "KatanaComponent.h"

UKatanaComponent::UKatanaComponent()
{
	AnimMontageKeys.Add(ECharacterAnimMontage::ECAM_KatanaAttack1);
	AnimMontageKeys.Add(ECharacterAnimMontage::ECAM_KatanaAttack2);
	AnimMontageKeys.Add(ECharacterAnimMontage::ECAM_KatanaAttack3);
	AnimMontageKeys.Add(ECharacterAnimMontage::ECAM_KatanaAttack4);

	AttackTime.Add(0.9f);
	AttackTime.Add(0.9f);
	AttackTime.Add(1.2f);
	AttackTime.Add(0.9f);
}

void UKatanaComponent::BeginPlay()
{
	Super::BeginPlay();
}
