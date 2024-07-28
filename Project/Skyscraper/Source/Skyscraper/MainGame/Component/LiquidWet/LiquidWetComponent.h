// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LiquidWetComponent.generated.h"

USTRUCT()
struct FLiquidData
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere)
		FVector2D HitUV;
	UPROPERTY(VisibleAnywhere)
		float HitDuration;
};


class ASkyscraperCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SKYSCRAPER_API ULiquidWetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULiquidWetComponent();

	void SetHitDataWithDelay();
	UFUNCTION(BlueprintCallable)
		void AddHitData(FVector2D HitUV, float LiquidDuration);
	
	UFUNCTION(BlueprintCallable)
		void SetSkirtGravity(float value);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void AddSkirtCollisionMesh();
	void FindOwnerClothConfigBase();
	void SetSkirtMaterialDynamicInstance();
	void CreateRenderTargetAndSetMaterialParam();

	void InitialSetting();

	void SetOwnerCharacterNewMesh();

	// 액체 흔적을 렌더링 하는 함수
	void RenderLiquidWet();
	// 액체 흔적 기준 치마의 물리 효과 계산하여 적용하는 함수
	void CalculateAndApplySkirtGravity();

	UFUNCTION()
		void LiquidUpdateFunc();
private:
public:	
protected:
	// 액체 최대 충돌 갯수
	int MaxHitCount;
	// 렌더타겟 내 데이터 간 간격
	int HitDataOffset;

	// 컴퍼넌트 소유 캐릭터
	TObjectPtr<ASkyscraperCharacter> OwnerCharacter;

	// Skirt의 Dynamic 머테리얼
	UPROPERTY()
	TObjectPtr<class UMaterialInstanceDynamic> MaterialDynamicInstanceObj;

	// HitData를 담는 RenderTarget 캔버스
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UTextureRenderTarget2D* RT_HitData;

	// Skirt의 ClothingData를 담고있는 UChaosClothConfig
	TObjectPtr<class UChaosClothConfig> SkirtConfig;

	// Skirt에 Liquid의 충돌 데이터를 담는 구조체 배열
	UPROPERTY()
	TArray<FLiquidData> FLiquidHitData;

	FTimerHandle LiquidUpdateTimerHandle;
	FTimerHandle SetSkirtGravityTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* SkirtCollisionMesh;
	

private:


		
};

