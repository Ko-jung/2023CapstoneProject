// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeEnemyCharacter.h"

#include "Skyscraper/MainGame/Component/Combat/Melee/GreatSwordComponent.h"
#include "Skyscraper/MainGame/Component/Health/HealthComponent.h"

AMeleeEnemyCharacter::AMeleeEnemyCharacter()
{
	DoAttackDelay = 0.3f;
	MeleeClass = UGreatSwordComponent::StaticClass();
	//MeleeComponent = CreateDefaultSubobject<UGreatSwordComponent>(TEXT("Melee"));
}

void AMeleeEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 무기 컴퍼넌트 제작
	MeleeComponent = Cast<UMainMeleeComponent>(AddComponentByClass(MeleeClass, false, FTransform(), true));
	MeleeComponent->RegisterComponent();

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
