// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "MainMeleeComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class SKYSCRAPER_API UMainMeleeComponent : public UActorComponent
{
	GENERATED_BODY()

	

public:	
	// Sets default values for this component's properties
	UMainMeleeComponent();


	// == Do attack action by anim montage anim notify
	UFUNCTION(BlueprintCallable)
		void Attack();
	// == Spawn attack area for attack

	//TODO: Refactoring for team not damaged
	UFUNCTION(BlueprintCallable)
	void CreateAttackArea(FVector vHitSize, float fStiffnessTime, float fBaseDamage, bool bDoDown);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY()
		ASkyscraperCharacter* OwnerCharacter;

	// == Play melee attack montage for attack
	void PlayAttackAnimMontage();

	// == On Blend Out attack montage
	UFUNCTION()		// To link delegate (OnMontageBlendingOut);
	void OnBlendOutMeleeAttack(UAnimMontage* Montage, bool bInterrupted);

	UPROPERTY(EditAnywhere, Category = Components)
		TMap<int32, UAnimMontage*> MeleeComboAnimMontage;
	UPROPERTY(EditAnywhere, Category = AnimMontage)
		TArray<float> AttackTime;
	UPROPERTY(EditAnywhere, Category = MotionWarping)
		float AnimationMovementDistance;
	UPROPERTY(VisibleAnywhere, Category = ComboSystem)
		int32 MeleeComboCount;
	UPROPERTY(VisibleAnywhere, Category = ComboSystem)
		bool CanAttack;
	UPROPERTY(VisibleAnywhere, Category = ComboSystem)
		float LastAttackClickTime;
	UPROPERTY()
		UAnimInstance* OwnerAnimInstance;

	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE APlayerController* GetOwnerPlayerController() const { return Cast<APlayerController>(OwnerCharacter->GetController()); }
	
private:
	// == Input Action And Input Mapping Context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputMappingContext* IMC_MeleeInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* IA_Attack;

};
