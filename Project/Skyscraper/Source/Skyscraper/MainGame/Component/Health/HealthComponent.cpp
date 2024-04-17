// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "PlayMontageCallbackProxy.h"
#include "Components/ProgressBar.h"
#include "Components/TextRenderComponent.h"
#include "Components/WidgetComponent.h"
#include "Skyscraper/MainGame/Widget/Health/HealthBar.h"

class UPlayMontageCallbackProxy;
// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	MaxHealth = 1000.0f;
	OriginMaxHealth = MaxHealth;
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
		HealthBarWidgetComponent->SetDrawSize(FVector2D(150.0f, 25.0f));
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

void UHealthComponent::ActivateGodMode(float GodModeTime)
{
	bIsGodMode = true;
	UE_LOG(LogTemp, Warning, TEXT("god mode on"));

	if (!GodModeTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(GodModeTimerHandle, this, &ThisClass::DeactivateGodMode, 0.2f, false, GodModeTime);
	}
	else      // 타이머가 기존에 실행 중이었다면 (무적 모드 중이었다면, 시간 초기화)
	{
		GetWorld()->GetTimerManager().ClearTimer(GodModeTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(GodModeTimerHandle, this, &ThisClass::DeactivateGodMode, 0.2f, false, GodModeTime);
	}
}

void UHealthComponent::DeactivateGodMode()
{
	GetWorld()->GetTimerManager().ClearTimer(GodModeTimerHandle);
	bIsGodMode = false;
	UE_LOG(LogTemp, Warning, TEXT("God Mode Turnn Off"));
}


void UHealthComponent::ActivatePlusHealthBuff(float PlusHealthPercent, float PlusHealthTime)
{
	float PlusHealthValue = OriginMaxHealth * PlusHealthPercent;
	MaxHealth += PlusHealthValue;
	CurrentHealth += PlusHealthValue;
	UE_LOG(LogTemp, Warning, TEXT("health %f / %f Plus - %f"), CurrentHealth, MaxHealth, PlusHealthValue);
	HealthProgressBar->GetHealthBar()->SetPercent(CurrentHealth / MaxHealth);

	if (!PlusHealthBuffTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(PlusHealthBuffTimerHandle, this, &ThisClass::DeactivatePlusHealth, 0.2f, false, PlusHealthTime);
	}
	else      // 타이머가 기존에 실행 중이었다면 (무적 모드 중이었다면, 시간 초기화)
	{
		GetWorld()->GetTimerManager().ClearTimer(PlusHealthBuffTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(PlusHealthBuffTimerHandle, this, &ThisClass::DeactivatePlusHealth, 0.2f, false, PlusHealthTime);
	}

}

void UHealthComponent::DeactivatePlusHealth()
{
	if(PlusHealthBuffTimerHandle.IsValid())
	{
		float PlusHealthValue = MaxHealth - OriginMaxHealth;
		MaxHealth = OriginMaxHealth;
		CurrentHealth = FMath::Max(CurrentHealth - PlusHealthValue, 1.0f);
		UE_LOG(LogTemp, Warning, TEXT("health plus end, %f / %f"), CurrentHealth,MaxHealth);
		HealthProgressBar->GetHealthBar()->SetPercent(CurrentHealth / MaxHealth);
		GetWorld()->GetTimerManager().ClearTimer(PlusHealthBuffTimerHandle);
	}
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
		// 사망 몽타쥬 플레이시키기

		if (UAnimMontage* Montage = OwnerCharacter->GetAnimMontage(ECharacterAnimMontage::ECAM_Death))
		{
			UPlayMontageCallbackProxy* PlayMontageCallbackProxy = UPlayMontageCallbackProxy::CreateProxyObjectForPlayMontage(OwnerCharacter->GetMesh(), Montage, 1.0, 0, FName(TEXT("Death_Bwd")));
		}

		// == TODO: Add DeadStateComponent

	}else
	{
		// == For enemy(no player)
		//OwnerCharacter->Destroy();
		
	}
}

