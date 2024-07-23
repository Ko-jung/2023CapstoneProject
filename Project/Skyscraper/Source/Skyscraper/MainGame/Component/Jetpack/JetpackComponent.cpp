// Fill out your copyright notice in the Description page of Project Settings.


#include "JetpackComponent.h"

#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"

#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Blueprint/UserWidget.h"
#include "Components/AudioComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/RepLayout.h"
#include "Skyscraper/MainGame/Core/SkyscraperPlayerController.h"
#include "Skyscraper/MainGame/Widget/Jetpack/JetpackGaugeBar.h"
#include "Skyscraper/Subsystem/SkyscraperEngineSubsystem.h"

// Sets default values for this component's properties
UJetpackComponent::UJetpackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MaxJetpackFuel = 1.0f;
	JetpackFuel = 0.0f;
	bChangeCameraFOV = false;
	bStartDash = false;
	ChangeFOVAlpha = 0.0f;
	LastCreateLandDustTime = 0.0f;

	bHoverStoping = false;
	HoveringMaxSpeed = 600.0f;
	HoverGaugePerSec = 0.33f;
	DashGaugePerSec = 0.1f;
	DodgeReductionGauge = 0.3f;

	MaxDashSpeed = 1500.0f;
	DodgeSpeed = 3000.0f;
		
	DodgeSlowdownValue = 0.04f;

	HoveringGravityScale = 1.0f;

	{ // == Set Input Asset
		static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_JetpackRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/2019180031/MainGame/Core/Input/Jetpack/IMC_Jetpack.IMC_Jetpack'"));
		IMC_Jetpack = IMC_JetpackRef.Object;

		static ConstructorHelpers::FObjectFinder<UInputAction> IA_Jetpack_HoverRef(TEXT("/Script/EnhancedInput.InputAction'/Game/2019180031/MainGame/Core/Input/Jetpack/IA_Jetpack_Hover.IA_Jetpack_Hover'"));
		IA_Jetpack_Hover = IA_Jetpack_HoverRef.Object;

		static ConstructorHelpers::FObjectFinder<UInputAction> IA_Jetpack_DashFastRef(TEXT("/Script/EnhancedInput.InputAction'/Game/2019180031/MainGame/Core/Input/Jetpack/IA_Jetpack_DashFast.IA_Jetpack_DashFast'"));
		IA_Jetpack_DashFast = IA_Jetpack_DashFastRef.Object;

		static ConstructorHelpers::FObjectFinder<UInputAction> IA_Jetpack_Dodge_FwdRef(TEXT("/Script/EnhancedInput.InputAction'/Game/2019180031/MainGame/Core/Input/Jetpack/IA_Jetpack_Dodge_Fwd.IA_Jetpack_Dodge_Fwd'"));
		IA_Jetpack_Dodge.Add(IA_Jetpack_Dodge_FwdRef.Object);
		static ConstructorHelpers::FObjectFinder<UInputAction> IA_Jetpack_Dodge_BwdRef(TEXT("/Script/EnhancedInput.InputAction'/Game/2019180031/MainGame/Core/Input/Jetpack/IA_Jetpack_Dodge_Bwd.IA_Jetpack_Dodge_Bwd'"));
		IA_Jetpack_Dodge.Add(IA_Jetpack_Dodge_BwdRef.Object);
		static ConstructorHelpers::FObjectFinder<UInputAction> IA_Jetpack_Dodge_RightRef(TEXT("/Script/EnhancedInput.InputAction'/Game/2019180031/MainGame/Core/Input/Jetpack/IA_Jetpack_Dodge_Right.IA_Jetpack_Dodge_Right'"));
		IA_Jetpack_Dodge.Add(IA_Jetpack_Dodge_RightRef.Object);
		static ConstructorHelpers::FObjectFinder<UInputAction> IA_Jetpack_Dodge_LeftRef(TEXT("/Script/EnhancedInput.InputAction'/Game/2019180031/MainGame/Core/Input/Jetpack/IA_Jetpack_Dodge_Left.IA_Jetpack_Dodge_Left'"));
		IA_Jetpack_Dodge.Add(IA_Jetpack_Dodge_LeftRef.Object);

		static ConstructorHelpers::FObjectFinder<UInputAction> IA_Jetpack_DescentRef(TEXT("/Script/EnhancedInput.InputAction'/Game/2019180031/MainGame/Core/Input/Jetpack/IA_Jetpack_Descent.IA_Jetpack_Descent'"));
		IA_Jetpack_Descent = IA_Jetpack_DescentRef.Object;
	}

	{ // 제트팩 위젯 클래스 로드
		static ConstructorHelpers::FClassFinder<UUserWidget> WBP_JetpackClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/2019180031/MainGame/Widget/Jetpack/WBP_JetpackGaugeBar.WBP_JetpackGaugeBar_C'"));
		JetpackWidgetClass = WBP_JetpackClass.Class;
	}

	{
		static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_LandDustRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/2019180031/MainGame/Fbx/LandDust/NS_LandDust.NS_LandDust'"));
		NS_LandDust = NS_LandDustRef.Object;
	}
	
	BoostMaintaingAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BoostMaintaingAudioComponent"));

	BoostStartAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BoostStartAudioComponent"));
}



