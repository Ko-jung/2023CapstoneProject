// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Skyscraper/Enum/ECharacterAnimMontage.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "MainMeleeComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class SKYSCRAPER_API UMainMeleeComponent : public UActorComponent
{
	GENERATED_BODY()

	

public:	
	// Sets default values for this component's properties
	UMainMeleeComponent();

	// InputMappingContext �߰� �� ���� �Լ�
	void AddInputMappingContext();
	void RemoveInputMappingContext();

	// �ٽ� ���⸦ ���� �Ͽ��� �� Ű ��ǲ �߰� �� ���� �߰��ϴ� �Լ�
	void AddThisWeapon();
	// ���� ���۳�Ʈ ������ ��, Ű ��ǲ ���� �� ���� �����ϴ� �Լ�
	void RemoveThisWeapon();

	// == Do attack action by anim montage anim notify
	UFUNCTION(BlueprintCallable)
		void Attack();
	// == Spawn attack area for attack

	//TODO: Refactoring for team not damaged
	UFUNCTION(BlueprintCallable)
	void CreateAttackArea(FVector vHitSize, float fStunTime, float fBaseDamage, bool bDoDown);

	// ���� ���� �� HitLag(������)�� �߻���Ű�� �Լ�
	void DoHitLag();
	void StopHitLag();
	
protected:
	// == OwnerCharacter variable
	UPROPERTY()
		ASkyscraperCharacter* OwnerCharacter;

	// ���� �� ���⿡ ���� ����
	// �� ����(�ڽ�) ���۳�Ʈ �鿡�� �ʱ�ȭ ����
	UPROPERTY()
		USkeletalMeshComponent* WeaponMeshComponent;
	UPROPERTY()
		FName WeaponSocketName;

	// == OwnerCharacter's CharacterAnimMontages - key variable
	ECharacterAnimMontage AnimMontageKey;

	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


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
		bool CanAttack;
	UPROPERTY(VisibleAnywhere, Category = ComboSystem)
		float LastAttackClickTime;
	// ���� �� �� �Է� ���� ��� 0.2�� �� �Է��� �̷����� �� �ٷ� �����ϵ��� ����
	UPROPERTY(VisibleAnywhere, Category = ComboSystem)
		float BufferedInput;
	UPROPERTY()
		UAnimInstance* OwnerAnimInstance;

	// ������ 0.1�ʿ� ���� Ÿ�̸��ڵ�
	FTimerHandle HitLagTimerHandle;

	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE APlayerController* GetOwnerPlayerController() const { return Cast<APlayerController>(OwnerCharacter->GetController()); }

	// ���� ���� skeletal mesh�� visible�� �������ִ� �Լ�
	virtual void SetWeaponHiddenInGame(bool bNewHidden) const;
	
private:
	// == Input Action And Input Mapping Context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputMappingContext* IMC_MeleeInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* IA_Attack;

};
