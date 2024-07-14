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
#include "Skyscraper/MainGame/Core/SkyscraperPlayerController.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MotionWarpingComponent.h"
#include "PlayMontageCallbackProxy.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Skyscraper/MainGame/Widget/LockOn/LockOnWidget.h"

// Sets default values for this component's properties
UCombatSystemComponent::UCombatSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	MeleeSelect = EMeleeSelect::EMS_Katana;
	RangeSelect = ERangeSelect::ERS_RPG;
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

	// Set Weapon Components
	{ 
		MeleeClass.Add(UDaggerComponent::StaticClass());
		MeleeClass.Add(UKatanaComponent::StaticClass());
		MeleeClass.Add(UGreatSwordComponent::StaticClass());

		RangeClass.Add(USMGComponent::StaticClass());
		RangeClass.Add(URifleComponent::StaticClass());
		RangeClass.Add(URPGComponent::StaticClass());
	}

	// 공격 시간 디폴트 값
	{
		DaggerAttackTime.Add(0.4f);
		DaggerAttackTime.Add(0.4f);
		DaggerAttackTime.Add(0.6f);
		DaggerAttackTime.Add(0.4f);
		DaggerAttackTime.Add(0.6f);

		KatanaAttackTime.Add(0.6f);
		KatanaAttackTime.Add(0.6f);
		KatanaAttackTime.Add(0.8f);
		KatanaAttackTime.Add(1.0f);

		SwordAttackTime.Add(0.8f);
		SwordAttackTime.Add(1.0f);
		SwordAttackTime.Add(0.8f);

		SMG_FireTime = 0.2f;
		SMG_ReloadTime = 1.0f;
		SMG_EffectiveDistance = 4000.0f;

		AR_FireTime = 0.3f;
		AR_ReloadTime = 3.0f;
		AR_EffectiveDistance = 6000.0f;

		RPG_FireTime = 1.0f;
		RPG_ReloadTime = 5.0f;

	}

}

void UCombatSystemComponent::SetInitialSelect(EMeleeSelect eMeleeSelect, ERangeSelect eRangeSelect)
{
	MeleeSelect = eMeleeSelect;
	RangeSelect = eRangeSelect;
	if(MainMeleeWeaponComponent)
	{
		MainMeleeWeaponComponent->DestroyComponent();
		MainMeleeWeaponComponent = OwnerCharacter->AddComponentByClass(MeleeClass[(uint8)MeleeSelect], false, FTransform(), true);
		MainMeleeWeaponComponent->RegisterComponent();
	}
	if(MainRangeWeaponComponent)
	{
		MainRangeWeaponComponent->DestroyComponent();
		MainRangeWeaponComponent = OwnerCharacter->AddComponentByClass(RangeClass[(uint8)RangeSelect], false, FTransform(), true);
		MainRangeWeaponComponent->RegisterComponent();
	}
	
}


// Called when the game starts
void UCombatSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	{ // == Get Owner Character And Anim Instance
		OwnerCharacter = Cast<ASkyscraperCharacter>(GetOwner());
		OwnerAnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();
	}

	{ // 소유 캐릭터에 근접 및 원거리 무기 컴퍼넌트 생성
		MainMeleeWeaponComponent =OwnerCharacter->AddComponentByClass(MeleeClass[(uint8)MeleeSelect], false, FTransform(), true);
		MainMeleeWeaponComponent->RegisterComponent();

		MainRangeWeaponComponent = OwnerCharacter->AddComponentByClass(RangeClass[(uint8)RangeSelect], false, FTransform(), true);
		MainRangeWeaponComponent->RegisterComponent();

		SwapToRangeWeapon(FInputActionValue());
	}

	//Add Input Mapping Context
	AddInputMappingContext();
	BindingInputActions();

	// ...
	
}

void UCombatSystemComponent::AddInputMappingContext()
{
	if (APlayerController* PlayerController = GetOwnerPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC_CombatSystem, 0);
			
			
		}
	}
}

