// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGComponent.h"

URPGComponent::URPGComponent()
{
	const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_FireRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Rifle/AM_FireRifle.AM_FireRifle'"));
	AM_Fire = AM_FireRef.Object;
	const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_ReloadRef(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Rifle/AM_ReloadRifle.AM_ReloadRifle'"));
	AM_Reload = AM_ReloadRef.Object;

	ReloadMaxCoolTime = 5.0f;
	BulletMaxCount = 5;
	FireMaxCoolTime = 1.0f;
	ReloadSpeedTime = 5.0f;

	RecoilAboveAmount = 1.0f;
	RecoilBesideAmount = 0.5f;
	RecoilTime = 0.1f;
	RecoilSpeed = 20.0f;
}
