// Fill out your copyright notice in the Description page of Project Settings.


#include "KatanaComponent.h"

UKatanaComponent::UKatanaComponent()
{
	AnimMontageKey = ECharacterAnimMontage::ECAM_KatanaAttack;

	AttackTime.Add(0.9f);
	AttackTime.Add(0.9f);
	AttackTime.Add(1.2f);
	AttackTime.Add(0.9f);
}

void UKatanaComponent::BeginPlay()
{
	Super::BeginPlay();
}
