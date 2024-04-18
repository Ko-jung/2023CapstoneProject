// Fill out your copyright notice in the Description page of Project Settings.


#include "JetpackComponent.h"

#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"

#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Skyscraper/MainGame/Core/SkyscraperPlayerController.h"

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

		static ConstructorHelpers::FObjectFinder<UInputAction> IA_Jetpack_DodgeRef(TEXT("/Script/EnhancedInput.InputAction'/Game/2019180031/MainGame/Core/Input/Default/IA_GameDefaultMove.IA_GameDefaultMove'"));
		IA_Jetpack_Dodge = IA_Jetpack_DodgeRef.Object;

	}

	for(int i = 0 ; i<(uint8)EDodgeKeys::EDK_SIZE; ++i)
	{
		DodgeKeyDownTime[i] = -1.0f;
		DodgeKeyUpTime[i] = -1.0f;
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
				EnhancedInputComponent->BindAction(IA_Jetpack_Dodge, ETriggerEvent::Triggered, this, &ThisClass::CalcDodgeKeyDownTime);
				EnhancedInputComponent->BindAction(IA_Jetpack_Dodge, ETriggerEvent::Completed, this, &ThisClass::CalcDodgeKeyUpTime);
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
	if (bIsBoostGaugeInfinity)
	{
		UE_LOG(LogTemp, Warning, TEXT("Boost Gauge Infinity Time : %f"),JetpackFuel);
		return;
	}
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

			bIsHovering = true;
			SetCharacterMaxSpeed();
			GetOwnerCharacterMovement()->GravityScale = 0.0f;
			GetOwnerCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
			GetOwnerCharacterMovement()->MaxAcceleration = 50000.0f;
		}
	}
	else   // bHover == false
	{
		OwnerCharacter->SetIsHover(false);
		bIsHovering = false;
		SetCharacterMaxSpeed();
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
		bIsDashing = true;
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

	bIsDashing = false;
	SetCharacterMaxSpeed();
	//GetOwnerCharacterMovement()->Velocity = ClampToMaxWalkSpeed(GetOwnerCharacterMovement()->Velocity);
}

bool UJetpackComponent::CalculateDodgeAxis(EDodgeKeys DodgeKey)
{
	uint8 ArrayIndex = (uint8)DodgeKey;
	
	
	// ���� Ű Input �ð��� ����Ͽ� dodge�� �������� ��ȯ�ϱ�
	{
		// ���� Ű Up �ð��� ���� Down �ð��� 0.5�� �����,
		if(GetWorld()->GetTimeSeconds() - DodgeKeyUpTime[ArrayIndex] < 0.5f)
		{
			// �߰������� ���� Ű Down �ð��� ���� Down �ð� 1.0f ����� ȸ�� ����
			if (GetWorld()->GetTimeSeconds() -DodgeKeyDownTime[ArrayIndex] < 1.0f)
			{
				return true;
			}
		}
		else //���� ȸ�Ǹ� �� �� �ִ� ������ �ƴ϶�� �ð��� �������ش�.
		{
			DodgeKeyDownTime[ArrayIndex] = GetWorld()->GetTimeSeconds();
			return false;
		}
	}
	return false;
}

void UJetpackComponent::CalcDodgeKeyDownTime(const FInputActionValue& InputActionValue)
{
	FVector2D InputValue = InputActionValue.Get<FVector2D>();
	FVector2D DodgeAxis{};
	{ // �Է� �ð� ���� �� �Է� �ð��� �־��� ��� Up �ð��� ����Ͽ� Dodge �������� ���
		// ���� �̵�
		if (InputValue.Y > FLT_EPSILON)
			if (CalculateDodgeAxis(EDodgeKeys::EDK_D)) DodgeAxis.Y += 1.0f;
		// ���� �̵�
		if (InputValue.Y < -FLT_EPSILON)
			if (CalculateDodgeAxis(EDodgeKeys::EDK_A)) DodgeAxis.Y -= 1.0f;
		// ���� �̵�
		if (InputValue.X > FLT_EPSILON)
			if (CalculateDodgeAxis(EDodgeKeys::EDK_W)) DodgeAxis.X	 += 1.0f;
		// �Ĺ� �̵�
		if (InputValue.X < -FLT_EPSILON)
			if (CalculateDodgeAxis(EDodgeKeys::EDK_S)) DodgeAxis.X += 1.0f;

		// ȸ�ǰ� �����ϴٸ�
		if(DodgeAxis.Length() > FLT_EPSILON)
		{
			// ȸ��
			Dodge(DodgeAxis);

			// �� ��ǲ ���� �ʱ�ȭ�ϰ�, �����Ѵ�.
			for(int i = 0; i< (uint8)EDodgeKeys::EDK_SIZE; ++i)
			{
				DodgeKeyDownTime[i] = -1.0f;
				DodgeKeyUpTime[i] = -1.0f;
			}
			
			return;
		}
	}

	return;
}