// Called when the game starts
void UJetpackComponent::BeginPlay()
{
	Super::BeginPlay();

	{ // == Get Owner Character
		OwnerCharacter = Cast<ASkyscraperCharacter>(GetOwner());
	}
	
	AddInputMappingContext();
	BindingInputActions();

	OwnerCharacter->PlayBoostAnimation("Default");

	// BoostMaintaing audio component 연결
	if(OwnerCharacter && OwnerCharacter->GetBoostMesh())
	{
		BoostMaintaingAudioComponent->AttachToComponent(OwnerCharacter->GetBoostMesh(), FAttachmentTransformRules{ EAttachmentRule::SnapToTarget,true });
		BoostStartAudioComponent->AttachToComponent(OwnerCharacter->GetBoostMesh(), FAttachmentTransformRules{ EAttachmentRule::SnapToTarget,true });

		if (USkyscraperEngineSubsystem* Subsystem = GEngine->GetEngineSubsystem<USkyscraperEngineSubsystem>())
		{
			// 부스트 시작 소리 실행
			if (USoundBase* Sound = Subsystem->GetSkyscraperSound(TEXT("BoostMaintaing")))
			{
				BoostMaintaingAudioComponent->SetSound(Sound);
			}
			if(USoundBase* Sound = Subsystem->GetSkyscraperSound(TEXT("BoostStart")))
			{
				BoostStartAudioComponent->SetSound(Sound);
			}
		}
		
	}
}


// Called every frame
void UJetpackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if( (GetWorld()->GetTimeSeconds() - LastCreateLandDustTime) >= 0.25f && OwnerCharacter->GetIsHover())
	{
		LastCreateLandDustTime = GetWorld()->GetTimeSeconds();

		static float TriggerDistance = 150.0f;
		
		FVector Start = OwnerCharacter->GetActorLocation() - FVector(0.0f, 0.0f, 75.0f);
		FVector End = Start - FVector(0.0f, 0.0f, TriggerDistance);

		TArray<AActor*> IgnoreActors;
		IgnoreActors.Add(OwnerCharacter);
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UCollisionProfile::Get()->ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel2));


		EDrawDebugTrace::Type DrawDebugType{EDrawDebugTrace::None};

		FHitResult OutHit{};
		bool HitResult = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), Start, End, ObjectTypes, true, IgnoreActors, DrawDebugType, OutHit, true, FLinearColor::Red, FLinearColor::Blue, 5.0f);


		if (HitResult)
		{
			if(NS_LandDust)
			{
				UNiagaraComponent* FX = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
					GetWorld(), NS_LandDust,
					OutHit.Location + FVector(0.0f,0.0f,10.0f),
					FRotator{0.0f,0.0f,0.0f},
					FVector(1));

			}
			
		}
	}

	// Change FOV
	{ 
		if (bChangeCameraFOV)
		{
			if(JetpackFuel <= 0.0f)
			{
				bStartDash = false;
				ChangeFOVAlpha = 1 - ChangeFOVAlpha;
			}

			if(bStartDash)
			{
				ChangeFOVAlpha += (DeltaTime * 2.0f);
			}
			else
			{
				ChangeFOVAlpha += (DeltaTime * 3.0f);
			}
			
			if(ChangeFOVAlpha>=1.0f)
			{
				bChangeCameraFOV = false;
			}

			if(bStartDash)
			{
				OwnerCharacter->SetCameraFOVToDash(true, ChangeFOVAlpha);
			}
			else
			{
				OwnerCharacter->SetCameraFOVToDash(false, ChangeFOVAlpha);
			}
		}
	}
	
}

