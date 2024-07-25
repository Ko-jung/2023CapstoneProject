// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "Components/ActorComponent.h"
#include "Skyscraper/Enum/ECharacterAnimMontage.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "MainMeleeComponent.generated.h"

class UMeleeWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class SKYSCRAPER_API UMainMeleeComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	// Sets default values for this component's properties
	UMainMeleeComponent();

	// InputMappingContext 추가 및 삭제 함수
	void AddInputMappingContext();
	void BindingInputAction();
	void RemoveInputMappingContext();

	// 다시 무기를 장착 하였을 때 키 인풋 추가 및 무기 추가하는 함수
	void AddThisWeapon();
	// 무기 컴퍼넌트 제거할 때, 키 인풋 제거 및 무기 제거하는 함수
	void RemoveThisWeapon();

	// == Do attack action by anim montage anim notify
	UFUNCTION(BlueprintCallable)
		void Attack();
	// == Spawn attack area for attack

	//TODO: Refactoring for team not damaged
	UFUNCTION(BlueprintCallable)
	//void CreateAttackArea(FVector vHitSize, float fStunTime, float fBaseDamage, bool bDoDown);
	void CreateAttackArea(float Width, float Height, float Distance, FVector StartOffset, float Angle, float fStunTime, float fBaseDamage, bool bDoDown, bool bIsFinalAttack = false);

	void PlayHitSound(bool bIsFinalAttack);

	// 적을 맞출 시 HitLag(역경직)을 발생시키는 함수
	void DoHitLag();
	void StopHitLag();
	
protected:
	// == OwnerCharacter variable
	UPROPERTY()
		ASkyscraperCharacter* OwnerCharacter;

	// 착용 시 무기에 대한 변수
	// 각 하위(자식) 컴퍼넌트 들에서 초기화 진행
	UPROPERTY()
		USkeletalMeshComponent* WeaponMeshComponent;
	UPROPERTY()
		TObjectPtr<UNiagaraComponent> NS_MainWeaponCreateEffect;

	// 서브 무기에 대한 변수
	UPROPERTY()
		USkeletalMeshComponent* SubWeaponMeshComponent;
	UPROPERTY()
		TObjectPtr<UNiagaraComponent> NS_SubWeaponCreateEffect;

	UPROPERTY()
		FName WeaponSocketName;

	// == OwnerCharacter's CharacterAnimMontages - key variable
	ECharacterAnimMontage AnimMontageKey;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> NS_HitEffect;

	// 근거리 무기에 대한 UI의 클래스와 변수
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> MainMeleeWidgetClass;
	UPROPERTY()
		UMeleeWidget* MainMeleeWidget;

	UPROPERTY()
		EMeleeSelect MeleeSelect;

	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// 근접공격 쿨타임 이후 실행될 함수
	void AttackCoolTimeFunc();
	// == Play melee attack montage for attack
	void PlayAttackAnimMontage();

	// == On Blend Out attack montage
	UFUNCTION()		// To link delegate (OnMontageBlendingOut);
	void OnBlendOutMeleeAttack(FName Notify_Name);

	UPROPERTY(EditAnywhere, Category = AnimMontage)
		TArray<float> AttackTime;
	UPROPERTY(EditAnywhere, Category = AnimMontage)
		TArray<float> AttackBlendOutTime;
	UPROPERTY(EditAnywhere, Category = MotionWarping)
		float AnimationMovementDistance;
	UPROPERTY(VisibleAnywhere, Category = ComboSystem)
		int32 MeleeComboCount;
	UPROPERTY(VisibleAnywhere, Category = ComboSystem)
		float LastAttackClickTime;
	// 공격 중 선 입력 했을 경우 0.2초 내 입력이 이뤄졌을 시 바로 공격하도록 실행
	UPROPERTY(VisibleAnywhere, Category = ComboSystem)
		float BufferedInput;
	UPROPERTY()
		UAnimInstance* OwnerAnimInstance;

	// 역경직 0.1초에 대한 타이머핸들
	FTimerHandle HitLagTimerHandle;

	virtual void SetInitialValue();

	UPROPERTY()
		bool bCanAttack;
	UPROPERTY(EditAnywhere)
		float AttackCoolDownTime;
	UPROPERTY()
		float CurrentCooldownTime;
	FTimerHandle AttackCoolTimeTimerHandle;
	float AttackCoolDownTimeOffset = 0.05f;

	UPROPERTY()
		FName AttackSound;
	UPROPERTY()
		FName FinalAttackSound;

	UPROPERTY()
		FName DamagedSound;
	UPROPERTY()
		FName FinalDamagedSound;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE APlayerController* GetOwnerPlayerController() const { return Cast<APlayerController>(OwnerCharacter->GetController()); }

	// 무기 웨폰 skeletal mesh의 visible을 변경해주는 함수
	virtual void SetWeaponHiddenInGame(bool bNewHidden) const;
	
private:
	// == Input Action And Input Mapping Context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputMappingContext* IMC_MeleeInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* IA_Attack;

};
