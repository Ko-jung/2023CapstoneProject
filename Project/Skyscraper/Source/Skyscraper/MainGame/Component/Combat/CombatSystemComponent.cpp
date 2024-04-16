// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystemComponent.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "Skyscraper/MainGame/Component/Combat/Melee/MainMeleeComponent.h"
#include "Skyscraper/MainGame/Component/Combat/Melee/DaggerComponent.h"
#include "Skyscraper/MainGame/Component/Combat/Melee/KatanaComponent.h"
#include "Skyscraper/MainGame/Component/Combat/Melee/GreatSwordComponent.h"
#include "Skyscraper/MainGame/Component/Combat/Range/MainRangeComponent.h"
#include "Skyscraper/MainGame/Component/Combat/Range/SMGComponent.h"
#include "Skyscraper/MainGame/Component/Combat/Range/RifleComponent.h"
#include "Skyscraper/MainGame/Component/Combat/Range/RPGComponent.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MotionWarpingComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UCombatSystemComponent::UCombatSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	MeleeSelect = EMeleeSelect::EMS_GreatSword;
	RangeSelect = ERangeSelect::ERS_Rifle;
	OwnerCharacter = nullptr;
	OwnerAnimInstance = nullptr;
	MainMeleeWeaponComponent = nullptr;
	MainRangeWeaponComponent = nullptr;
	LockOnStartTime = 0.0f;
	LockOnActor = nullptr;
	CloseTargetDistance = InitTargetDistance = 10000.0f;

	{ // == Set Input Asset
		static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_CombatSystemRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/2019180031/MainGame/Core/Input/Combat/IMC_CombatSystem.IMC_CombatSystem'"));
		IMC_CombatSystem = IMC_CombatSystemRef.Object;

		static ConstructorHelpers::FObjectFinder<UInputAction> IA_MeleeWeaponSelectRef(TEXT("/Script/EnhancedInput.InputAction'/Game/2019180031/MainGame/Core/Input/Combat/IA_MeleeWeaponSelect.IA_MeleeWeaponSelect'"));
		IA_MeleeWeaponSelect = IA_MeleeWeaponSelectRef.Object;

		static ConstructorHelpers::FObjectFinder<UInputAction> IA_RangeWeaponSelectRef(TEXT("/Script/EnhancedInput.InputAction'/Game/2019180031/MainGame/Core/Input/Combat/IA_RangeWeaponSelect.IA_RangeWeaponSelect'"));
		IA_RangeWeaponSelect = IA_RangeWeaponSelectRef.Object;

		static ConstructorHelpers::FObjectFinder<UInputAction> IA_LockOnRef(TEXT("/Script/EnhancedInput.InputAction'/Game/2019180031/MainGame/Core/Input/Combat/IA_LockOn.IA_LockOn'"));
		IA_LockOn = IA_LockOnRef.Object;
	}

	{ // Set Weapon Components
		MeleeClass.Add(UDaggerComponent::StaticClass());
		MeleeClass.Add(UKatanaComponent::StaticClass());
		MeleeClass.Add(UGreatSwordComponent::StaticClass());

		RangeClass.Add(USMGComponent::StaticClass());
		RangeClass.Add(URifleComponent::StaticClass());
		RangeClass.Add(URPGComponent::StaticClass());
	}

}

void UCombatSystemComponent::SetInitialSelect(EMeleeSelect eMeleeSelect, ERangeSelect eRangeSelect)
{
	MeleeSelect = eMeleeSelect;
	RangeSelect = eRangeSelect;
}