void UJetpackComponent::OnLandJetpack()
{
	SetFuel(MaxJetpackFuel);
	SetHoveringMode(false);

	if(OwnerCharacter->GetAnimInstance())
	{
		OwnerCharacter->GetAnimInstance()->bIsDescent = false;
	}
	
}



FVector UJetpackComponent::ClampToMaxWalkSpeed(const FVector& NewVelocity)
{
	// Owner Character의 최대 속도에 Clamp 하는 함수
	if (NewVelocity.Length() > GetOwnerCharacterMovement()->MaxWalkSpeed)
	{
		return NewVelocity.GetSafeNormal() * GetOwnerCharacterMovement()->MaxWalkSpeed;
	}

	return NewVelocity;

}

void UJetpackComponent::SetFuel(double NewFuel)
{
	if (bIsBoostGaugeInfinity)
	{
		return;
	}
	JetpackFuel = FMath::Max(0.0f, NewFuel);

	{
		// UI 내 제트팩 연료 설정
		if(JetpackWidget)
		{
			JetpackWidget->SetJetpackGaugePercent(JetpackFuel / MaxJetpackFuel);
		}
		
	}

}

void UJetpackComponent::SetHoveringMode(bool bHover)
{
	if (!OwnerCharacter) return;

	if (bHover)
	{
		// Hover 중이 아니었다면
		if (!OwnerCharacter->GetIsHover())
		{
			OwnerCharacter->SetIsHover(true);
			bIsHovering = true;
			SetCharacterMaxSpeed();
			GetOwnerCharacterMovement()->GravityScale = 0.0f;
			GetOwnerCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
			GetOwnerCharacterMovement()->MaxAcceleration = 50000.0f;

			OwnerCharacter->GetAnimInstance()->bIsDescent = false;

			// 이펙트
			{
				OwnerCharacter->SetBoostEffectVisibility(true);
			}

			// 소리
			{
				if (USkyscraperEngineSubsystem* Subsystem = GEngine->GetEngineSubsystem<USkyscraperEngineSubsystem>())
				{
					// 부스트 시작 소리 실행
					if(!BoostStartAudioComponent->IsPlaying())
					{
						BoostStartAudioComponent->Play(1.0f);
					}

					if(!BoostMaintaingAudioComponent->IsPlaying())
					{
						BoostMaintaingAudioComponent->Play(1.0f);
					}
				}
			}
		}
	}
	else   // bHover == false
	{
		OwnerCharacter->SetIsHover(false);
		bIsHovering = false;
		SetCharacterMaxSpeed();
		GetOwnerCharacterMovement()->GravityScale = 2.0f;

		if (BoostMaintaingAudioComponent->IsPlaying())
		{
			BoostMaintaingAudioComponent->Stop();
		}
		if (BoostStartAudioComponent->IsPlaying())
		{
			BoostStartAudioComponent->Stop();
		}

		// 이펙트
		{
			OwnerCharacter->SetBoostEffectVisibility(false);
		}
	}
}

