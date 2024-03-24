// Fill out your copyright notice in the Description page of Project Settings.


#include "KatanaComponent.h"

UKatanaComponent::UKatanaComponent()
{
	const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Katana1Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/Katana/AM_Katana1.AM_Katana1'"));
	MeleeComboAnimMontage.Add(MeleeComboAnimMontage.Num(), AM_Katana1Ref.Object);
	const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Katana2Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/Katana/AM_Katana2.AM_Katana2'"));
	MeleeComboAnimMontage.Add(MeleeComboAnimMontage.Num(), AM_Katana2Ref.Object);
	const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Katana3Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/Katana/AM_Katana3.AM_Katana3'"));
	MeleeComboAnimMontage.Add(MeleeComboAnimMontage.Num(), AM_Katana3Ref.Object);
	const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Katana4Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/Katana/AM_Katana4.AM_Katana4'"));
	MeleeComboAnimMontage.Add(MeleeComboAnimMontage.Num(), AM_Katana4Ref.Object);

	AttackTime.Add(0.9f);
	AttackTime.Add(0.9f);
	AttackTime.Add(1.2f);
	AttackTime.Add(0.9f);
}

void UKatanaComponent::BeginPlay()
{
	Super::BeginPlay();
}