// Called when the game starts
void UCombatSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	{ // == Get Owner Character And Anim Instance
		OwnerCharacter = Cast<ASkyscraperCharacter>(GetOwner());
		OwnerAnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();
		OwnerAnimInstance->OnMontageBlendingOut.AddDynamic(this, &ThisClass::OnOutDownMontage);
		OwnerAnimInstance->OnMontageEnded.AddDynamic(this, &ThisClass::OnOutDownMontage);
	}

	{ // 소유 캐릭터에 근접 및 원거리 무기 컴퍼넌트 생성
		MainMeleeWeaponComponent =OwnerCharacter->AddComponentByClass(MeleeClass[(uint8)MeleeSelect], false, FTransform(), true);
		MainMeleeWeaponComponent->RegisterComponent();

		MainRangeWeaponComponent = OwnerCharacter->AddComponentByClass(RangeClass[(uint8)RangeSelect], false, FTransform(), true);
		MainRangeWeaponComponent->RegisterComponent();

		SwapToRangeWeapon(FInputActionValue());
	}

	//Add Input Mapping Context
	if (APlayerController* PlayerController = GetOwnerPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC_CombatSystem, 0);

			if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
			{
				EnhancedInputComponent->BindAction(IA_MeleeWeaponSelect, ETriggerEvent::Started, this, &ThisClass::SwapToMeleeWeapon);
				EnhancedInputComponent->BindAction(IA_RangeWeaponSelect, ETriggerEvent::Started, this, &ThisClass::SwapToRangeWeapon);
				EnhancedInputComponent->BindAction(IA_LockOn, ETriggerEvent::Started, this, &ThisClass::LockOnKeyFunc);
				EnhancedInputComponent->BindAction(IA_LockOn, ETriggerEvent::Triggered, this, &ThisClass::LockOn);
				EnhancedInputComponent->BindAction(IA_LockOn, ETriggerEvent::Completed, this, &ThisClass::LockOnKeyFunc);
			}
		}
	}
	// ...
	
}

void UCombatSystemComponent::SwapWeapon(UActorComponent* TargetWeaponComponent)
{
	if(MainWeaponComponent == TargetWeaponComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("같은 장비 교체 X"));
		return;
	}

	// 무기를 착용 중일때는 기존 무기 Input 및 무기 제거
	
	if(MainWeaponComponent)
	{
		if(UMainMeleeComponent* MeleeComp = Cast<UMainMeleeComponent>(MainWeaponComponent))
		{
			MeleeComp->RemoveThisWeapon();
		}
		else if (UMainRangeComponent* RangeComp = Cast<UMainRangeComponent>(MainWeaponComponent))
		{
			RangeComp->RemoveThisWeapon();
		}
	}
	
	if (UMainMeleeComponent* MeleeComp = Cast<UMainMeleeComponent>(TargetWeaponComponent))
	{
		MeleeComp->AddThisWeapon();
	}
	else if (UMainRangeComponent* RangeComp = Cast<UMainRangeComponent>(TargetWeaponComponent))
	{
		RangeComp->AddThisWeapon();
	}

	MainWeaponComponent = TargetWeaponComponent;

	
}


void UCombatSystemComponent::SwapToMeleeWeapon(const FInputActionValue& Value)
{
	SwapWeapon(MainMeleeWeaponComponent);
}

void UCombatSystemComponent::SwapToRangeWeapon(const FInputActionValue& Value)
{
	SwapWeapon(MainRangeWeaponComponent);
}

void UCombatSystemComponent::LockOnKeyFunc(const FInputActionValue& Value)
{
	bool bKeyDown = Value.Get<bool>();
	if(bKeyDown)
	{
		LockOnStartTime = GetWorld()->GetTimeSeconds();

	}else
	{
		LockOnActor = nullptr;
		CloseTargetDistance = InitTargetDistance;
	}
	
}

void UCombatSystemComponent::LockOn()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASkyscraperCharacter::StaticClass(), OutActors);
	int32 LockOnActorCount = 0;

	// == find nearest TargetActor in LockOnRange
	for(AActor* TargetActor : OutActors)
	{
		// == If not self character,
		if(TargetActor != OwnerCharacter)
		{
			// == Get TargetActor Screen Location
			FVector2D ScreenLocation(0.0f, 0.0f);;
			UGameplayStatics::ProjectWorldToScreen(OwnerCharacter->GetPlayerController(), TargetActor->GetActorLocation(),ScreenLocation);

			// == Get Player Viewport size
			FVector2D ViewportSize = UWidgetLayoutLibrary::GetViewportSize(GetWorld());

			// == Get distance from TargetActor's ScreenLocation and Viewport center
			float Distance = UKismetMathLibrary::Distance2D(ScreenLocation, ViewportSize / 2);

			// == if TargetActor's screenlocation is far from center point, find next
			// == ViewportSize.X / 10.0f is LockOnRange => can make to variable
			if (!(Distance < ViewportSize.X / 10.0f)) continue;

			LockOnActorCount += 1;

			// == find nearest TargetActor
			if (Distance < CloseTargetDistance) 
			{
				LockOnActor = TargetActor;
				CloseTargetDistance = Distance;
			}
		}
	}

	if(LockOnActorCount == 0)
	{
		CloseTargetDistance = InitTargetDistance;
		LockOnActor = nullptr;
	}

	if(LockOnActor)
	{
		float LockOnSpeed{};
		// == In first 0.5 sec, fast else slow
		if((GetWorld()->GetTimeSeconds() - LockOnStartTime)< 0.5f)
		{
			LockOnSpeed = 20.0f;
		}else
		{
			LockOnSpeed = 2.0f;
		}


		FRotator CurrentRotator = OwnerCharacter->GetPlayerController()->GetControlRotation();
		FRotator TargetRotator = 
			(LockOnActor->GetActorLocation() - OwnerCharacter->GetFollowCamera()->GetComponentLocation()).ToOrientationRotator();
		FRotator NewRotator = UKismetMathLibrary::RInterpTo(CurrentRotator, TargetRotator, GetWorld()->GetDeltaSeconds(), LockOnSpeed);

		OwnerCharacter->GetPlayerController()->SetControlRotation(NewRotator);
	}


}

