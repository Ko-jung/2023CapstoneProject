// Fill out your copyright notice in the Description page of Project Settings.


#include "GreatSwordComponent.h"

UGreatSwordComponent::UGreatSwordComponent()
{
	const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_GreatSword1Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/GreatSword/GreatSwordSlash1_Montage.GreatSwordSlash1_Montage'"));
	MeleeComboAnimMontage.Add(MeleeComboAnimMontage.Num(), AM_GreatSword1Ref.Object);
	const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_GreatSword2Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/GreatSword/GreatSwordSlash2_Montage.GreatSwordSlash2_Montage'"));
	MeleeComboAnimMontage.Add(MeleeComboAnimMontage.Num(), AM_GreatSword2Ref.Object);
	const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_GreatSword3Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/GreatSword/GreatSwordSlash3_Montage.GreatSwordSlash3_Montage'"));
	MeleeComboAnimMontage.Add(MeleeComboAnimMontage.Num(), AM_GreatSword3Ref.Object);

	AttackTime.Add(1.2f);
	AttackTime.Add(1.5f);
	AttackTime.Add(1.2f);
}

void UGreatSwordComponent::BeginPlay()
{
	Super::BeginPlay();
}
