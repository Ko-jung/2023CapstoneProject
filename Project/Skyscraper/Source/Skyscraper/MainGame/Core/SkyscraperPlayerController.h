// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SkyscraperPlayerController.generated.h"

class ASkyscraperCharacter;
/**
 * 
 */
UCLASS()
class SKYSCRAPER_API ASkyscraperPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ASkyscraperPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	UFUNCTION(BlueprintCallable)
		FORCEINLINE void SetCanLookInput(bool NewCanLookInput) { bCanLookInput = NewCanLookInput; }
	

protected:
	// 소유한 GetPawn() 에 대하여 형변환
	UPROPERTY()
	ASkyscraperCharacter* PossessingPawn;

	// 캐릭터와 컨트롤러를 분리한 ECharacterCameraMode::ECCM_SeparateController 시 bool 값 변경을 통해 사용
	UPROPERTY(EditAnywhere)
		bool bCanLookInput = false;

};
