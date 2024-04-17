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
	// ������ GetPawn() �� ���Ͽ� ����ȯ
	UPROPERTY()
	ASkyscraperCharacter* PossessingPawn;

	// ĳ���Ϳ� ��Ʈ�ѷ��� �и��� ECharacterCameraMode::ECCM_SeparateController �� bool �� ������ ���� ���
	UPROPERTY(EditAnywhere)
		bool bCanLookInput = false;

};
