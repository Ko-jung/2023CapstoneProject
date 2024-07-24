// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"

//#include "../../Common/EnumDef.h"
#include "../../../Enum/EHealthState.h"

#include "HealthComponent.generated.h"

class UMyHealthWidget;
class UTextRenderComponent;
class UProgressBar;
class UWidgetComponent;
class UHealthBar;
class ASkyscraperCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SKYSCRAPER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

private:
	// 체력 상태 변수
	UPROPERTY(VisibleAnywhere, Category = Health)
		float CurrentHealth;
	UPROPERTY(EditAnywhere, Category = Health)
		float MaxHealth;
	UPROPERTY()
		float OriginMaxHealth;
	EHealthState LivingState;

	// 컴퍼넌트 소유 캐릭터
	UPROPERTY()
		ASkyscraperCharacter* OwnerCharacter;

	// 위젯 컴퍼넌트 관련 변수
	UPROPERTY(EditAnywhere)
		UWidgetComponent* HealthBarWidgetComponent;
	UPROPERTY(VisibleAnywhere)
		UClass* HealthBarWidgetClass;
	UPROPERTY()
		TObjectPtr<UHealthBar> HealthProgressBar;

	// 캐릭터 무적 bool 변수
	UPROPERTY()
		bool bIsGodMode;
	UPROPERTY()
		UTextRenderComponent* GodModeTextRender;

	// 캐릭터 무적 타이머 핸들
	UPROPERTY()
		FTimerHandle GodModeTimerHandle;

	// 체력 증가 타이머 핸들
	UPROPERTY()
		FTimerHandle PlusHealthBuffTimerHandle;

	// MyHealth 위젯에 대한 클래스 및 변수
	TSubclassOf<UUserWidget> MyHealthWidgetClass;
	UPROPERTY()
		UMyHealthWidget* MyHealthWidget;

	// 적군에게 공격 받을 시 일정 시간 동안 보여주게 하기 위한 타이머 및 변수들
	UPROPERTY()
		FTimerHandle VisibleHealthPBTimerHandle;
	UPROPERTY()
		float VisibleTime = 10.0f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// 캐릭터 무적 시간(타이머) 종료시 실행될 함수
	UFUNCTION()
		void DeactivateGodMode();
	// 캐릭터 추가 체력 시간(타이머) 종료시 실행될 함수
	UFUNCTION()
		void DeactivatePlusHealth();
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 캐릭터 생존 상태 변수 Getter
	FORCEINLINE EHealthState GetLivingState() const { return LivingState; }

	// 대미지 처리 함수
	void GetDamaged(float fBaseDamage, TObjectPtr<AActor> DamageCauser);

	// 애니메이션에서 캐릭터의 체력 퍼센트 받는 함수
	UFUNCTION(BlueprintCallable)
		float GetHealthPercent() const;

	// 캐릭터 무적 상태 변수 Setter <- 타이머 전용
	UFUNCTION(BlueprintCallable)
		void ActivateGodMode(float GodModeTime);

	// 캐릭터 체력 추가 실행 함수
	UFUNCTION(BlueprintCallable)
		void ActivatePlusHealthBuff(float PlusHealthPercent, float PlusHealthTime);

	// 무적상태 반환 함수(getter) 및 setter
	FORCEINLINE bool IsGodMode() const { return bIsGodMode; }
	FORCEINLINE void SetGodMode(bool bNewGodMode) { bIsGodMode = bNewGodMode; }

	// 아군/적군 체력바 위젯 설정
	UFUNCTION(BlueprintCallable)
	void SetHealthBarFriendly();
	void SetHiddenHealthPB();
	void GetDamagedByEnemy();

	// === 2019180016 ===
	// Process Packet From Server
	void ChangeCurrentHp(float hp);
	void ChangeState(EHealthState s);

	void AddWidget();
	// ==================
	
private:
	void SetPlayerDie(TObjectPtr<AActor> DamageCauser = nullptr);
};
