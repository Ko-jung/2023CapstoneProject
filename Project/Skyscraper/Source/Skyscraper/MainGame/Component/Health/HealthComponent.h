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
	// ü�� ���� ����
	UPROPERTY(VisibleAnywhere, Category = Health)
		float CurrentHealth;
	UPROPERTY(EditAnywhere, Category = Health)
		float MaxHealth;
	EHealthState LivingState;

	// ���۳�Ʈ ���� ĳ����
	UPROPERTY()
		ASkyscraperCharacter* OwnerCharacter;

	// ���� ���۳�Ʈ ���� ����
	UPROPERTY()
		UWidgetComponent* HealthBarWidgetComponent;
	UPROPERTY(VisibleAnywhere)
		UClass* HealthBarWidgetClass;
	UPROPERTY()
		UHealthBar* HealthProgressBar;

	// ĳ���� ���� bool ����
	UPROPERTY()
		bool bIsGodMode;
	UPROPERTY()
		UTextRenderComponent* GodModeTextRender;

	// ĳ���� ���� Ÿ�̸� �ڵ�
	UPROPERTY()
		FTimerHandle GodModeTimerHandle;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// ĳ���� ���� ���� ���� Getter
	FORCEINLINE EHealthState GetLivingState() const { return LivingState; }

	// ����� ó�� �Լ�
	void GetDamaged(float fBaseDamage);

	// �ִϸ��̼ǿ��� ĳ������ ü�� �ۼ�Ʈ �޴� �Լ�
	UFUNCTION(BlueprintCallable)
		float GetHealthPercent() const;

	// ĳ���� ���� ���� ���� Setter
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