void UJetpackComponent::AddJetpackVelocity(FVector AddVelocity, float FuelReduction)
{
	// == 현재 제트팩 속력에서 AddVelocity 만큼 더하고, FuelReduction 만큼 게이지 사용

	// == 캐릭터 호버링 모드 설정
	SetHoveringMode(true);

	// == 속력 설정
	GetOwnerCharacterMovement()->Velocity = ClampToMaxWalkSpeed(GetOwnerCharacterMovement()->Velocity + AddVelocity);

	// == 제트팩 연료 설정
	SetFuel(JetpackFuel - (GetWorld()->GetDeltaSeconds() * FuelReduction));
}

void UJetpackComponent::Hover(const FInputActionValue& InputActionValue)
{
	if (JetpackFuel > 0.0f)
	{
		AddJetpackVelocity(FVector(0.0f, 0.0f, 50.0f * HoveringGravityScale), HoverGaugePerSec);
		bHoverStoping = false;

		if(!BoostMaintaingAudioComponent->IsPlaying())
		{
			BoostMaintaingAudioComponent->Play(1.0f);
		}
		if (!BoostStartAudioComponent->IsPlaying())
		{
			BoostStartAudioComponent->Play(1.0f);
		}

		// 이펙트
		{
			OwnerCharacter->SetBoostEffectVisibility(true);
		}
	}
	else
	{
		HoverStop();
	}

}

void UJetpackComponent::HoverStop()
{
	ToGlidingSpeed();
	if(!bHoverStoping)
	{
		GetOwnerCharacterMovement()->Velocity.Z *= 0.1f;
		bHoverStoping = true;

		if (BoostMaintaingAudioComponent->IsPlaying() && !bIsDashing)
		{
			BoostMaintaingAudioComponent->Stop();
		}
		if (BoostStartAudioComponent->IsPlaying())
		{
			BoostStartAudioComponent->Stop();
		}

		// 이펙트
		{
			OwnerCharacter->SetBoostEffectVisibility(false);
		}
	}
	
}

void UJetpackComponent::ToGlidingSpeed()
{
	OwnerCharacter->GetCharacterMovement()->GravityScale = 0.5f;
}

void UJetpackComponent::DashFast()
{
	if(JetpackFuel >0.0f)
	{
		if(!bIsDashing)
		{
			bIsDashing = true;
			bChangeCameraFOV = true;
			ChangeFOVAlpha = 0.0f;
			bStartDash = true;			
			OwnerCharacter->SetDashEffectHiddenInGame(false);

			if(!BoostMaintaingAudioComponent->IsPlaying())
			{
				BoostMaintaingAudioComponent->Play(1.0f);
			}
			if (!BoostStartAudioComponent->IsPlaying())
			{
				BoostStartAudioComponent->Play(1.0f);
			}
			// 이펙트
			{
				OwnerCharacter->SetBoostEffectVisibility(true);
			}
		}
		SetHoveringMode(true);
		
		SetCharacterMaxSpeed();
		SetFuel(JetpackFuel - GetWorld()->GetDeltaSeconds() * DashGaugePerSec);
	}
	else
	{
		DashStop();
	}
}

void UJetpackComponent::DashStop()
{
	ToGlidingSpeed();
	OwnerCharacter->SetDashEffectHiddenInGame(true);
	//OwnerCharacter->SetCameraFOVToDash(false);
	bChangeCameraFOV = true;
	ChangeFOVAlpha = 0.0f;
	bStartDash = false;
	
	bIsDashing = false;
	SetCharacterMaxSpeed();
	//GetOwnerCharacterMovement()->Velocity = ClampToMaxWalkSpeed(GetOwnerCharacterMovement()->Velocity);
	if (BoostMaintaingAudioComponent->IsPlaying())
	{
		BoostMaintaingAudioComponent->Stop();
	}
	if (BoostStartAudioComponent->IsPlaying())
	{
		BoostStartAudioComponent->Stop();
	}

	// 이펙트
	{
		OwnerCharacter->SetBoostEffectVisibility(false);
	}
	
}

void UJetpackComponent::Dodge_Fwd()
{
	Dodge(FVector2D(1.0f, 0.0f));
}

