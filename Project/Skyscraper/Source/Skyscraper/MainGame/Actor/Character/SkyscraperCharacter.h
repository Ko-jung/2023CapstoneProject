// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Skyscraper/Enum/ECharacterAnimMontage.h"
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

	// 플레이어가 떠 있는지에 대한 변수 (AnimInstance에서 사용 예정)
	UPROPERTY(VisibleAnywhere)
		bool bIsHover;

	// 캐릭터 기본 걷기 속도
	UPROPERTY(EditAnywhere)
		float CharacterMaxWalkSpeed;
	// 캐릭터 스피드 버프 수치 - 기본 1.0f ( 40% 증가 버프 받으면 1.4f ...)
	UPROPERTY(EditAnywhere)
		float SpeedBuffValue;

	FTimerHandle SpeedBuffTimerHandle;

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
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	// 제트팩 컴퍼넌트 - 회피 기능 사용
	void Dodge(const FInputActionValue& InputActionValue);
	// 아이템 상호작용 키 
	void ItemInteraction();
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay() override;

	virtual void Landed(const FHitResult& Hit) override;
	
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

	FORCEINLINE float GetCharacterMaxWalkSpeed() const { return CharacterMaxWalkSpeed; }
	FORCEINLINE float GetSpeedBuffValue() const { return SpeedBuffValue; }
	

	// 스피드 증가 적용 해제 함수
	void SetSpeedBuffValue(float NewSpeedBuffValue, float fBuffTime);
	UFUNCTION()
		void ResetSpeedBuffValue();
protected:
	float Speed;
};

