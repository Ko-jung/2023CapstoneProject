// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGComponent.h"

URPGComponent::URPGComponent()
{
	FireAnimMontageKey = ECharacterAnimMontage::ECAM_RPGFire;
	ReloadAnimMontageKey = ECharacterAnimMontage::ECAM_RPGReload;

	

	ReloadMaxCoolTime = 5.0f;
	BulletMaxCount = 5;
	FireMaxCoolTime = 1.0f;
	ReloadSpeedTime = 5.0f;

	RecoilAboveAmount = 1.0f;
	RecoilBesideAmount = 0.5f;
	RecoilTime = 0.1f;
	RecoilSpeed = 20.0f;
}