void UCombatSystemComponent::BindingInputActions()
{
	if (!OwnerCharacter->GetPlayerController()) return;

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(OwnerCharacter->GetPlayerController()->InputComponent))
	{
		EnhancedInputComponent->BindAction(IA_MeleeWeaponSelect, ETriggerEvent::Started, this, &ThisClass::SwapToMeleeWeapon);
		EnhancedInputComponent->BindAction(IA_RangeWeaponSelect, ETriggerEvent::Started, this, &ThisClass::SwapToRangeWeapon);
		EnhancedInputComponent->BindAction(IA_LockOn, ETriggerEvent::Started, this, &ThisClass::LockOnKeyFunc);
		EnhancedInputComponent->BindAction(IA_LockOn, ETriggerEvent::Triggered, this, &ThisClass::LockOn);
		EnhancedInputComponent->BindAction(IA_LockOn, ETriggerEvent::Completed, this, &ThisClass::LockOnKeyFunc);
	}
}

void UCombatSystemComponent::SwapWeapon(UActorComponent* TargetWeaponComponent)
{
	if (OwnerAnimInstance->IsAnyMontagePlaying())
	{
		UE_LOG(LogTemp, Warning, TEXT("행동 중 무기 교체 불가"));
		return;
	}

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
	if (OwnerCharacter->DisableLockOn) return;

	bool bKeyDown = Value.Get<bool>();
	if(bKeyDown)
	{
		LockOnStartTime = GetWorld()->GetTimeSeconds();
		if(GetOwnerPlayerController())
		{
			GetOwnerPlayerController()->GetLockOnWidget()->SetVisibility(ESlateVisibility::Visible);
		}
	}else
	{
		LockOnActor = nullptr;
		CloseTargetDistance = InitTargetDistance;
		GetOwnerPlayerController()->GetLockOnWidget()->SetVisibility(ESlateVisibility::Hidden);
	}
	
}

