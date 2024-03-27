// Fill out your copyright notice in the Description page of Project Settings.


#include "DaggerComponent.h"
#include "Skyscraper/Enum/ECharacterAnimMontage.h"

UDaggerComponent::UDaggerComponent()
{
	AnimMontageKeys.Add(ECharacterAnimMontage::ECAM_DaggerAttack1);
	AnimMontageKeys.Add(ECharacterAnimMontage::ECAM_DaggerAttack2);
	AnimMontageKeys.Add(ECharacterAnimMontage::ECAM_DaggerAttack3);
	AnimMontageKeys.Add(ECharacterAnimMontage::ECAM_DaggerAttack4);
	AnimMontageKeys.Add(ECharacterAnimMontage::ECAM_DaggerAttack5);

	AttackTime.Add(0.6f);
	AttackTime.Add(0.6f);
	AttackTime.Add(0.6f);
	AttackTime.Add(0.9f);
	AttackTime.Add(0.6f);

	
}

void UDaggerComponent::BeginPlay()
{
	Super::BeginPlay();
}
