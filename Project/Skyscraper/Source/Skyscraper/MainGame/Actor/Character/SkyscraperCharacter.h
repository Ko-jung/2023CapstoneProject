// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Skyscraper/Enum/ECharacterAnimMontage.h"
#include "Skyscraper/Enum/ECharacterCameraMode.h"
#include "Skyscraper/Enum/ECharacterSelect.h"
#include "Skyscraper/Enum/EItemEffect.h"
#include "Skyscraper/Enum/EItemRareLevel.h"
#include "Skyscraper/Enum/EMeleeSelect.h"
#include "Skyscraper/Enum/ERangeSelect.h"
#include "Skyscraper/Enum/ESkillActor.h"
#include "Skyscraper/Enum/ESwapWeapon.h"
#include "Skyscraper/MainGame/Animation/SkyscraperAnimInstance.h"
#include "SkyscraperCharacter.generated.h"

class UMaterialInstanceConstant;
class UNiagaraComponent;
class ASkyscraperPlayerController;
class USkyscraperAnimInstance;
class UJetpackComponent;
class UHealthComponent;
class UMainRangeComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UCombatSystemComponent;
class UMotionWarpingComponent;
class UMainMeleeComponent;
class ULiquidWetComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ASkyscraperCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	ASkyscraperCharacter();

	// == Get component
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE UMotionWarpingComponent* GetMotionWarpingComponent() const { return MotionWarpingComponent; }
	ASkyscraperPlayerController* GetPlayerController() const;

	// == Take Damage
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// == Stun / Down
	virtual void DoStun(const AActor* Attacker, const float StunTime, const FVector StunDirection) const;
	virtual void DoDown(const AActor* Attacker, const FVector& DownDirection) const;

	// == Get Anim Montage
	UAnimMontage* GetAnimMontage(ECharacterAnimMontage) const;

	// bIsHover 값 setter / getter
	void SetIsHover(bool NewIsHover);
	FORCEINLINE bool GetIsHover() const { return bIsHover; }

	// 캐릭터 기본 걷기 최대 속도 반환 함수
	FORCEINLINE float GetCharacterMaxWalkSpeed() const { return CharacterMaxWalkSpeed; }
	// 캐릭터 스피드 버프 수치 (기본 1.0f / 25% 증가시 1.25f 반환) 반환 함수
	FORCEINLINE float GetSpeedBuffValue() const { return SpeedBuffValue; }
	// 캐릭터 공격력 버프 수치 (기본 1.0f / 25% 증가시 1.25f 반환) 반환 함수
	FORCEINLINE float GetPowerBuffValue() const { return PowerBuffValue; }

	// 스피드 증가 적용 해제 함수
	UFUNCTION(BlueprintCallable)			// 2019180016 Add To SkillDebuff
	void SetSpeedBuffValue(float NewSpeedBuffValue, float fBuffTime);
	void AddSpeedBuffValue(float AddSpeedBuffValue);

	// 공격력 증가 적용 해제 함수
	void SetPowerBuffValue(float NewPowerBuffValue, float fBuffTime);

	// 아이템을 추가시키는 함수
	void AddItem(EItemEffect ItemEffect, EItemRareLevel RareLevel, AActor* Item);

	// 캐릭터 무적 설정 및 해제 변수 / GodMode인지 get 함수
	UFUNCTION(BlueprintCallable)
		void SetCharacterGodMode(bool bNewGodMode);
	UFUNCTION(BlueprintCallable)
		bool IsCharacterGodMode();

	// 캐릭터 카메라 모드 변경하는 함수
	UFUNCTION(BlueprintCallable)
		void SetCameraMode(ECharacterCameraMode CameraMode);

	void PlayBoostAnimation(const FString& SectionString) const;

	UFUNCTION(BlueprintCallable,BlueprintPure)
		FORCEINLINE bool GetIsMoveDiagonally() { return bIsMoveDiagonally; }

	FORCEINLINE TObjectPtr<USkyscraperAnimInstance> GetAnimInstance() const { return Cast<USkyscraperAnimInstance>(GetMesh()->GetAnimInstance()); }

	FORCEINLINE UStaticMesh* GetSkirtStaticMesh()const { return SkirtStaticMesh; }
	FORCEINLINE UMaterial* GetSkirtMaterial() const { return SkirtMaterial; }
	FORCEINLINE float GetSkirtMaterialValue() const { return SkirtMaterialValue; }

	UFUNCTION()
		void SetDashEffectHiddenInGame(bool NewHidden) const;

	UFUNCTION()
		void SetCameraFOVToDash(bool bToDash, float Alpha = 1.0f);

	UFUNCTION()
		void SpawnGravityChangerArea(bool bGravityLow);

	UFUNCTION()
		FORCEINLINE USkeletalMeshComponent* GetBoostMesh() const { return BoostMesh; }

	// 2019180016
