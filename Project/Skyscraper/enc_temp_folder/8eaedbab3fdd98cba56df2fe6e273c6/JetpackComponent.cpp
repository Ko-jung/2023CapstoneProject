// Fill out your copyright notice in the Description page of Project Settings.


#include "JetpackComponent.h"

#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"

#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UJetpackComponent::UJetpackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MaxJetpackFuel = 1.0f;
	JetpackFuel = 0.0f;

	bHoverStoping = false;
	HoveringMaxSpeed = 600.0f;
	HoverGaugePerSec = 0.33f;
	DashGaugePerSec = 0.1f;
	DodgeReductionGauge = 0.3f;
	MaxDashSpeed = 1500.0f;
	DodgeSpeed = 3000.0f;
		
	DodgeSlowdownValue = 0.04f;

	{ // == Set Input Asset
		static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_JetpackRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/2019180031/MainGame/Core/Input/Jetpack/IMC_Jetpack.IMC_Jetpack'"));
		IMC_Jetpack = IMC_JetpackRef.Object;

		static ConstructorHelpers::FObjectFinder<UInputAction> IA_Jetpack_HoverRef(TEXT("/Script/EnhancedInput.InputAction'/Game/2019180031/MainGame/Core/Input/Jetpack/IA_Jetpack_Hover.IA_Jetpack_Hover'"));
		IA_Jetpack_Hover = IA_Jetpack_HoverRef.Object;

		static ConstructorHelpers::FObjectFinder<UInputAction> IA_Jetpack_DashFastRef(TEXT("/Script/EnhancedInput.InputAction'/Game/2019180031/MainGame/Core/Input/Jetpack/IA_Jetpack_DashFast.IA_Jetpack_DashFast'"));
		IA_Jetpack_DashFast = IA_Jetpack_DashFastRef.Object;

		
	}
}



// Called when the game starts
void UJetpackComponent::BeginPlay()
{
	Super::BeginPlay();

	{ // == Get Owner Character
		OwnerCharacter = Cast<ASkyscraperCharacter>(GetOwner());

		
	}

	// == TODO: UI �����ϱ�

	JetpackFuel = MaxJetpackFuel;

	//Add Input Mapping Context
	if (APlayerController* PlayerController = OwnerCharacter->GetPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC_Jetpack, 1);
	
			if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
			{
				EnhancedInputComponent->BindAction(IA_Jetpack_Hover, ETriggerEvent::Triggered, this, &ThisClass::Hover);
				EnhancedInputComponent->BindAction(IA_Jetpack_Hover, ETriggerEvent::Completed, this, &ThisClass::HoverStop);
				EnhancedInputComponent->BindAction(IA_Jetpack_DashFast, ETriggerEvent::Triggered, this, &ThisClass::DashFast);
				EnhancedInputComponent->BindAction(IA_Jetpack_DashFast, ETriggerEvent::Completed, this, &ThisClass::DashStop);
				//EnhancedInputComponent->BindAction(IA_Jetpack_Dodge, ETriggerEvent::Triggered, this, &ThisClass::Dodge);
			}
		}
	}
}


// Called every frame
void UJetpackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UJetpackComponent::OnLandJetpack()
{
	SetFuel(MaxJetpackFuel);
	SetHoveringMode(false);
}



FVector UJetpackComponent::ClampToMaxWalkSpeed(const FVector& NewVelocity)
{
	// Owner Character�� �ִ� �ӵ��� Clamp �ϴ� �Լ�
	if (NewVelocity.Length() > GetOwnerCharacterMovement()->MaxWalkSpeed)
	{
		return NewVelocity.GetSafeNormal() * GetOwnerCharacterMovement()->MaxWalkSpeed;
	}

	return NewVelocity;

}

void UJetpackComponent::SetFuel(double NewFuel)
{
	JetpackFuel = FMath::Max(0.0f, NewFuel);
	// == TODO: UI �� ��Ʈ�� ���� ����
}

