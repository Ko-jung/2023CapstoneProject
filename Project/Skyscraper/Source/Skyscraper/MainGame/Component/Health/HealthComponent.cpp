// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "Components/ProgressBar.h"
#include "Components/TextRenderComponent.h"
#include "Components/WidgetComponent.h"
#include "Skyscraper/MainGame/Widget/Health/HealthBar.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	MaxHealth = 1000.0f;
	CurrentHealth = 0.0f;
	OwnerCharacter = nullptr;
	LivingState = EHealthState::EHS_LIVING;
	HealthProgressBar = nullptr;
	bIsGodMode = false;

	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	
	HealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	static ConstructorHelpers::FClassFinder<UUserWidget> HealthBarWidgetRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/2019180031/MainGame/Widget/Health/WBP_HealthBar.WBP_HealthBar_C'"));
	if(HealthBarWidgetRef.Class)
	{
		HealthBarWidgetComponent->SetWidgetClass(HealthBarWidgetRef.Class);
		HealthBarWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		HealthBarWidgetComponent->SetDrawSize(FVector2D(200.0f, 50.0f));
		HealthBarWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	
	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	{ // == Initial Settings
		CurrentHealth = MaxHealth;
		LivingState = EHealthState::EHS_LIVING;
		OwnerCharacter = Cast<ASkyscraperCharacter>(GetOwner());
	}

	{ // == create widget and attach to owner
		USceneComponent* OwnerRootComponent = OwnerCharacter->GetRootComponent();
		const FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
		HealthBarWidgetComponent->InitWidget();
		HealthBarWidgetComponent->AttachToComponent(OwnerRootComponent, AttachRules);
		HealthBarWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 90.0f));
		
		HealthProgressBar = Cast<UHealthBar>(HealthBarWidgetComponent->GetUserWidgetObject());
		
		
		
		
	}

	
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UHealthComponent::GetDamaged(float fBaseDamage)
{
	// 무적 상태라면 대미지 안받도록
	if (bIsGodMode) return;

	CurrentHealth = FMath::Max(CurrentHealth - fBaseDamage, 0.0f);
	if(CurrentHealth<=0.0f)
	{
		SetPlayerDie();
	}

	HealthProgressBar->GetHealthBar()->SetPercent(CurrentHealth/MaxHealth);
	
}

float UHealthComponent::GetHealthPercent() const
{
	if(HealthProgressBar)
	{
		return HealthProgressBar->GetHealthBar()->GetPercent();
	}
	
	return 1.0f;
	
}

void UHealthComponent::SetHealthGodMode(bool bSet)
{
	bIsGodMode = bSet;
}

void UHealthComponent::ChangeCurrentHp(float hp)
{
	CurrentHealth = hp;

	HealthProgressBar->GetHealthBar()->SetPercent(CurrentHealth / MaxHealth);
}

void UHealthComponent::ChangeState(ECharacterState s)
{
	switch (s)
	{
	case ECharacterState::LIVING:
		break;
	case ECharacterState::DYING:
		break;
	case ECharacterState::DEAD:
		SetPlayerDie();
		break;
	default:
		break;
	}
}

void UHealthComponent::SetPlayerDie()
{
	LivingState = EHealthState::EHS_DEAD;

	if(APlayerController* OwnerPlayerController = OwnerCharacter->GetPlayerController())
	{
		// == For player (with player controller)
		OwnerCharacter->DisableInput(OwnerPlayerController);

		// == TODO: Add DeadStateComponent

	}else
	{
		// == For enemy(no player)
		//OwnerCharacter->Destroy();
	}
}

