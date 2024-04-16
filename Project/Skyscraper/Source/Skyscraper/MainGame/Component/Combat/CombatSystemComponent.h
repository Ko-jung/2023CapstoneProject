// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Range/MainRangeComponent.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "Skyscraper/Enum/EMeleeSelect.h"
#include "Skyscraper/Enum/ERangeSelect.h"
#include "CombatSystemComponent.generated.h"


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


	// AnimInstance에서 캐릭터의 Idle 상태 애니메이션을 위해 필요한 변수 getter
	// WeaponType - 맨손(0), 근거리(1), 원거리(2)
	// EquippedWeapon - EMeleeSelect/ERangeSelect 값과 동일
	UFUNCTION(BlueprintCallable)
		void GetWeaponEquipStateForAnimation(uint8& WeaponType, uint8& EquippedWeapon);
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

	// == Input action function
	UFUNCTION()
		void SwapToMeleeWeapon(const FInputActionValue& Value);
	UFUNCTION()
		void SwapToRangeWeapon(const FInputActionValue& Value);
	UFUNCTION()
		void LockOnKeyFunc(const FInputActionValue& Value);


	// == Action Function
	void LockOn();


	UFUNCTION()
	void OnOutDownMontage(UAnimMontage* Montage, bool bInterrupted);
public:	
	FORCEINLINE APlayerController* GetOwnerPlayerController() const { return Cast<APlayerController>(OwnerCharacter->GetController()); }
	FORCEINLINE UMainRangeComponent* GetRangeComponent() const { return Cast<UMainRangeComponent>(MainRangeWeaponComponent); }


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

};