void UJetpackComponent::SetHoveringMode(bool bHover)
{
	if (bHover)
	{
		// Hover ���� �ƴϾ��ٸ�
		if (!OwnerCharacter->GetIsHover())
		{
			OwnerCharacter->SetIsHover(true);
			GetOwnerCharacterMovement()->MaxWalkSpeed = HoveringMaxSpeed;
			GetOwnerCharacterMovement()->GravityScale = 0.0f;
			GetOwnerCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
			GetOwnerCharacterMovement()->MaxAcceleration = 50000.0f;
		}
	}
	else   // bHover == false
	{
		OwnerCharacter->SetIsHover(false);
		GetOwnerCharacterMovement()->MaxWalkSpeed = 600.0f;
		GetOwnerCharacterMovement()->GravityScale = 2.0f;

	}
}

void UJetpackComponent::AddJetpackVelocity(FVector AddVelocity, float FuelReduction)
{
	// == ���� ��Ʈ�� �ӷ¿��� AddVelocity ��ŭ ���ϰ�, FuelReduction ��ŭ ������ ���

	// == ĳ���� ȣ���� ��� ����
	SetHoveringMode(true);

	// == �ӷ� ����
	GetOwnerCharacterMovement()->Velocity = ClampToMaxWalkSpeed(GetOwnerCharacterMovement()->Velocity + AddVelocity);

	// == ��Ʈ�� ���� ����
	SetFuel(JetpackFuel - (GetWorld()->GetDeltaSeconds() * FuelReduction));
}

void UJetpackComponent::Hover(const FInputActionValue& InputActionValue)
{
	if (JetpackFuel > 0.0f)
	{
		AddJetpackVelocity(FVector(0.0f, 0.0f, 50.0f), HoverGaugePerSec);
		bHoverStoping = false;
	}
	else
	{
		HoverStop();
	}

}

void UJetpackComponent::HoverStop()
{
	UE_LOG(LogTemp, Warning, TEXT("stop hovering"));
	ToGlidingSpeed();
	if(!bHoverStoping)
	{
		GetOwnerCharacterMovement()->Velocity.Z *= 0.1f;
		bHoverStoping = true;
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
		SetHoveringMode(true);
		GetOwnerCharacterMovement()->MaxWalkSpeed = MaxDashSpeed;
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
	GetOwnerCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetOwnerCharacterMovement()->Velocity = ClampToMaxWalkSpeed(GetOwnerCharacterMovement()->Velocity);
}


void UJetpackComponent::Dodge(FVector2D InputValue)
{
	if (JetpackFuel < 0.1f) return;

	// �߷� ���ֱ�
	GetOwnerCharacterMovement()->GravityScale = 0.0f;

	// ���� ��ġ ��¦ �ø� �� �̵�(�ٷ� ���� ���λ��¿��� ����� �ٷ� �������� ���� ����)
	OwnerCharacter->SetActorLocation(OwnerCharacter->GetActorLocation() + FVector(0.0f, 0.0f, 3.0f));

	// ĳ���� �߻�
	FVector	ForwardVector = GetOwnerPlayerController()->GetControlRotation().Vector();
	FVector	RightVector = ForwardVector.RightVector;
	ForwardVector *= InputValue.X;
	RightVector *= InputValue.Y;

	FVector LaunchVelocity = (ForwardVector + RightVector).Normalize()* DodgeSpeed* FVector(1.0f, 1.0f, 0.0f);
	OwnerCharacter->LaunchCharacter(LaunchVelocity,false,false);

	// ���� ���
	SetFuel(JetpackFuel - DodgeReductionGauge);

	// ȸ�� ���� Ÿ�̸� ����
	if (!SlowdownDodgeTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(SlowdownDodgeTimerHandle, this, &ThisClass::SlowdownDodge, 0.2f, false,0.2f);
	}

	//UE_LOG(LogTemp, Warning, TEXT("%f %f"), InputValue.X, InputValue.Y);
}

void UJetpackComponent::SlowdownDodge()
{
	if(GetOwnerCharacterMovement()->Velocity.Length()<600.0f)
	{
		GetOwnerCharacterMovement()->GravityScale = 1.0f;
	}else
	{
		GetOwnerCharacterMovement()->Velocity *= DodgeSlowdownValue;
		GetWorld()->GetTimerManager().SetTimer(SlowdownDodgeTimerHandle, this, &ThisClass::SlowdownDodge, 0.1f, false, 0.1f);
	}
}