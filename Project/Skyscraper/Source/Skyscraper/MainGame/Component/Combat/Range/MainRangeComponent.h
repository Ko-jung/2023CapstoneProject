// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "MainRangeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class SKYSCRAPER_API UMainRangeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// ������
	UMainRangeComponent();

	// InputMappingContext �߰� �� ���� �Լ�
	void AddInputMappingContext();
	void RemoveInputMappingContext();

	// �ٽ� ���⸦ ���� �Ͽ��� �� Ű ��ǲ �߰� �� ���� �߰��ϴ� �Լ�
	void AddThisWeapon();
	// ���� ���۳�Ʈ ������ ��, Ű ��ǲ ���� �� ���� �����ϴ� �Լ�
	void RemoveThisWeapon();
	

	// �ѹ߻縦 ���� �ִϸ��̼��� ����ϴ� �Լ�
	UFUNCTION(BlueprintCallable)
	void PlayFireAnim();

	// ź �߻� ���� �Լ�
	UFUNCTION(BlueprintCallable)
	virtual void Fire(float fBaseDamage);
	// ���� ź �߻� ���� �Լ�
	UFUNCTION(BlueprintCallable)
		void EnemyFire(float fBaseDamage);

	// �������� ���� �ִϸ��̼��� ����ϴ� �Լ�
	UFUNCTION(BlueprintCallable)
		void PlayReloadAnim();
	// ������ ���� �Լ�
	UFUNCTION(BlueprintCallable)
		void BulletReloading();

	// �߻� �������� ���¸� ��ȯ�ϴ� �Լ�
	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool CanFire() const { return (CurrentBulletCount > 0 && CurrentFireCoolTime <= 0.0f); }

protected:
	// BeginPlay / EndPlay
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	
	// ���� ĳ���� ����
	UPROPERTY()
		ASkyscraperCharacter* OwnerCharacter;

	// ���� �� ���⿡ ���� ����
	// �� ����(�ڽ�) ���۳�Ʈ �鿡�� �ʱ�ȭ ����
	UPROPERTY()
		USkeletalMeshComponent* WeaponMesh;
	UPROPERTY()
		USkeletalMesh* WeaponObject;
	UPROPERTY()
		FName WeaponSocketName;

	// �߻� ���� ����
	UPROPERTY(VisibleAnywhere, Category = Fire)
		float CurrentFireCoolTime;
	UPROPERTY(EditAnywhere,Category = Fire)
		float FireMaxCoolTime;
	// ������ ���� ����
	UPROPERTY(VisibleAnywhere, Category = Reload)
		float CurrentReloadCoolTime;
	UPROPERTY(EditAnywhere, Category = Reload)
		float ReloadMaxCoolTime;
	UPROPERTY(EditAnywhere, Category = Reload)
		float ReloadSpeedTime;
	// �Ѿ� ���� ����
	UPROPERTY(VisibleAnywhere, Category = Bullet)
		int32 CurrentBulletCount;
	UPROPERTY(EditAnywhere, Category = Bullet)
		int32 BulletMaxCount;
	UPROPERTY()
		bool bIsBulletInfinity;

	// �ѱ� �ݵ� ���� ����
	UPROPERTY(EditAnywhere, Category = Recoil)
		float RecoilAboveAmount;
	UPROPERTY(EditAnywhere, Category = Recoil)
		float RecoilBesideAmount;
	UPROPERTY()
		float RecoilTime;
	UPROPERTY()
		FRotator RecoilTargetRot;
	UPROPERTY(EditAnywhere, Category = Recoil)
		float RecoilSpeed;

	// �ִϸ��̼� ���� ����
	UPROPERTY()
		UAnimInstance* OwnerAnimInstance;
	ECharacterAnimMontage FireAnimMontageKey;
	ECharacterAnimMontage ReloadAnimMontageKey;

	// �߻� / ������ ���� ��Ÿ�ӿ� ���� Ÿ�̸� �ڵ� ����
	FTimerHandle FireCoolTimerHandle;
	FTimerHandle ReloadCoolTimerHandle;
	FTimerHandle BulletInfinityTimerHandle;


protected:
	//FORCEINLINE bool CanFire() const { return (CurrentBulletCount > 0 && CurrentFireCoolTime <= 0.0f); }
	FORCEINLINE bool CanReload() const { return CurrentReloadCoolTime <= 0.0f; }
	void UseBullet();
	void Recoil();

	void FireCoolDownTimerFunc();
	void ReloadCoolDownTimerFunc();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE APlayerController* GetOwnerPlayerController()const { return Cast<APlayerController>(OwnerCharacter->GetController()); }

	FORCEINLINE void SetBulletMaxCount(int32 iNewBulletCount) { CurrentBulletCount = BulletMaxCount = iNewBulletCount;  }

	UFUNCTION()
		void ActivateBulletInfinity(float BulletInfinityTime);
	UFUNCTION()
		void DeactivateBulletInfinity();

private:
	// == Input Action And Input Mapping Context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputMappingContext* IMC_RangeInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* IA_Fire;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* IA_Reload;

};
