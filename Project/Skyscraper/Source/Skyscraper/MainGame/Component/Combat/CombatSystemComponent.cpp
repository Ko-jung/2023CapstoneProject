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
#include "Components/InputComponent.h"

// Sets default values for this component's properties
UCombatSystemComponent::UCombatSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	MeleeSelect = EMeleeSelect::EMS_Dagger;
	RangeSelect = ERangeSelect::ERS_Rifle;
	OwnerCharacter = nullptr;
	MainWeaponComponent = nullptr;

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
	// ...
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
	OwnerCharacter = Cast<ASkyscraperCharacter>(GetOwner());

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
				EnhancedInputComponent->BindAction(IA_LockOn, ETriggerEvent::Started, this, &ThisClass::LockOn);
				EnhancedInputComponent->BindAction(IA_LockOn, ETriggerEvent::Completed, this, &ThisClass::LockOn);
			}
		}
	}
	// ...
	
}

void UCombatSystemComponent::SwapWeapon(UClass* WeaponClass)
{
	if(MainWeaponComponent && MainWeaponComponent->IsA(WeaponClass))
	{
		UE_LOG(LogTemp, Warning, TEXT("같은 장비 교체 X"));
		return;
	}

	if(MainWeaponComponent)
	{
		MainWeaponComponent->DestroyComponent();
		MainWeaponComponent = nullptr;
	}

	if(WeaponClass)
	{
		MainWeaponComponent = OwnerCharacter->AddComponentByClass(WeaponClass, false, FTransform(), true);
		MainWeaponComponent->RegisterComponent();
	}
}


void UCombatSystemComponent::SwapToMeleeWeapon(const FInputActionValue& Value)
{
	SwapWeapon(MeleeClass[(uint8)MeleeSelect]);
	FString Name = MeleeClass[(uint8)MeleeSelect]->GetDisplayNameText().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s 무기 교체"), *Name);
}

void UCombatSystemComponent::SwapToRangeWeapon(const FInputActionValue& Value)
{
	SwapWeapon(RangeClass[(uint8)RangeSelect]);
	FString Name = RangeClass[(uint8)RangeSelect]->GetDisplayNameText().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s 무기 교체"), *Name);
}

void UCombatSystemComponent::LockOn(const FInputActionValue& Value)
{
	bool what = Value.Get<bool>();
	if(what)
	{
		UE_LOG(LogTemp, Warning, TEXT("눌림"));
	}else
	{
		UE_LOG(LogTemp, Warning, TEXT("뗌"));
	}
	
}


