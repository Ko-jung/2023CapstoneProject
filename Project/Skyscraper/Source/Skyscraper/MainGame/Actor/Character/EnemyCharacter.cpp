// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Skyscraper/MainGame/Component/Combat/Range/RifleComponent.h"
#include "Skyscraper/MainGame/Component/Combat/Range/MainRangeComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	RangeComponent = CreateDefaultSubobject<URifleComponent>(TEXT("Range"));
	
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	RangeComponent->SetBulletMaxCount(5);

	GetWorld()->GetTimerManager().SetTimer(EnemyFireTimerHandle, this, &ThisClass::FirePer1Sec, 1.0f, false,2.0f);
}

void AEnemyCharacter::FirePer1Sec()
{
	if(RangeComponent)
	{
		if (RangeComponent->CanFire())
		{
			RangeComponent->PlayFireAnim();
			GetWorld()->GetTimerManager().SetTimer(EnemyFireTimerHandle, this, &ThisClass::FirePer1Sec, 1.0f, false, 1.1f);
		}
		else
		{
			RangeComponent->PlayReloadAnim();
			GetWorld()->GetTimerManager().SetTimer(EnemyFireTimerHandle, this, &ThisClass::FirePer1Sec, 1.0f, false, 3.0f);
		}
	}else
	{
		UE_LOG(LogTemp, Warning, TEXT("진짜 모르겠다.."));
	}
	
}
