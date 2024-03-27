// Fill out your copyright notice in the Description page of Project Settings.


#include "SMGComponent.h"

USMGComponent::USMGComponent()
{
	FireAnimMontageKey = ECharacterAnimMontage::ECAM_SMGFire;
	ReloadAnimMontageKey = ECharacterAnimMontage::ECAM_SMGReload;
	
	ReloadMaxCoolTime = 5.0f;
	BulletMaxCount = 50;
	FireMaxCoolTime = 0.1f;
	ReloadSpeedTime = 1.0f;

	RecoilAboveAmount = 1.0f;
	RecoilBesideAmount = 0.5f;
	RecoilTime = 0.1f;
	RecoilSpeed = 20.0f;
}
