// Fill out your copyright notice in the Description page of Project Settings.


#include "DaggerComponent.h"
#include "Skyscraper/Enum/ECharacterAnimMontage.h"

UDaggerComponent::UDaggerComponent()
{
	AnimMontageKey = ECharacterAnimMontage::ECAM_DaggerAttack;

	AttackTime.Add(0.4f);
	AttackTime.Add(0.4f);
	AttackTime.Add(0.4f);
	AttackTime.Add(0.6f);
	AttackTime.Add(0.4f);

	
}

void UDaggerComponent::BeginPlay()
{
	Super::BeginPlay();
}