void UJetpackComponent::Dodge_Bwd()
{
	Dodge(FVector2D(-1.0f, 0.0f));
}

void UJetpackComponent::Dodge_Right()
{
	Dodge(FVector2D(0.0f, 1.0f));
}

void UJetpackComponent::Dodge_Left()
{
	Dodge(FVector2D(0.0f, -1.0f));
}


void UJetpackComponent::SetCharacterMaxSpeed()
{
	if(bIsDashing)
	{
		GetOwnerCharacterMovement()->MaxWalkSpeed = MaxDashSpeed * OwnerCharacter->GetSpeedBuffValue();
		return;
	}

	if(bIsHovering)
	{
		GetOwnerCharacterMovement()->MaxWalkSpeed = HoveringMaxSpeed * OwnerCharacter->GetSpeedBuffValue() * HoveringGravityScale;
		return;
	}

	GetOwnerCharacterMovement()->MaxWalkSpeed = OwnerCharacter->GetCharacterMaxWalkSpeed() * OwnerCharacter->GetSpeedBuffValue();
	
}


void UJetpackComponent::Dodge(FVector2D InputValue)
{

	if (JetpackFuel < 0.1f) return;
	// 중력 없애기
	GetOwnerCharacterMovement()->GravityScale = 0.0f;

	OwnerCharacter->GetAnimInstance()->bIsDescent = false;

	// 액터 위치 살짝 올린 뒤 이동(바로 땅에 닿인상태에서 진행시 바로 내려오는 현상 수정)
	OwnerCharacter->SetActorLocation(OwnerCharacter->GetActorLocation() + FVector(0.0f, 0.0f, 3.0f));
	
	// 캐릭터 발사
	FVector	ForwardVector = OwnerCharacter->GetActorForwardVector();
	FVector	RightVector = OwnerCharacter->GetActorRightVector();
	ForwardVector *= InputValue.X;
	RightVector *= InputValue.Y;

	FVector LaunchVelocity = (ForwardVector + RightVector);
	LaunchVelocity.Normalize();
	LaunchVelocity = LaunchVelocity* DodgeSpeed * FVector(1.0f, 1.0f, 0.0f);
	OwnerCharacter->LaunchCharacter(LaunchVelocity,false,false);

	// 연료 사용
	SetFuel(JetpackFuel - DodgeReductionGauge);

	// 회피 감속 타이머 설정
	if (!SlowdownDodgeTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(SlowdownDodgeTimerHandle, this, &ThisClass::SlowdownDodge, 0.2f, false,0.2f);
	}

}


void UJetpackComponent::SlowdownDodge()
{
	if(GetOwnerCharacterMovement()->Velocity.Length()<= OwnerCharacter->GetCharacterMaxWalkSpeed())
	{
		GetWorld()->GetTimerManager().ClearTimer(SlowdownDodgeTimerHandle);
		GetOwnerCharacterMovement()->GravityScale = 1.0f;
	}else
	{
		GetOwnerCharacterMovement()->Velocity *= DodgeSlowdownValue;
			GetWorld()->GetTimerManager().SetTimer(SlowdownDodgeTimerHandle, this, &ThisClass::SlowdownDodge, 0.1f, false, 0.1f);
	}
}