void UJetpackComponent::CalcDodgeKeyUpTime(const FInputActionValue& InputActionValue)
{
	FVector2D InputValue = InputActionValue.Get<FVector2D>();
	uint8 ArrayIndex = (uint8)EDodgeKeys::EDK_SIZE;
	// ���� �̵�
	if (InputValue.Y > FLT_EPSILON)
		ArrayIndex = (uint8)EDodgeKeys::EDK_D;
	// ���� �̵�
	if (InputValue.Y < -FLT_EPSILON)
		ArrayIndex = (uint8)EDodgeKeys::EDK_A;
	// ���� �̵�
	if (InputValue.X > FLT_EPSILON)
		ArrayIndex = (uint8)EDodgeKeys::EDK_W;
	// �Ĺ� �̵�
	if (InputValue.X < -FLT_EPSILON)
		ArrayIndex = (uint8)EDodgeKeys::EDK_S;

	if(ArrayIndex < (uint8) EDodgeKeys::EDK_SIZE)
	{
		DodgeKeyUpTime[ArrayIndex] = GetWorld()->GetTimeSeconds();
	}
	
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
		GetOwnerCharacterMovement()->MaxWalkSpeed = HoveringMaxSpeed * OwnerCharacter->GetSpeedBuffValue();
		return;
	}

	GetOwnerCharacterMovement()->MaxWalkSpeed = OwnerCharacter->GetCharacterMaxWalkSpeed() * OwnerCharacter->GetSpeedBuffValue();
	
}


void UJetpackComponent::Dodge(FVector2D InputValue)
{

	if (JetpackFuel < 0.1f) return;
	UE_LOG(LogTemp, Warning, TEXT("%f,%f"), InputValue.X, InputValue.Y);
	// �߷� ���ֱ�
	GetOwnerCharacterMovement()->GravityScale = 0.0f;

	// ���� ��ġ ��¦ �ø� �� �̵�(�ٷ� ���� ���λ��¿��� ����� �ٷ� �������� ���� ����)
	OwnerCharacter->SetActorLocation(OwnerCharacter->GetActorLocation() + FVector(0.0f, 0.0f, 3.0f));
	
	// ĳ���� �߻�
	FVector	ForwardVector = OwnerCharacter->GetActorForwardVector();
	FVector	RightVector = OwnerCharacter->GetActorRightVector();
	ForwardVector *= InputValue.X;
	RightVector *= InputValue.Y;

	FVector LaunchVelocity = (ForwardVector + RightVector);
	LaunchVelocity.Normalize();
	LaunchVelocity = LaunchVelocity* DodgeSpeed * FVector(1.0f, 1.0f, 0.0f);
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
	UE_LOG(LogTemp, Warning, TEXT("Boost Gauge Infinity Activate"));

	JetpackFuel = FMath::Max(JetpackFuel, 0.33f);


	if (!BoostGaugeInfinityTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(BoostGaugeInfinityTimerHandle, this, &ThisClass::DeactivateBoostGaugeInfinity, 0.2f, false, InfinityTime);
	}
	else      // Ÿ�̸Ӱ� ������ ���� ���̾��ٸ� (���� ��� ���̾��ٸ�, �ð� �ʱ�ȭ)
	{
		GetWorld()->GetTimerManager().ClearTimer(BoostGaugeInfinityTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(BoostGaugeInfinityTimerHandle, this, &ThisClass::DeactivateBoostGaugeInfinity, 0.2f, false, InfinityTime);
	}
}

void UJetpackComponent::DeactivateBoostGaugeInfinity()
{
	GetWorld()->GetTimerManager().ClearTimer(BoostGaugeInfinityTimerHandle);
	bIsBoostGaugeInfinity = false;
	UE_LOG(LogTemp, Warning, TEXT("Boost Gauge Infinity Deactivate"));
}