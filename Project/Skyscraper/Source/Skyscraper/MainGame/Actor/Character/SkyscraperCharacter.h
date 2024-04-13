// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Skyscraper/Enum/ECharacterAnimMontage.h"
#include "Skyscraper/Enum/EItemEffect.h"
#include "Skyscraper/Enum/EItemRareLevel.h"
#include "SkyscraperCharacter.generated.h"

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

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ASkyscraperCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	// 플레이어가 떠 있는지에 대한 변수 (AnimInstance에서 사용 예정)
	UPROPERTY(VisibleAnywhere)
		bool bIsHover;

	// 캐릭터 기본 걷기 속도
	UPROPERTY(EditAnywhere)
		float CharacterMaxWalkSpeed;
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

public:
	ASkyscraperCharacter();

public:
	// == 컴퍼넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
		UCombatSystemComponent* CombatSystemComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
		UMotionWarpingComponent* MotionWarpingComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
		UHealthComponent* HealthComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
		UJetpackComponent* JetpackComponent;
	
protected:
	UPROPERTY()
	TMap<ECharacterAnimMontage, UAnimMontage*> CharacterAnimMontages;
			

protected:
	// 키 인풋에 따른 액션 함수
	/** Called for movement input */
	void Move(const FInputActionValue& Value);
	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	// 제트팩 컴퍼넌트 - 회피 기능 사용
	void Dodge(const FInputActionValue& InputActionValue);
	// 아이템 상호작용 키 
	void ItemInteraction();
	// 아이템 사용
	void UseItem();

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay() override;

	// 캐릭터가 땅에 닿았을 때 실행될 함수
	virtual void Landed(const FHitResult& Hit) override;

	// 버프(속도/공격력 증가 등) 타이머 시간 이후 초기화 시키는 함수
	UFUNCTION()
		void ResetSpeedBuffValue();
	UFUNCTION()
		void ResetPowerBuffValue();
public:
	// == Get component
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE UMotionWarpingComponent* GetMotionWarpingComponent() const { return MotionWarpingComponent; }
	FORCEINLINE APlayerController* GetPlayerController() const { return Cast<APlayerController>(GetController()); }

	// == Take Damage
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// == Stiffness / Down
	void DoStiffness(const float StiffnessTime) const;
	void DoDown(const FVector& DownDirection) const;

	// == Get Anim Montage
	UAnimMontage* GetAnimMontage(ECharacterAnimMontage) const;

	void SyncTransformAndAnim(FTransform t, float s);

	void SetSpeed(float s) { Speed = s; }
	int  GetSpeed() { return Speed; }

	// bIsHover 값 setter / getter
	FORCEINLINE void SetIsHover(bool NewIsHover) { bIsHover = NewIsHover; }
	FORCEINLINE bool GetIsHover() const { return bIsHover; }

	// 캐릭터 기본 걷기 최대 속도 반환 함수
	FORCEINLINE float GetCharacterMaxWalkSpeed() const { return CharacterMaxWalkSpeed; }
	// 캐릭터 스피드 버프 수치 (기본 1.0f / 25% 증가시 1.25f 반환) 반환 함수
	FORCEINLINE float GetSpeedBuffValue() const { return SpeedBuffValue; }
	// 캐릭터 공격력 버프 수치 (기본 1.0f / 25% 증가시 1.25f 반환) 반환 함수
	FORCEINLINE float GetPowerBuffValue() const { return PowerBuffValue; }

	// 스피드 증가 적용 해제 함수
	void SetSpeedBuffValue(float NewSpeedBuffValue, float fBuffTime);

	// 공격력 증가 적용 해제 함수
	void SetPowerBuffValue(float NewPowerBuffValue, float fBuffTime);

	// 아이템을 추가시키는 함수
	void AddItem(EItemEffect ItemEffect, EItemRareLevel RareLevel);
protected:
	float Speed;

private:
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

	// 제트팩 WW/AA/SS/DD 회피 Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* IA_Jetpack_Dodge;

	// 아이템 상호작용 Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* IA_ItemInteraction;

	// 아이템 사용 Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* IA_ItemUsing;
};