void UJetpackComponent::ActivateBoostGaugeInfinity(float InfinityTime)
{
	bIsBoostGaugeInfinity = true;

	OwnerCharacter->SetItemEffectAndOverlayMaterial(EItemEffect::EIE_Single_BoostBulletInfinity, true);

	JetpackFuel = FMath::Max(JetpackFuel, 0.33f);


	if (!BoostGaugeInfinityTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(BoostGaugeInfinityTimerHandle, this, &ThisClass::DeactivateBoostGaugeInfinity, 0.2f, false, InfinityTime);
	}
	else      // 타이머가 기존에 실행 중이었다면 (무적 모드 중이었다면, 시간 초기화)
	{
		GetWorld()->GetTimerManager().ClearTimer(BoostGaugeInfinityTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(BoostGaugeInfinityTimerHandle, this, &ThisClass::DeactivateBoostGaugeInfinity, 0.2f, false, InfinityTime);
	}
}

void UJetpackComponent::DeactivateBoostGaugeInfinity()
{
	GetWorld()->GetTimerManager().ClearTimer(BoostGaugeInfinityTimerHandle);
	bIsBoostGaugeInfinity = false;
	OwnerCharacter->SetItemEffectAndOverlayMaterial(EItemEffect::EIE_Single_BoostBulletInfinity, false);
}

void UJetpackComponent::DoDescent() 
{
	if(UCharacterMovementComponent* CharacterMovementComponent = GetOwnerCharacterMovement())
	{
		CharacterMovementComponent->GravityScale = 1.0f;

		OwnerCharacter->GetAnimInstance()->bIsDescent = true;	

		if (!BoostStartAudioComponent->IsPlaying())
		{
			BoostStartAudioComponent->Play(1.0f);
		}
	}
}

void UJetpackComponent::RemoveAllInputMappingTemporary(UEnhancedInputLocalPlayerSubsystem* Subsystem)
{
	Subsystem->RemoveMappingContext(IMC_Jetpack);
}

void UJetpackComponent::BindingInputActions()
{
	if (!OwnerCharacter->GetPlayerController()) return;


	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(OwnerCharacter->GetPlayerController()->InputComponent))
	{
		// Hover InputAction 바인딩
		EnhancedInputComponent->BindAction(IA_Jetpack_Hover, ETriggerEvent::Triggered, this, &ThisClass::Hover);
		EnhancedInputComponent->BindAction(IA_Jetpack_Hover, ETriggerEvent::Completed, this, &ThisClass::HoverStop);
		// 대시 InputAction 바인딩
		EnhancedInputComponent->BindAction(IA_Jetpack_DashFast, ETriggerEvent::Triggered, this, &ThisClass::DashFast);
		EnhancedInputComponent->BindAction(IA_Jetpack_DashFast, ETriggerEvent::Completed, this, &ThisClass::DashStop);
		// 회피 InputAction 바인딩
		EnhancedInputComponent->BindAction(IA_Jetpack_Dodge[static_cast<uint8>(EDodgeKeys::EDK_W)], ETriggerEvent::Started, this, &ThisClass::Dodge_Fwd);
		EnhancedInputComponent->BindAction(IA_Jetpack_Dodge[static_cast<uint8>(EDodgeKeys::EDK_S)], ETriggerEvent::Started, this, &ThisClass::Dodge_Bwd);
		EnhancedInputComponent->BindAction(IA_Jetpack_Dodge[static_cast<uint8>(EDodgeKeys::EDK_D)], ETriggerEvent::Started, this, &ThisClass::Dodge_Right);
		EnhancedInputComponent->BindAction(IA_Jetpack_Dodge[static_cast<uint8>(EDodgeKeys::EDK_A)], ETriggerEvent::Started, this, &ThisClass::Dodge_Left);
		EnhancedInputComponent->BindAction(IA_Jetpack_Descent, ETriggerEvent::Started, this, &ThisClass::DoDescent);
	}
}

void UJetpackComponent::AddInputMappingContext()
{
	if(!JetpackWidget)
	{
		{// == UI 연결하기
			if (OwnerCharacter && OwnerCharacter->GetPlayerController())
			{
				JetpackWidget = Cast<UJetpackGaugeBar>(CreateWidget(OwnerCharacter->GetPlayerController(), JetpackWidgetClass));
				JetpackWidget->AddToViewport();
			}
		}

		JetpackFuel = MaxJetpackFuel;
	}
	


	//Add Input Mapping Context
	if (APlayerController* PlayerController = OwnerCharacter->GetPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC_Jetpack, 1);
		}
	}
}

void UJetpackComponent::AddHoveringGravityScale(float AddValue)
{
	HoveringGravityScale += AddValue;
}

void UJetpackComponent::SubtractFuelHalf()
{
	SetFuel(JetpackFuel - MaxJetpackFuel / 2);
}
