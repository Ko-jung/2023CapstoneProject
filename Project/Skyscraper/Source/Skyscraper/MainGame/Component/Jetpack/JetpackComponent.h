// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "JetpackComponent.generated.h"


class ASkyscraperCharacter;
class UInputAction;
class UInputMappingContext;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SKYSCRAPER_API UJetpackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UJetpackComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	FVector ClampToMaxWalkSpeed(const FVector& NewVelocity);
	void SetFuel(double NewFuel);
	void SetHoveringMode(bool bHover);
	void AddJetpackVelocity(FVector AddVelocity, float FuelReduction);
	void Hover(const FInputActionValue& InputActionValue);
	void HoverStop();
	void ToGlidingSpeed();
	void DashFast();
	void DashStop();
	void Dodge(const FInputActionValue& InputActionValue);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void OnLandJetpack();
protected:
	// == Owner 캐릭터 관련
	UPROPERTY()
		TObjectPtr<ASkyscraperCharacter> OwnerCharacter;

	// == 제트팩 변수
	UPROPERTY(VisibleAnywhere)
		double JetpackFuel;
	UPROPERTY(EditAnywhere)
		double MaxJetpackFuel;
	UPROPERTY(EditAnywhere)
		float HoveringMaxSpeed;
	UPROPERTY(EditAnywhere)
		float HoverGaugePerSec;
	UPROPERTY(EditAnywhere)
		float DashGaugePerSec;
	UPROPERTY(EditAnywhere)
		float MaxDashSpeed;
	bool bHoverStoping;

protected:
	UFUNCTION()
	FORCEINLINE APlayerController* GetOwnerPlayerController() const { return OwnerCharacter->GetPlayerController(); }
	UFUNCTION()
	FORCEINLINE UCharacterMovementComponent* GetOwnerCharacterMovement() const { return OwnerCharacter->GetCharacterMovement(); }


private:
	// == Input Action And Input Mapping Context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputMappingContext* IMC_Jetpack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* IA_Jetpack_Hover;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* IA_Jetpack_DashFast;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* IA_Jetpack_Dodge;
};
