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
	// 생성자
	UMainRangeComponent();

	// InputMappingContext 추가 및 삭제 함수
	void AddInputMappingContext();
	void RemoveInputMappingContext();

	// 다시 무기를 장착 하였을 때 키 인풋 추가 및 무기 추가하는 함수
	void AddThisWeapon();
	// 무기 컴퍼넌트 제거할 때, 키 인풋 제거 및 무기 제거하는 함수
	void RemoveThisWeapon();
	

	// 총발사를 위한 애니메이션을 재생하는 함수
	UFUNCTION(BlueprintCallable)
	void PlayFireAnim();

	// 탄 발사 로직 함수
	UFUNCTION(BlueprintCallable)
	virtual void Fire(float fBaseDamage);
	// 적군 탄 발사 로직 함수
	UFUNCTION(BlueprintCallable)
		void EnemyFire(float fBaseDamage);

	// 재장전을 위한 애니메이션을 재생하는 함수
	UFUNCTION(BlueprintCallable)
		void PlayReloadAnim();
	// 재장전 로직 함수
	UFUNCTION(BlueprintCallable)
		void BulletReloading();

	// 발사 가능한지 상태를 반환하는 함수
	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool CanFire() const { return (CurrentBulletCount > 0 && CurrentFireCoolTime <= 0.0f); }

protected:
	// BeginPlay / EndPlay
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	
	// 소유 캐릭터 변수
	UPROPERTY()
		ASkyscraperCharacter* OwnerCharacter;

	// 착용 시 무기에 대한 변수
	// 각 하위(자식) 컴퍼넌트 들에서 초기화 진행
	UPROPERTY()
		USkeletalMeshComponent* WeaponMesh;
	UPROPERTY()
		USkeletalMesh* WeaponObject;
	UPROPERTY()
		FName WeaponSocketName;

	// 발사 관련 변수
	UPROPERTY(VisibleAnywhere, Category = Fire)
		float CurrentFireCoolTime;
	UPROPERTY(EditAnywhere,Category = Fire)
		float FireMaxCoolTime;
	// 재장전 관련 변수
	UPROPERTY(VisibleAnywhere, Category = Reload)
		float CurrentReloadCoolTime;
	UPROPERTY(EditAnywhere, Category = Reload)
		float ReloadMaxCoolTime;
	UPROPERTY(EditAnywhere, Category = Reload)
		float ReloadSpeedTime;
	// 총알 관련 변수
	UPROPERTY(VisibleAnywhere, Category = Bullet)
		int32 CurrentBulletCount;
	UPROPERTY(EditAnywhere, Category = Bullet)
		int32 BulletMaxCount;
	UPROPERTY()
		bool bIsBulletInfinity;

	// 총기 반동 관련 변수
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

	// 애니메이션 관련 변수
	UPROPERTY()
		UAnimInstance* OwnerAnimInstance;
	ECharacterAnimMontage FireAnimMontageKey;
	ECharacterAnimMontage ReloadAnimMontageKey;

	// 발사 / 재장전 등의 쿨타임에 대한 타이머 핸들 변수
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
