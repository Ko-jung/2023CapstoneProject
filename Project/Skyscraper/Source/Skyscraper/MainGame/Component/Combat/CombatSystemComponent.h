// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Melee/MainMeleeComponent.h"
#include "Range/MainRangeComponent.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "Skyscraper/Enum/EMeleeSelect.h"
#include "Skyscraper/Enum/ERangeSelect.h"
#include "Skyscraper/Enum/ESwapWeapon.h"
#include "CombatSystemComponent.generated.h"


class UEnhancedInputLocalPlayerSubsystem;

UCLASS
( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SKYSCRAPER_API UCombatSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatSystemComponent();

	// == Call right after construct
	void SetInitialSelect(EMeleeSelect eMeleeSelect, ERangeSelect eRangeSelect);

	// == Do Stun / Down Function
	UFUNCTION(BlueprintCallable)
		void Stun(float StunTime, FVector StunDirection);
	UFUNCTION(BlueprintCallable)
		void Down(FVector DownDirection);

	// == Input action function
	UFUNCTION()
		void SwapToMeleeWeapon(const FInputActionValue& Value);
	UFUNCTION()
		void SwapToRangeWeapon(const FInputActionValue& Value);

	// AnimInstance에서 캐릭터의 Idle 상태 애니메이션을 위해 필요한 변수 getter
	// WeaponType - 맨손(0), 근거리(1), 원거리(2)
	// EquippedWeapon - EMeleeSelect/ERangeSelect 값과 동일
	UFUNCTION(BlueprintCallable)
		void GetWeaponEquipStateForAnimation(ESwapWeapon& WeaponType, uint8& EquippedWeapon);

	UFUNCTION()
		void ChangeMeleeWeapon(EMeleeSelect NewMeleeSelect);
	UFUNCTION()
		void ChangeRangeWeapon(ERangeSelect NewRangeSelect);

	EMeleeSelect GetCurrentMeleeSelect() const { return MeleeSelect; }
	ERangeSelect GetCurrentRangeSelect() const { return RangeSelect; }

	void RemoveAllInputMappingTemporary(UEnhancedInputLocalPlayerSubsystem* Subsystem);
	void AddAllInputMappingContext(UEnhancedInputLocalPlayerSubsystem* Subsystem);

	UPROPERTY(EditAnywhere, Category = MeleeValue)
		TArray<float> DaggerAttackTime;
	UPROPERTY(EditAnywhere, Category = MeleeValue)
		TArray<float> KatanaAttackTime;
	UPROPERTY(EditAnywhere, Category = MeleeValue)
		TArray<float> SwordAttackTime;

	UPROPERTY(EditAnywhere, Category = RangeValue)
		float SMG_ReloadTime;
	UPROPERTY(EditAnywhere, Category = RangeValue)
		float SMG_FireTime;
	UPROPERTY(EditAnywhere, Category = RangeValue)
		float AR_ReloadTime;
	UPROPERTY(EditAnywhere, Category = RangeValue)
		float AR_FireTime;
	UPROPERTY(EditAnywhere, Category = RangeValue)
		float RPG_ReloadTime;
	UPROPERTY(EditAnywhere, Category = RangeValue)
		float RPG_FireTime;

	UPROPERTY(EditAnywhere, Category = RangeDistanceValue)
		float SMG_EffectiveDistance;
	UPROPERTY(EditAnywhere, Category = RangeDistanceValue)
		float AR_EffectiveDistance;
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// == Weapon Change function
	void SwapWeapon(UActorComponent* TargetWeaponComponent);

	// == Owner Character
	UPROPERTY()
		ASkyscraperCharacter* OwnerCharacter;
	UPROPERTY()
		UAnimInstance* OwnerAnimInstance;

	//UPROPERTY(EditAnywhere, Category=MotionWarping)
	//	UAnimMontage* AM_Damaged;
	//UPROPERTY(EditAnywhere,Category = MotionWarping)
	//	UAnimMontage* AM_Down;

	// == 무기 컴퍼넌트에 대한 변수
	UPROPERTY()
		UActorComponent* MainWeaponComponent;
	UPROPERTY()
		UActorComponent* MainMeleeWeaponComponent;
	UPROPERTY()
		UActorComponent* MainRangeWeaponComponent;

	// == Selected weapon class and enum
	TArray<TSubclassOf<UMainMeleeComponent>> MeleeClass;
	TArray<TSubclassOf<UMainRangeComponent>> RangeClass;
	EMeleeSelect MeleeSelect;
	ERangeSelect RangeSelect;

	// == LockOn variable
	UPROPERTY()
	float LockOnStartTime;
	UPROPERTY()
	AActor* LockOnActor;
	UPROPERTY()
	float CloseTargetDistance;
	UPROPERTY(EditAnywhere,Category = LockOn)
	float InitTargetDistance;


	UFUNCTION()
		void LockOnKeyFunc(const FInputActionValue& Value);

	// == Action Function
	void LockOn();

	UFUNCTION()
	void OnOutDownMontage(FName NotifyName);

	// 디버깅을 위한 함수
	// 캐릭터 무기 전환
	UFUNCTION(BlueprintCallable)
	void DEBUG_ChangeToNextWeapon();

public:	
	FORCEINLINE APlayerController* GetOwnerPlayerController() const { return Cast<APlayerController>(OwnerCharacter->GetController()); }
	FORCEINLINE UMainRangeComponent* GetRangeComponent() const { return Cast<UMainRangeComponent>(MainRangeWeaponComponent); }
	FORCEINLINE UMainMeleeComponent* GetMeleeComponent() const { return Cast<UMainMeleeComponent>(MainMeleeWeaponComponent); }

private:
	// == Input Action And Input Mapping Context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputMappingContext* IMC_CombatSystem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* IA_MeleeWeaponSelect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* IA_RangeWeaponSelect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* IA_LockOn;


// === 2019180016 ===
public:
	void AddInputMappingContext();
};
