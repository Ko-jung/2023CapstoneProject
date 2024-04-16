// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeEnemyCharacter.h"

#include "InputActionValue.h"
#include "Skyscraper/MainGame/Component/Combat/CombatSystemComponent.h"
#include "Skyscraper/MainGame/Component/Combat/Melee/GreatSwordComponent.h"
#include "Skyscraper/MainGame/Component/Health/HealthComponent.h"

AMeleeEnemyCharacter::AMeleeEnemyCharacter()
{
	DoAttackDelay = 0.3f;
	MeleeSelect = EMeleeSelect::EMS_GreatSword;
	
}

void AMeleeEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	CombatSystemComponent->SetInitialSelect(MeleeSelect,ERangeSelect::ERS_Rifle);
	CombatSystemComponent->SwapToMeleeWeapon(FInputActionValue());
	
	GetWorld()->GetTimerManager().SetTimer(EnemyAttackTimerHandle, this, &AMeleeEnemyCharacter::MeleeEnemyAttack, DoAttackDelay, false, 2.0f);
}

void AMeleeEnemyCharacter::MeleeEnemyAttack()
{
	if (HealthComponent && HealthComponent->GetHealthPercent() <= 0.0f) return;
	if(MeleeComponent)
	{
		MeleeComponent->Attack();
		GetWorld()->GetTimerManager().SetTimer(EnemyAttackTimerHandle, this, &AMeleeEnemyCharacter::MeleeEnemyAttack, DoAttackDelay, false, DoAttackDelay);
	}
}
