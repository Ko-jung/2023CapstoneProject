// Fill out your copyright notice in the Description page of Project Settings.


#include "DaggerComponent.h"

UDaggerComponent::UDaggerComponent()
{
	const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Dagger1Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/Dagger/AM_Dagger1.AM_Dagger1'"));
	MeleeComboAnimMontage.Add(MeleeComboAnimMontage.Num(),AM_Dagger1Ref.Object);
	const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Dagger2Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/Dagger/AM_Dagger2.AM_Dagger2'"));
	MeleeComboAnimMontage.Add(MeleeComboAnimMontage.Num(), AM_Dagger2Ref.Object);
	const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Dagger3Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/Dagger/AM_Dagger3.AM_Dagger3'"));
	MeleeComboAnimMontage.Add(MeleeComboAnimMontage.Num(), AM_Dagger3Ref.Object);
	const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Dagger4Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/Dagger/AM_Dagger4.AM_Dagger4'"));
	MeleeComboAnimMontage.Add(MeleeComboAnimMontage.Num(), AM_Dagger4Ref.Object);
	const ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Dagger5Ref(TEXT("/Script/Engine.AnimMontage'/Game/2019180031/Character/PrototypeAnimation/Combat/Attacks/Dagger/AM_Dagger5.AM_Dagger5'"));
	MeleeComboAnimMontage.Add(MeleeComboAnimMontage.Num(), AM_Dagger5Ref.Object);
	
	AttackTime.Add(0.6f);
	AttackTime.Add(0.6f);
	AttackTime.Add(0.6f);
	AttackTime.Add(0.9f);
	AttackTime.Add(0.6f);

	
}

void UDaggerComponent::BeginPlay()
{
	Super::BeginPlay();
}
