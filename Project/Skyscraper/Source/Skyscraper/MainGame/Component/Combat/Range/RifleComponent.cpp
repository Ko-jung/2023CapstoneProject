// Fill out your copyright notice in the Description page of Project Settings.


#include "RifleComponent.h"

URifleComponent::URifleComponent()
{
	FireAnimMontageKey = ECharacterAnimMontage::ECAM_RifleFire;
	ReloadAnimMontageKey = ECharacterAnimMontage::ECAM_RifleReload;

	ReloadMaxCoolTime = 5.0f;
	BulletMaxCount = 20;
	FireMaxCoolTime = 0.2;
	ReloadSpeedTime = 3.0f;

	RecoilAboveAmount = 1.0f;
	RecoilBesideAmount = 0.5f;
	RecoilTime = 0.1f;
	RecoilSpeed = 20.0f;
}

void URifleComponent::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("라이플 컴퍼넌트 잘 만들어짐"));
}
