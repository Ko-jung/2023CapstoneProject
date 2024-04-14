// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeEnemyCharacter.h"

#include "Skyscraper/MainGame/Component/Combat/Melee/GreatSwordComponent.h"
#include "Skyscraper/MainGame/Component/Health/HealthComponent.h"

AMeleeEnemyCharacter::AMeleeEnemyCharacter()
{
	MeleeComponent = CreateDefaultSubobject<UGreatSwordComponent>(TEXT("Melee"));
}

void AMeleeEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

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
