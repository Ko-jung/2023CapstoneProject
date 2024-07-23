// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "PlayMontageCallbackProxy.h"
#include "Components/ProgressBar.h"
#include "Components/TextRenderComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Skyscraper/MainGame/Core/SkyscraperPlayerController.h"
#include "Skyscraper/MainGame/Widget/Health/HealthBar.h"
#include "Skyscraper/MainGame/Widget/Health/MyHealthWidget.h"
#include "Skyscraper/Subsystem/SkyscraperEngineSubsystem.h"

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
	
	{ // 제트팩 위젯 클래스 로드
		static ConstructorHelpers::FClassFinder<UUserWidget> WBP_MyHealthClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/2019180031/MainGame/Widget/Health/WBP_Health.WBP_Health_C'"));
		MyHealthWidgetClass = WBP_MyHealthClass.Class;
	}
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	{ // == Initial Settings
		CurrentHealth = MaxHealth;
		LivingState = EHealthState::EHS_LIVING;
		OwnerCharacter = Cast<ASkyscraperCharacter>(GetOwner());
		if(OwnerCharacter == GEngine->GetFirstLocalPlayerController(GetWorld())->GetPawn())
		{
			HealthBarWidgetComponent->SetVisibility(false);
		}

		//TODO: DELETELATER
		HealthBarWidgetComponent->SetVisibility(false);
	}

	{ // == create widget and attach to owner
		USceneComponent* OwnerRootComponent = OwnerCharacter->GetRootComponent();
		const FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
		HealthBarWidgetComponent->InitWidget();
		HealthBarWidgetComponent->AttachToComponent(OwnerRootComponent, AttachRules);
		HealthBarWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 90.0f));
		
		HealthProgressBar = Cast<UHealthBar>(HealthBarWidgetComponent->GetUserWidgetObject());
	}

	// 생성 시 Player엔 controller가 없다. 후에 불러줄 예정
	AddWidget();

	// 게임 초기 시작때에는 소리가 안들리도록 및 부활 시 부활 사운드 실행
	{
		if(GetWorld()->GetTimeSeconds() >= 0.5f)
		{
			if (USkyscraperEngineSubsystem* Subsystem = GEngine->GetEngineSubsystem<USkyscraperEngineSubsystem>())
			{
				if (USoundBase* Sound = Subsystem->GetSkyscraperSound(TEXT("Revive")))
				{
					if (OwnerCharacter)
					{
						UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, OwnerCharacter->GetActorLocation(), FRotator{});
					}
				}
			}
		}
		
	}
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UHealthComponent::GetDamaged(float fBaseDamage, TObjectPtr<AActor> DamageCauser)
{
	// 무적 상태라면 대미지 안받도록
	if (bIsGodMode) return;

	CurrentHealth = FMath::Max(CurrentHealth - fBaseDamage, 0.0f);
	if(CurrentHealth<=0.0f)
	{
		SetPlayerDie(DamageCauser);
	}

	//HealthProgressBar->GetHealthBar()->SetPercent(CurrentHealth/MaxHealth);
	ChangeCurrentHp(CurrentHealth);
	
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

	OwnerCharacter->SetItemEffectAndOverlayMaterial(EItemEffect::EIE_Single_GodMode, true);

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
	OwnerCharacter->SetItemEffectAndOverlayMaterial(EItemEffect::EIE_Single_GodMode, false);
}


void UHealthComponent::ActivatePlusHealthBuff(float PlusHealthPercent, float PlusHealthTime)
{
	float PlusHealthValue = OriginMaxHealth * PlusHealthPercent;
	MaxHealth += PlusHealthValue;
	CurrentHealth += PlusHealthValue;
	//HealthProgressBar->GetHealthBar()->SetPercent(CurrentHealth / MaxHealth);
	ChangeCurrentHp(CurrentHealth);

	OwnerCharacter->SetItemEffectAndOverlayMaterial(EItemEffect::EIE_Team_PlusHealth, true);

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
		GetWorld()->GetTimerManager().ClearTimer(PlusHealthBuffTimerHandle);
		float PlusHealthValue = MaxHealth - OriginMaxHealth;
		MaxHealth = OriginMaxHealth;
		CurrentHealth = FMath::Max(CurrentHealth - PlusHealthValue, 1.0f);
		//HealthProgressBar->GetHealthBar()->SetPercent(CurrentHealth / MaxHealth);
		ChangeCurrentHp(CurrentHealth);

		OwnerCharacter->SetItemEffectAndOverlayMaterial(EItemEffect::EIE_Team_PlusHealth, false);
	}
}

void UHealthComponent::ChangeCurrentHp(float hp)
{
	CurrentHealth = hp;

	HealthProgressBar->GetHealthBar()->SetPercent(CurrentHealth / MaxHealth);

	if(MyHealthWidget)
	{
		MyHealthWidget->SetHealthPercent(CurrentHealth / MaxHealth);
	}
}

void UHealthComponent::ChangeState(EHealthState s)
{
	switch (s)
	{
	case EHealthState::EHS_INVINCIBILITY:
		break;
	case EHealthState::EHS_LIVING:
		break;		   
	case EHealthState::EHS_DYING:
		break;
	case EHealthState::EHS_DEAD:
		SetPlayerDie();
		break;
	default:
		break;
	}
}

void UHealthComponent::AddWidget()
{
	{// == My Health UI 연결하기
		if (APlayerController* PlayerController = OwnerCharacter->GetPlayerController())
		{
			MyHealthWidget = Cast<UMyHealthWidget>(CreateWidget(PlayerController, MyHealthWidgetClass));
			MyHealthWidget->AddToViewport();
		}
	}
}

void UHealthComponent::SetPlayerDie(TObjectPtr<AActor> DamageCauser)
{
	if (!OwnerCharacter) return;

	LivingState = EHealthState::EHS_DEAD;

	if(APlayerController* OwnerPlayerController = OwnerCharacter->GetPlayerController())
	{
		if(USkyscraperEngineSubsystem* Subsystem = GEngine->GetEngineSubsystem<USkyscraperEngineSubsystem>())
		{
			USoundBase* Sound = Subsystem->GetSkyscraperSound(TEXT("Death"));
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, OwnerCharacter->GetActorLocation());
		}

		// == For player (with player controller)
		OwnerCharacter->DisableInput(OwnerPlayerController);

		// 사망 몽타쥬 플레이시키기
		if (UAnimMontage* Montage = OwnerCharacter->GetAnimMontage(ECharacterAnimMontage::ECAM_Death))
		{
			UPlayMontageCallbackProxy* PlayMontageCallbackProxy = UPlayMontageCallbackProxy::CreateProxyObjectForPlayMontage(OwnerCharacter->GetMesh(), Montage, 1.0, 0, FName(TEXT("Death_Bwd")));
		}

		if(ASkyscraperPlayerController* PC = Cast<ASkyscraperPlayerController>(OwnerPlayerController))
		{
			// 무기교체 UI 추가
			PC->AddChangeWeaponWidget();

			// 관전 모드로 변경할 수 있도록 설정
			if(DamageCauser)
			{
				PC->SetSpectatorMode(true, DamageCauser);
			}
		}


	}else
	{
		// == For enemy(no player)
		//OwnerCharacter->Destroy();
		
	}
}

