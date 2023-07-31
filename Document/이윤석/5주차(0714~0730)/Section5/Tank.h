// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyBasePawn.h"
#include "InputActionValue.h"
#include "Tank.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class UDEMYSECTION05_API ATank : public AMyBasePawn
{
	GENERATED_BODY()

public:
	ATank();
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void HandleDestruction();
	APlayerController* GetTankPlayerController() const { return PlayerController; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;




private:
	UPROPERTY(EditAnywhere, Category = "Property")
	float Speed = 600.0f;
	UPROPERTY(EditAnywhere, Category = "Property")
	float TurnRate = 45.0f;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArm;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> Camera;


	//���ǰ� �ƴ϶� https://intunknown.tistory.com/641 �� ���� ������
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMapping;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MovementAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> RotateAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> FireAction;

	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;

	void Move(const FInputActionValue& value);
	void Rotate(const FInputActionValue& value);
	
};
