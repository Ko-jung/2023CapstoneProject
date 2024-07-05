// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "InputActionValue.h"
#include "Skyscraper/MainGame/Component/Combat/CombatSystemComponent.h"
#include "Skyscraper/MainGame/Component/Combat/Range/RifleComponent.h"
#include "Skyscraper/MainGame/Component/Combat/Range/MainRangeComponent.h"
#include "Skyscraper/MainGame/Component/Health/HealthComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	//RangeComponent = CreateDefaultSubobject<URifleComponent>(TEXT("Range"));
	RangeSelect = ERangeSelect::ERS_RPG;
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (RangeSelect != ERangeSelect::ERS_NONE)
	{
		CombatSystemComponent->SetInitialSelect(EMeleeSelect::EMS_Dagger, RangeSelect);
		CombatSystemComponent->SwapToMeleeWeapon(FInputActionValue());
	}

	GetWorld()->GetTimerManager().SetTimer(EnemyFireTimerHandle, this, &ThisClass::FirePer1Sec, 1.0f, false,2.0f);
}

void AEnemyCharacter::FirePer1Sec()
{
	if (HealthComponent && HealthComponent->GetHealthPercent() <= 0.0f) return;
	if(CombatSystemComponent)
	{
		
		if (CombatSystemComponent->GetRangeComponent()->CanFire())
		{
			CombatSystemComponent->GetRangeComponent()->PlayFireAnim();
			GetWorld()->GetTimerManager().SetTimer(EnemyFireTimerHandle, this, &ThisClass::FirePer1Sec, 1.0f, false, 1.1f);
		}
		else
		{
			CombatSystemComponent->GetRangeComponent()->PlayReloadAnim();
			GetWorld()->GetTimerManager().SetTimer(EnemyFireTimerHandle, this, &ThisClass::FirePer1Sec, 1.0f, false, 3.0f);
		}
	}
	
}
