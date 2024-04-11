// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"

#include "../../Common/EnumDef.h"

#include "HealthComponent.generated.h"

class UTextRenderComponent;
class UProgressBar;
class UWidgetComponent;
class UHealthBar;
class ASkyscraperCharacter;

enum class EHealthState
{
	EHS_LIVING, EHS_DYING, EHS_DEAD
};

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
	EHealthState LivingState;

	// 컴퍼넌트 소유 캐릭터
	UPROPERTY()
		ASkyscraperCharacter* OwnerCharacter;

	// 위젯 컴퍼넌트 관련 변수
	UPROPERTY()
		UWidgetComponent* HealthBarWidgetComponent;
	UPROPERTY(VisibleAnywhere)
		UClass* HealthBarWidgetClass;
	UPROPERTY()
		UHealthBar* HealthProgressBar;

	// 캐릭터 무적 bool 변수
	UPROPERTY()
		bool bIsGodMode;
	UPROPERTY()
		UTextRenderComponent* GodModeTextRender;

	// 캐릭터 무적 타이머 핸들
	UPROPERTY()
		FTimerHandle GodModeTimerHandle;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 캐릭터 생존 상태 변수 Getter
	FORCEINLINE EHealthState GetLivingState() const { return LivingState; }

	// 대미지 처리 함수
	void GetDamaged(float fBaseDamage);

	// 애니메이션에서 캐릭터의 체력 퍼센트 받는 함수
	UFUNCTION(BlueprintCallable)
		float GetHealthPercent() const;

	// 캐릭터 무적 상태 변수 Setter
	UFUNCTION(BlueprintCallable)
		void ActivateGodMode(float GodModeTime);
	UFUNCTION()
	void DeactivateGodMode();

	// Process Packet From Server
	void ChangeCurrentHp(float hp);
	void ChangeState(ECharacterState s);

private:
	void SetPlayerDie();
};
