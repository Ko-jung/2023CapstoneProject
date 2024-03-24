// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Skyscraper/Enum/ECharacterSelect.h"
#include "Skyscraper/Enum/EMeleeSelect.h"
#include "Skyscraper/Enum/ERangeSelect.h"
#include "SelectCharacterController.generated.h"



class USelectCharacter;
class USelectDetail;
UCLASS()
class SKYSCRAPER_API ASelectCharacterController : public APlayerController
{
	GENERATED_BODY()
public:
	ASelectCharacterController();	
private:
	virtual void BeginPlay() override;

	UPROPERTY()
		TObjectPtr<USelectCharacter> CharacterSelectionWidget;
	UPROPERTY()
		TObjectPtr<USelectDetail> SelectDetailWidget;
	UPROPERTY()
		TSubclassOf<USelectCharacter> CharacterSelectionWidgetClass;
	UPROPERTY()
		TSubclassOf<USelectDetail> SelectDetailWidgetClass;
	
	ECharacterSelect ESelectedCharacter;
	EMeleeSelect ESelectedMeleeWeapon;
	ERangeSelect ESelectedRangeWeapon;
public:
	/* Getter / Setter */
	FORCEINLINE ECharacterSelect GetSelectedCharacter() const { return ESelectedCharacter; }
	FORCEINLINE EMeleeSelect GetSelectedMeleeWeapon() const { return ESelectedMeleeWeapon; }
	FORCEINLINE ERangeSelect GetSelectedRangeWeapon() const { return ESelectedRangeWeapon; }
	FORCEINLINE void SetSelectedCharacter(ECharacterSelect Data) { ESelectedCharacter = Data; }
	FORCEINLINE void SetSelectedMeleeWeapon(EMeleeSelect Data) { ESelectedMeleeWeapon = Data; }
	FORCEINLINE void SetSelectedRangeWeapon(ERangeSelect Data) { ESelectedRangeWeapon = Data; }


	UFUNCTION()
		void SetDetailWidgetVisibility(bool bVisible) const;
};
