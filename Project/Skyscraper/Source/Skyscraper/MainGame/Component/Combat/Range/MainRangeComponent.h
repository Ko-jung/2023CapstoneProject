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
	// Sets default values for this component's properties
	UMainRangeComponent();

	UFUNCTION(BlueprintCallable)
	void PlayFireAnim();

	UFUNCTION(BlueprintCallable)
	void Fire(float fBaseDamage);
	UFUNCTION(BlueprintCallable)
		void EnemyFire(float fBaseDamage);

	UFUNCTION(BlueprintCallable)
		void BulletReloading();
	UFUNCTION(BlueprintCallable)
		void PlayReloadAnim();
	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool CanFire() const { return (CurrentBulletCount > 0 && CurrentFireCoolTime <= 0.0f); }
	protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	// == Owner Character Variable
	UPROPERTY()
		ASkyscraperCharacter* OwnerCharacter;

	// == MainRange Variable
	UPROPERTY(VisibleAnywhere, Category = Fire)
		float CurrentFireCoolTime;
	UPROPERTY(EditAnywhere,Category = Fire)
		float FireMaxCoolTime;
	UPROPERTY(VisibleAnywhere, Category = Reload)
		float CurrentReloadCoolTime;
	UPROPERTY(EditAnywhere, Category = Reload)
		float ReloadMaxCoolTime;
	UPROPERTY(EditAnywhere, Category = Reload)
		float ReloadSpeedTime;
	UPROPERTY(VisibleAnywhere, Category = Bullet)
		int32 CurrentBulletCount;
	UPROPERTY(EditAnywhere, Category = Bullet)
		int32 BulletMaxCount;

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



	// == Anim Variable
	UPROPERTY()
		UAnimInstance* OwnerAnimInstance;
	//UPROPERTY(EditAnywhere, Category = AnimMontage)
	//	UAnimMontage* AM_Fire;
	//UPROPERTY(EditAnywhere, Category = AnimMontage)
	//	UAnimMontage* AM_Reload;
	ECharacterAnimMontage FireAnimMontageKey;
	ECharacterAnimMontage ReloadAnimMontageKey;

	// == Timer Handle Variable And Function
	FTimerHandle FireCoolTimerHandle;
	FTimerHandle ReloadCoolTimerHandle;


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

private:
	// == Input Action And Input Mapping Context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputMappingContext* IMC_RangeInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* IA_Fire;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* IA_Reload;

};
