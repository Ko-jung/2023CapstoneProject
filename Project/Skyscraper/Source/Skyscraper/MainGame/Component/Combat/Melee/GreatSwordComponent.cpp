// Fill out your copyright notice in the Description page of Project Settings.


#include "GreatSwordComponent.h"

UGreatSwordComponent::UGreatSwordComponent()
{
	AnimMontageKey = ECharacterAnimMontage::ECAM_GreatSwordAttack;
	

	AttackTime.Add(1.2f);
	AttackTime.Add(1.5f);
	AttackTime.Add(1.2f);
}

void UGreatSwordComponent::BeginPlay()
{
	Super::BeginPlay();
}