public:
	// Skill
		UFUNCTION(BlueprintCallable)
		void DoDisableLockOn(float Timer);
		void DoAbleLockOn();
		bool DisableLockOn;


	UFUNCTION(BlueprintCallable)
	void DoCantEnemyLockOnMe(float Timer);
	void DoCanEnemyLockOnMe();
	bool CanEnemyLockOnMe;

	UFUNCTION(BlueprintCallable)
	void SkillInteract(ESkillActor SkillActor, float Timer);

	UFUNCTION(BlueprintCallable)
	void InitCoolTime(bool IsSpecial);
	//==============

	// When Character Attack. Define each Character class. Now Use Only Assasin
	virtual void CharacterAttackEvent() {};
	// When Own SkillActor has Damaged. Now Use Only Shield
	virtual void SkillActorDamaged(float AfterHp);

	/// <returns>
	/// If Weapon Changed return true
	/// </returns>
	bool CheckHoldWeapon(ESwapWeapon& weaponType, uint8& equippedWeapon);

	void SwapWeapon(ESwapWeapon WeaponType);
	
	UFUNCTION(BlueprintCallable)
	void SendAnimMontageStatus(ECharacterAnimMontage eMontage, int Section);

	// == Stun / Down
	void ApplyStun(const float StunTime, const FVector StunDirection) const;
	void ApplyDown(const FVector& DownDirection) const;

	// 서버에서 캐릭터 생성시 Controller가 없다. BeginPlay에서 AddInput할 수 없다.
	void AddInputMappingContext();
	void AddCharacterMappingContext();

	void ObserveLook(const FInputActionValue& InputActionValue);
	void AddObserveInputMappingContext();
	void RemoveObserveInputMappingContext();

	void SyncTransformAndAnim(FTransform t, float s, FRotator r);
	void SetMontage(ECharacterAnimMontage eAnimMontage, int SectionNum);

	virtual void SetBoostEffectVisibility(bool bVisible);

	// Item
	void SingleGodMode(EItemRareLevel EIRL);
	// ================

	void SetSpeed(float s) { Speed = s; }
	void SetXRotate(float r) { XRotate = r; }
	int  GetSpeed() { return Speed; }
	float GetXRotate() { return XRotate; }

	// 현재의 모든 인풋 컨텍스트를 지우는 함수
	void RemoveAllInputMappingTemporary();
	// 현재 사용 가능한 모든 인풋 컨텍스트(디폴트 입력들)를 추가하는 함수
	void AddAllInputMappingContext();

	// 상대의 탐지시 Custom Depth 활성화
	void CustomDepthOn();
	void CustomDepthOff();
	UFUNCTION(BlueprintNativeEvent)
	void SetCustomDepth(bool On);

	UFUNCTION(BlueprintCallable)
	void SubtractFuelHalf();

	UFUNCTION(BlueprintCallable)
	void ChangeMappingContext(bool IsOnlyMouseMode);

	UFUNCTION(BlueprintCallable)
	void CastingSkill(bool IsSpecialSkill);

	void InValidCommonTimer();
	void InValidSpecialTimer();

	UFUNCTION(BlueprintCallable)
	bool IsTimerValid(bool IsSpecialSkill);

	UFUNCTION(BlueprintNativeEvent)
	void SkillActorSpawnUsingPacket(bool IsSpecialSkill, FVector SpawnLocation, FVector ForwardVector, AActor*& NewActor);

	UFUNCTION(BlueprintNativeEvent)
	void ActiveSkill(bool IsSpecialSkill);

	UFUNCTION(BlueprintNativeEvent)
	void PlaySkillMontage(bool IsSpecialSkill, uint8 SectionNum);

		// Process Mine Stun
		UFUNCTION(BlueprintCallable)
		void AbleToAct();

		UFUNCTION(BlueprintCallable)
		void ApplyStun(const float StunTime);
		// ==================

	UFUNCTION(BlueprintCallable)
	bool IsAlliance(AActor* Target);

	void SetCombatOwner();
	// ==================

	UFUNCTION()
		void SetItemEffectAndOverlayMaterial(EItemEffect TargetItemEffect, bool bAdd);
	

protected:
	// 키 인풋에 따른 액션 함수
	/** Called for movement input */
	void Move(const FInputActionValue& Value);
	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	// 아이템 상호작용 키 
	void ItemInteraction();
	// 아이템 사용
	void UseItem();
	// ObserveMode로 변경
	void StartObserveMode();
	void EndObserveMode();
	// 휠 업다운(alt 중)
	void SetCameraZoomUpDown(const FInputActionValue& Value);

	void ItemInteractionStart();
	void ItemInteractionEnd();
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay() override;

	// === 2019180016 ===
	virtual void Tick(float DeltaSeconds) override;
	// ==================

	// 캐릭터가 땅에 닿았을 때 실행될 함수
	virtual void Landed(const FHitResult& Hit) override;

	// 버프(속도/공격력 증가 등) 타이머 시간 이후 초기화 시키는 함수
	UFUNCTION()
		void ResetSpeedBuffValue();
	UFUNCTION()
		void ResetPowerBuffValue();

	// === 2019180016 ===
