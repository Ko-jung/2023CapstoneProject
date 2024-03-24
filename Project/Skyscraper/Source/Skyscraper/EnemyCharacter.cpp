// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Skyscraper/MainGame/Component/Combat/Range/MainRangeComponent.h"

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	MainRangeComponent->SetBulletMaxCount(5);

	GetWorld()->GetTimerManager().SetTimer(EnemyFireTimerHandle, this, &ThisClass::FirePer1Sec, 1.0f, false,2.0f);
}

void AEnemyCharacter::FirePer1Sec()
{
	if(MainRangeComponent->CanFire())
	{
		MainRangeComponent->PlayFireAnim();
		GetWorld()->GetTimerManager().SetTimer(EnemyFireTimerHandle, this, &ThisClass::FirePer1Sec, 1.0f, false, 1.1f);
	}
	else
	{
		MainRangeComponent->PlayReloadAnim(1.0f);
		GetWorld()->GetTimerManager().SetTimer(EnemyFireTimerHandle, this, &ThisClass::FirePer1Sec, 1.0f, false, 2.0f);
	}
}
