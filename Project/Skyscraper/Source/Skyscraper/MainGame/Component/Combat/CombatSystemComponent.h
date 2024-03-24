// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// == Weapon Change function
	void SwapWeapon(UClass* WeaponClass);

	// == Owner Character
	UPROPERTY()
		ASkyscraperCharacter* OwnerCharacter;

	// == Weapon Component Variable
	UPROPERTY()
		UActorComponent* MainWeaponComponent;

	// == Selected weapon class and enum
	TArray<TSubclassOf<UMainMeleeComponent>> MeleeClass;
	TArray<TSubclassOf<UMainRangeComponent>> RangeClass;
	EMeleeSelect MeleeSelect;
	ERangeSelect RangeSelect;


	// == Input action function
	UFUNCTION()
		void SwapToMeleeWeapon(const FInputActionValue& Value);
	UFUNCTION()
		void SwapToRangeWeapon(const FInputActionValue& Value);
	UFUNCTION()
		void LockOn(const FInputActionValue& Value);
public:	
	FORCEINLINE APlayerController* GetOwnerPlayerController() const { return Cast<APlayerController>(OwnerCharacter->GetController()); }



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
