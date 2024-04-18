// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "JetpackComponent.generated.h"

enum class EDodgeKeys
{
	EDK_W = 0 , EDK_S, EDK_D, EDK_A, EDK_SIZE
};

class ASkyscraperCharacter;
class UInputAction;
class UInputMappingContext;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SKYSCRAPER_API UJetpackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// ������
	UJetpackComponent();

protected:
	// BeginPlay
	virtual void BeginPlay() override;

	// �÷��̾��� �ִ� �ӵ��� ���� Clamp �Լ�
	FVector ClampToMaxWalkSpeed(const FVector& NewVelocity);

	// �ν��� ���� ���� �Լ�
	void SetFuel(double NewFuel);
	// ���� ��� ���� �Լ�
	void SetHoveringMode(bool bHover);
	// �ν��� �ӷ�(ĳ���� �����Ʈ ���۳�Ʈ �ӷ�) ���� �Լ�
	void AddJetpackVelocity(FVector AddVelocity, float FuelReduction);

	// ���� ���� ���� �Լ�
	void Hover(const FInputActionValue& InputActionValue);
	// ���� ���� ���� ���� �Լ�
	void HoverStop();

	// ���� ���� ����� õõ�� ����(�۶��̵�) �ӵ��� �����ϴ� �Լ�
	void ToGlidingSpeed();

	// ���� �뽬 ���� �Լ�
	void DashFast();
	// ���� �뽬 ���� ���� �Լ�
	void DashStop();

	// ȸ�� ���� �Լ�
	void Dodge_Fwd();
	void Dodge_Bwd();
	void Dodge_Right();
	void Dodge_Left();


	// ���� ��Ʈ���� �Ӽ� (bIsHovering / bIsDashing) �� ���� ĳ���� �ִ� �ӵ� ����
	void SetCharacterMaxSpeed();

	// ȸ��(Dodge) �� �ӵ� ���Ҹ� ���� �Լ�
	UFUNCTION()
	void SlowdownDodge();
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// ĳ���Ͱ� ���� ����� ��(On Landed) ����� �Լ�
	UFUNCTION()
	void OnLandJetpack();

	// ȸ�� ���� �Լ�
	void Dodge(FVector2D InputValue);

	// �ν��� ���� ���� �� ���� �Լ�
	UFUNCTION()
		void ActivateBoostGaugeInfinity(float InfinityTime);
	UFUNCTION()
		void DeactivateBoostGaugeInfinity();


protected:
	// == Owner ĳ���� ����
	UPROPERTY()
		TObjectPtr<ASkyscraperCharacter> OwnerCharacter;

	// == ��Ʈ�� ����
	// ���� ���� ����
	UPROPERTY(VisibleAnywhere)
		double JetpackFuel;
	UPROPERTY(EditAnywhere)
		double MaxJetpackFuel;

	// �ӵ� ���� �Լ�
	UPROPERTY(EditAnywhere)
		float HoveringMaxSpeed;
	UPROPERTY(EditAnywhere)
		float MaxDashSpeed;
	UPROPERTY(EditAnywhere)
		float DodgeSpeed;
	UPROPERTY(EditAnywhere)
		float DodgeSlowdownValue;

	// ������ ��� ��ġ ���� �Լ�
	UPROPERTY(EditAnywhere)
		float HoverGaugePerSec;
	UPROPERTY(EditAnywhere)
		float DashGaugePerSec;
	UPROPERTY(EditAnywhere)
		float DodgeReductionGauge;

	bool bHoverStoping;

	// �ν��� ������ ���� bool ����
	UPROPERTY()
		bool bIsBoostGaugeInfinity;

	// ���� ��Ʈ���� ���¿� ���� ����, ĳ������ �ӵ��� ������ �� ���
	bool bIsHovering;
	bool bIsDashing;


	// Ÿ�̸� �ڵ�
	FTimerHandle SlowdownDodgeTimerHandle;
	FTimerHandle BoostGaugeInfinityTimerHandle;

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
		TArray<UInputAction*> IA_Jetpack_Dodge;
	
	
};
