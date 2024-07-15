// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageComponent.h"
#include "Skyscraper/MainGame/Widget/Damage/DamageWidget.h"

UDamageComponent::UDamageComponent()
{
	ConstructorHelpers::FClassFinder<UUserWidget> WBP_DamagewidgetRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/2019180031/MainGame/Widget/Damage/WBP_DamageWidget.WBP_DamageWidget_C'"));
	if(WBP_DamagewidgetRef.Succeeded())
	{
		SetWidgetClass(WBP_DamagewidgetRef.Class);
	}

	SetWidgetSpace(EWidgetSpace::Screen);
	SetPivot(FVector2D{ 0.2f,0.75f });
}

void UDamageComponent::InitializeDamage(int GetDamage)
{
	Damage = GetDamage;
	LengthOfDamage = GetDamage == 0 ? 1 : FMath::LogX(10.0f, abs(Damage)) + 1;

	MaxLifeTime = 3.0f;
	StartTime = GetWorld()->GetTimeSeconds();

	SetDrawSize(FVector2D{ LengthOfDamage * 100.0f, 50.0f });

	Cast<UDamageWidget>(GetUserWidgetObject())->CreateDamageImage(Damage, LengthOfDamage);
	SetComponentTickEnabled(true);
	
}

void UDamageComponent::BeginPlay()
{
	Super::BeginPlay();
	SetComponentTickEnabled(false);
	
}

void UDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	SetRelativeLocation(GetRelativeLocation() + FVector{0.0f, 0.0f, 300.0f * DeltaTime});

	if (GetWorld()->GetTimeSeconds() >= StartTime + MaxLifeTime)
	{
		DestroyComponent();
	}
}
