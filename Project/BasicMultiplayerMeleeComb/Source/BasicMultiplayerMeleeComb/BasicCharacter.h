// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "BasicCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class BASICMULTIPLAYERMELEECOMB_API ABasicCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasicCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
protected:
	/* Key Input */
	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UInputMappingContext> IMC_Default;
	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UInputAction> IA_Move;
	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UInputAction> IA_Look;
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	/* 캐릭터의 컴퍼넌트 */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* CameraComponent;


	APlayerController* GetPlayerController() const;
};
