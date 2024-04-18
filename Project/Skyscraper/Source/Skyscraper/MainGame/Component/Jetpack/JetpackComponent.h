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
	// 생성자
	UJetpackComponent();

protected:
	// BeginPlay
	virtual void BeginPlay() override;

	// 플레이어의 최대 속도에 대한 Clamp 함수
	FVector ClampToMaxWalkSpeed(const FVector& NewVelocity);

	// 부스터 연료 설정 함수
	void SetFuel(double NewFuel);
	// 공중 모드 설정 함수
	void SetHoveringMode(bool bHover);
	// 부스터 속력(캐릭터 무브먼트 컴퍼넌트 속력) 변경 함수
	void AddJetpackVelocity(FVector AddVelocity, float FuelReduction);

	// 공중 날기 로직 함수
	void Hover(const FInputActionValue& InputActionValue);
	// 공중 날기 종료 로직 함수
	void HoverStop();

	// 공중 날기 종료시 천천히 낙하(글라이딩) 속도로 변경하는 함수
	void ToGlidingSpeed();

	// 빠른 대쉬 로직 함수
	void DashFast();
	// 빠른 대쉬 종료 로직 함수
	void DashStop();

	// 회피 관련 함수
	void Dodge_Fwd();
	void Dodge_Bwd();
	void Dodge_Right();
	void Dodge_Left();


	// 현재 제트팩의 속성 (bIsHovering / bIsDashing) 에 따라 캐릭터 최대 속도 조정
	void SetCharacterMaxSpeed();

	// 회피(Dodge) 시 속도 감소를 위한 함수
	UFUNCTION()
	void SlowdownDodge();
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 캐릭터가 땅에 닿았을 때(On Landed) 실행될 함수
	UFUNCTION()
	void OnLandJetpack();

	// 회피 로직 함수
	void Dodge(FVector2D InputValue);

	// 부스터 무한 적용 및 해제 함수
	UFUNCTION()
		void ActivateBoostGaugeInfinity(float InfinityTime);
	UFUNCTION()
		void DeactivateBoostGaugeInfinity();


protected:
	// == Owner 캐릭터 관련
	UPROPERTY()
		TObjectPtr<ASkyscraperCharacter> OwnerCharacter;

	// == 제트팩 변수
	// 연료 관련 변수
	UPROPERTY(VisibleAnywhere)
		double JetpackFuel;
	UPROPERTY(EditAnywhere)
		double MaxJetpackFuel;

	// 속도 관련 함수
	UPROPERTY(EditAnywhere)
		float HoveringMaxSpeed;
	UPROPERTY(EditAnywhere)
		float MaxDashSpeed;
	UPROPERTY(EditAnywhere)
		float DodgeSpeed;
	UPROPERTY(EditAnywhere)
		float DodgeSlowdownValue;

	// 게이지 사용 수치 관련 함수
	UPROPERTY(EditAnywhere)
		float HoverGaugePerSec;
	UPROPERTY(EditAnywhere)
		float DashGaugePerSec;
	UPROPERTY(EditAnywhere)
		float DodgeReductionGauge;

	bool bHoverStoping;

	// 부스터 게이지 무한 bool 변수
	UPROPERTY()
		bool bIsBoostGaugeInfinity;

	// 현재 제트팩의 상태에 대한 변수, 캐릭터의 속도를 조정할 때 사용
	bool bIsHovering;
	bool bIsDashing;


	// 타이머 핸들
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