void UCombatSystemComponent::Stiffness(float StiffnessTime, FVector StiffnessDirection)
{
	if (StiffnessTime <= FLT_EPSILON) return;
	if (OwnerCharacter->IsCharacterGodMode()) return;	// 무적이면 경직 먹지 않도록

	// 캐릭터와 경직 방향의 각도 구하기
	float AngleD = FMath::RadiansToDegrees(FMath::Acos(StiffnessDirection.GetSafeNormal().Dot(OwnerCharacter->GetActorForwardVector().GetSafeNormal())));

	UAnimMontage* Montage = nullptr;
	// 캐릭터가 뒤에서 공격받은 상황
	if(AngleD < 90.0f)
	{
		Montage = OwnerCharacter->GetAnimMontage(ECharacterAnimMontage::ECAM_Stiffness_Bwd);
		
	}
	// 캐릭터가 앞에서 공격받은 상황
	else
	{
		Montage = OwnerCharacter->GetAnimMontage(ECharacterAnimMontage::ECAM_Stiffness);
	}

	if(Montage)
	{
		const float DamagedAnimPlayRate = Montage->GetPlayLength() / StiffnessTime;
		OwnerAnimInstance->Montage_Play(Montage, DamagedAnimPlayRate);
	}
	

	// 방향으로 800.0f 의 힘으로 경직
	OwnerCharacter->LaunchCharacter(StiffnessDirection * 800.0f, true, false);
}

void UCombatSystemComponent::Down(FVector DownDirection)
{
	if (OwnerCharacter->IsCharacterGodMode()) return;	// 무적이면 다운 당하지 않도록


	// 캐릭터와 경직 방향의 각도 구하기
	float AngleD = FMath::RadiansToDegrees(FMath::Acos(DownDirection.GetSafeNormal().Dot(OwnerCharacter->GetActorForwardVector().GetSafeNormal())));


	UAnimMontage* Montage = nullptr;
	// 캐릭터가 뒤에서 공격받은 상황
	if (AngleD < 90.0f)
	{
		Montage = OwnerCharacter->GetAnimMontage(ECharacterAnimMontage::ECAM_Down_Bwd);

	}
	// 캐릭터가 앞에서 공격받은 상황
	else
	{
		Montage = OwnerCharacter->GetAnimMontage(ECharacterAnimMontage::ECAM_Down);
	}

	if(Montage)
	{
		{ // == Play Down Montage
			OwnerCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
			OwnerAnimInstance->Montage_Play(Montage);
		}

		// 다운 힘 = 1000.0f
		DownDirection *= 1000.0f;
		OwnerCharacter->LaunchCharacter(FVector(DownDirection.X, DownDirection.Y, 750.0f), false, true);
	}
	
}

void UCombatSystemComponent::GetWeaponEquipStateForAnimation(uint8& WeaponType, uint8& EquippedWeapon)
{
	if(MainWeaponComponent)
	{
		if(MainWeaponComponent == MainMeleeWeaponComponent)
		{
			WeaponType = 1;	//근거리 장비 착용중
			EquippedWeapon = (uint8)MeleeSelect;
		}
		else if (MainWeaponComponent == MainRangeWeaponComponent)
		{
			WeaponType = 2; // 원거리 장비 착용중
			EquippedWeapon = (uint8)RangeSelect;
		}
	}
	else
	{
		WeaponType = 0;		// 맨손
	}
}

void UCombatSystemComponent::OnOutDownMontage(UAnimMontage* Montage, bool bInterrupted)
{
	OwnerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}