void UCombatSystemComponent::LockOn()
{
	if (OwnerCharacter->DisableLockOn) return;

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASkyscraperCharacter::StaticClass(), OutActors);
	int32 LockOnActorCount = 0;
	FVector2D ViewportSize = UWidgetLayoutLibrary::GetViewportSize(GetWorld());
	FVector2D TargetActorScreenLocation{};

	// == find nearest TargetActor in LockOnRange
	for(AActor* TargetActor : OutActors)
	{
		ASkyscraperCharacter* TargetCharacter = Cast<ASkyscraperCharacter>(TargetActor);	// 2019180016
																							//	TargetActor -> TargetCharacter
		// == If not self character,
		if(TargetCharacter != OwnerCharacter && TargetCharacter->CanEnemyLockOnMe)
		{
			// == Get TargetActor Screen Location
			FVector2D ScreenLocation(0.0f, 0.0f);
			UGameplayStatics::ProjectWorldToScreen(OwnerCharacter->GetPlayerController(), TargetCharacter->GetActorLocation(),ScreenLocation);

			// == Get Player Viewport size
			//FVector2D ViewportSize = UWidgetLayoutLibrary::GetViewportSize(GetWorld());

			// == Get distance from TargetActor's ScreenLocation and Viewport center
			float Distance = UKismetMathLibrary::Distance2D(ScreenLocation, ViewportSize / 2);

			// == if TargetActor's screenlocation is far from center point, find next
			// == ViewportSize.X / 10.0f is LockOnRange => can make to variable
			if (!(Distance < ViewportSize.X / 10.0f)) continue;

			LockOnActorCount += 1;

			// == find nearest TargetActor
			if (Distance < CloseTargetDistance || TargetCharacter == LockOnActor) 
			{
				LockOnActor = TargetCharacter;
				CloseTargetDistance = Distance;
				TargetActorScreenLocation = ScreenLocation;
			}
		}
	}

	if(LockOnActorCount == 0)
	{
		CloseTargetDistance = InitTargetDistance;
		LockOnActor = nullptr;
		if (GetOwnerPlayerController() && GetOwnerPlayerController()->GetLockOnWidget())
		{
			GetOwnerPlayerController()->GetLockOnWidget()->SetTargetLockImageVisibie(false);
		}
	}

	if(LockOnActor)
	{
		if(GetOwnerPlayerController() && GetOwnerPlayerController()->GetLockOnWidget())
		{
			GetOwnerPlayerController()->GetLockOnWidget()->SetTargetLockImageVisibie(true);
			GetOwnerPlayerController()->GetLockOnWidget()->SetTargetLockImageAlignment(ViewportSize, TargetActorScreenLocation);
		}

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

void UCombatSystemComponent::Stun(float StunTime, FVector StunDirection)
{
	if (StunTime <= FLT_EPSILON) return;
	if (OwnerCharacter->IsCharacterGodMode()) return;	// 무적이면 경직 먹지 않도록

	// 캐릭터와 경직 방향의 각도 구하기
	float AngleD = FMath::RadiansToDegrees(FMath::Acos(StunDirection.GetSafeNormal().Dot(OwnerCharacter->GetActorForwardVector().GetSafeNormal())));

	ECharacterAnimMontage NowMontageType = ECharacterAnimMontage::ECAM_Stun;
	UAnimMontage* Montage = OwnerCharacter->GetAnimMontage(NowMontageType);
	FName StartingSection{};
	int SectionNum = -1;
	// 캐릭터가 뒤에서 공격받은 상황
	if(AngleD < 90.0f)
	{
		StartingSection = FName(*(FString("Stun_Bwd")));
		SectionNum = 0;
	}
	// 캐릭터가 앞에서 공격받은 상황
	else
	{
		StartingSection = FName(*(FString("Stun_Fwd")));
		SectionNum = 1;
	}

	if(Montage)
	{
		{	// Montage Sync
			OwnerCharacter->SendAnimMontageStatus(NowMontageType, SectionNum);
		}

		float AttackAnimPlayRate = Montage->GetSectionLength(SectionNum) / StunTime;
		UE_LOG(LogClass, Warning, TEXT("UCombatSystemComponent::Stun StunTime is %f"), StunTime);
		const float DamagedAnimPlayRate = Montage->GetPlayLength();
		
		UPlayMontageCallbackProxy* PlayMontageCallbackProxy = UPlayMontageCallbackProxy::CreateProxyObjectForPlayMontage(OwnerCharacter->GetMesh(), Montage, DamagedAnimPlayRate, 0, StartingSection);
	}
	

	// 방향으로 800.0f 의 힘으로 경직
	OwnerCharacter->LaunchCharacter(StunDirection * 800.0f, true, false);
}

void UCombatSystemComponent::Down(FVector DownDirection)
{
	if (OwnerCharacter->IsCharacterGodMode()) return;	// 무적이면 다운 당하지 않도록


	// 캐릭터와 경직 방향의 각도 구하기
	float AngleD = FMath::RadiansToDegrees(FMath::Acos(DownDirection.GetSafeNormal().Dot(OwnerCharacter->GetActorForwardVector().GetSafeNormal())));


	ECharacterAnimMontage NowMontageType = ECharacterAnimMontage::ECAM_Down;
	UAnimMontage* Montage = OwnerCharacter->GetAnimMontage(NowMontageType);
	

	if(Montage)
	{
		FName StartingSection{};
		FRotator NewRotator{};
		// 캐릭터가 뒤에서 공격받은 상황
		if (AngleD < 90.0f)
		{
			StartingSection = FName(*(FString("Down_Bwd")));
			NewRotator = DownDirection.Rotation();
		}
		// 캐릭터가 앞에서 공격받은 상황
		else
		{
			StartingSection = FName(*(FString("Down_Fwd")));
			NewRotator = (DownDirection * -1.0f).Rotation();
		}
		NewRotator.Pitch = -45.0f;

		{	// Montage Sync
			OwnerCharacter->SendAnimMontageStatus(NowMontageType, Montage->GetSectionIndex(StartingSection));
		}

		{ // == Play Down Montage
			OwnerCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
			UPlayMontageCallbackProxy* PlayMontageCallbackProxy = UPlayMontageCallbackProxy::CreateProxyObjectForPlayMontage(OwnerCharacter->GetMesh(), Montage, 1.0f, 0, StartingSection);
			PlayMontageCallbackProxy->OnBlendOut.AddDynamic(this, &ThisClass::OnOutDownMontage);
			
		}

		{ // 캐릭터 공격 방향으로 시선 확 돌리기
			OwnerCharacter->GetController()->SetControlRotation(NewRotator);
			//OwnerCharacter->SetActorRotation(NewRotator);
		}

		// 다운 힘 = 1000.0f
		DownDirection *= 1000.0f;
		OwnerCharacter->LaunchCharacter(FVector(DownDirection.X, DownDirection.Y, 750.0f), false, true);

		// 캐릭터 중력 적용시키기
		if(UCharacterMovementComponent* CharacterMovement = OwnerCharacter->GetCharacterMovement())
		{
			CharacterMovement->GravityScale = 2.0f;
		}
		
	}
	
}

void UCombatSystemComponent::GetWeaponEquipStateForAnimation(ESwapWeapon& WeaponType, uint8& EquippedWeapon)
{
	if(MainWeaponComponent)
	{
		if(MainWeaponComponent == MainMeleeWeaponComponent)
		{
			// (uint8& WeaponType) -> (ESwapWeapon& WeaponType)
			//WeaponType = (uint8)ESwapWeapon::MeleeWeapon;	//근거리 장비 착용중

			WeaponType = ESwapWeapon::MeleeWeapon;	//근거리 장비 착용중
			EquippedWeapon = (uint8)MeleeSelect;
		}
		else if (MainWeaponComponent == MainRangeWeaponComponent)
		{
			WeaponType = ESwapWeapon::RangeWeapon; // 원거리 장비 착용중
			EquippedWeapon = (uint8)RangeSelect;
		}
	}
	else
	{
		WeaponType = ESwapWeapon::NullWeapon;		// 맨손
	}
}

void UCombatSystemComponent::OnOutDownMontage(FName NotifyName)
{
	OwnerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void UCombatSystemComponent::DEBUG_ChangeToNextWeapon()
{
	EMeleeSelect NewMeleeSelect = (EMeleeSelect)(((uint8)(MeleeSelect) + 1) % ((uint8)(EMeleeSelect::EMS_NONE)));
	ERangeSelect NewRangeSelect = (ERangeSelect)(((uint8)(RangeSelect)+1) % ((uint8)(ERangeSelect::ERS_NONE)));
	SetInitialSelect(NewMeleeSelect, NewRangeSelect);
	SwapToMeleeWeapon(FInputActionValue());
}

ASkyscraperPlayerController* UCombatSystemComponent::GetOwnerPlayerController() const
{
	return OwnerCharacter->GetPlayerController(); 
}

void UCombatSystemComponent::ChangeMeleeWeapon(EMeleeSelect NewMeleeSelect)
{
	SetInitialSelect(NewMeleeSelect, RangeSelect);
	SwapToMeleeWeapon(FInputActionValue());
}

void UCombatSystemComponent::ChangeRangeWeapon(ERangeSelect NewRangeSelect)
{
	SetInitialSelect(MeleeSelect, NewRangeSelect);
	SwapToRangeWeapon(FInputActionValue());
}

void UCombatSystemComponent::RemoveAllInputMappingTemporary(UEnhancedInputLocalPlayerSubsystem* Subsystem)
{
	Subsystem->RemoveMappingContext(IMC_CombatSystem);

	if(UMainMeleeComponent* MeleeComponent = Cast<UMainMeleeComponent>(MainWeaponComponent))
	{
		MeleeComponent->RemoveInputMappingContext();
	}
	else if(UMainRangeComponent* RangeComponent = Cast<UMainRangeComponent>(MainWeaponComponent))
	{
		RangeComponent->RemoveInputMappingContext();
	}
}

void UCombatSystemComponent::AddAllInputMappingContext(UEnhancedInputLocalPlayerSubsystem* Subsystem)
{
	//Subsystem->AddMappingContext(IMC_CombatSystem, 0);
	AddInputMappingContext();

	if (UMainMeleeComponent* MeleeComponent = Cast<UMainMeleeComponent>(MainWeaponComponent))
	{
		MeleeComponent->AddInputMappingContext();
	}
	else if (UMainRangeComponent* RangeComponent = Cast<UMainRangeComponent>(MainWeaponComponent))
	{
		RangeComponent->AddInputMappingContext();
	}
}