protected:
	class AMainGameMode* MainGameMode;

	ESwapWeapon PrevWeaponType;

	AActor* InteractingActor;

	UPROPERTY(BlueprintReadWrite)
		float Speed;
	UPROPERTY(BlueprintReadWrite)
		float XRotate; 

	UPROPERTY(BlueprintReadWrite)
	bool IsUnableAct;

	float CommonSkillCoolTime;
	float SpecialSkillCoolTime;
	FTimerHandle CommonSkillTimerHandle;
	FTimerHandle SpecialSkillTimerHandle;

	FTimerHandle UnableActTimerHandle;
	FTimerHandle DetectingTimerHandle;
	FTimerHandle LockOnTimerHandle;
	FTimerHandle EnemyLockOnTimerHandle;

	UFUNCTION(BlueprintCallable)
		void SendSkillActorSpawnPacket(const AActor* Sender, ESkillActor SkillActor, FVector SpawnLocation, FVector ForwardVec);
	// ======
private:

public:
	// == 컴퍼넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
		TObjectPtr<UCombatSystemComponent> CombatSystemComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
		TObjectPtr<UMotionWarpingComponent> MotionWarpingComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
		TObjectPtr<UHealthComponent> HealthComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
		TObjectPtr<UJetpackComponent> JetpackComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Component)
		TObjectPtr<ULiquidWetComponent> LiquidWetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FOV")
		float DefaultFOV;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FOV")
		float DashFOV;

	bool bIsTrainingBot;

	UPROPERTY()
		ECharacterSelect CharacterType;
protected:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* FollowCamera;

	UPROPERTY()
		float InitialCameraArmLength = 350.0f;
	UPROPERTY()
		FVector InitialCameraBoomOffset = FVector{ 20.0f,0.0f, 85.0f };

	UPROPERTY()
		TMap<ECharacterAnimMontage, UAnimMontage*> CharacterAnimMontages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boost")
		USkeletalMeshComponent* BoostMesh;

	UPROPERTY(EditAnywhere, Category = "Skirt")
		UStaticMesh* SkirtStaticMesh;
	UPROPERTY(EditAnywhere, Category = "Skirt")
		UMaterial* SkirtMaterial;
	UPROPERTY(EditAnywhere, Category = "Skirt")
		float SkirtMaterialValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
		TObjectPtr<UNiagaraComponent> NS_DashEffect;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> BP_GravityChangerAreaClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> BP_GravityChangerAreaHighClass;

	UPROPERTY(EditAnywhere)
		TArray<TObjectPtr<UMaterialInstanceConstant>> MI_ItemOverlay;

	UPROPERTY()
		TArray<EItemEffect> CurrentItemEffects;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		TObjectPtr<UNiagaraComponent> NS_BoostEffect;

private:
	

	// 플레이어가 떠 있는지에 대한 변수 (AnimInstance에서 사용 예정)
	UPROPERTY(VisibleAnywhere)
		bool bIsHover;

	UPROPERTY(VisibleAnywhere)
		bool bIsMoveDiagonally;

	// 캐릭터 기본 걷기 속도
	UPROPERTY(EditAnywhere,Category = Locomotion, meta = (AllowPrivateAccess = "true"))
		float CharacterMaxWalkSpeed;
	UPROPERTY(EditAnywhere, Category = Locomotion, meta = (AllowPrivateAccess = "true"))
		float CharacterBwdMaxWalkSpeed;
	UPROPERTY(EditAnywhere, Category = Locomotion, meta = (AllowPrivateAccess = "true"))
		float CharacterBesideMaxWalkSpeed;

	// 캐릭터 버프 수치 - 기본 1.0f ( 40% 증가 버프 받으면 1.4f ...)
	UPROPERTY(EditAnywhere)
		float SpeedBuffValue;
	UPROPERTY(EditAnywhere)
		float PowerBuffValue;

	// 캐릭터의 소유하고 있는 아이템에 대한 변수 ( 기본 값 - [EIE_NONE, EIRL_NONE]
	TTuple<EItemEffect, EItemRareLevel> OwningItem;


	// 타이머 핸들
	FTimerHandle SpeedBuffTimerHandle;
	FTimerHandle PowerBuffTimerHandle;

	// Input 관련 변수
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* LookAction;

	/** ObserveMode Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* IA_ObserveMode;

	// 아이템 상호작용 Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* IA_ItemInteraction;

	// 아이템 사용 Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* IA_ItemUsing;

	// Observe
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputMappingContext* IMC_Observe;

	// alt(Observe Mode) 중 휠 시 카메라 줌 업다운
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* IA_Observe_CameraZoom;
	// alt(Observe Mode) 중 카메라 회전
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* IA_Observe_Look;

	// =================== 2019180016 ===================
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* OnlyMouseMappingContext;
	// ==================================================
};

