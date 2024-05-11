// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Skyscraper/Enum/EMeleeSelect.h"
#include "Skyscraper/Enum/ERangeSelect.h"
#include "SkyscraperPlayerController.generated.h"

class UChangeWeaponWidget;
class UMiniMapWidget;
class UTimeAndKillCountWidget;
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

	UFUNCTION(BlueprintCallable)
		FORCEINLINE void SetCanLookInput(bool NewCanLookInput) { bCanLookInput = NewCanLookInput; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UTimeAndKillCountWidget* GetTimeAndKillCountWidget() const { return TimeAndKillCountWidget; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE UMiniMapWidget* GetMiniMapWidget() const { return MiniMapWidget; }

	UFUNCTION(BlueprintCallable)
	void AddChangeWeaponWidget();
	UFUNCTION(BlueprintCallable)
	void RemoveChangeWeaponWidget();

	void ChangePlayerMeleeWeapon(EMeleeSelect NewMeleeSelect) const;
	void ChangePlayerRangeWeapon(ERangeSelect NewRangeSelect) const;
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:

public:

protected:
	// 소유한 GetPawn() 에 대하여 형변환
	UPROPERTY()
	ASkyscraperCharacter* PossessingPawn;

	// TimeAndKillCount Widget 클래스 및 변수
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> TimeAndKillCountWidgetClass;
	UPROPERTY()
		TObjectPtr<UTimeAndKillCountWidget> TimeAndKillCountWidget;

	// MiniMap Widget 클래스 및 변수
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> MiniMapWidgetClass;
	UPROPERTY()
		TObjectPtr<UMiniMapWidget> MiniMapWidget;

	// ChangeWeapon Widget 클래스 및 변수
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> ChangeWeaponWidgetClass;
	UPROPERTY()
		TObjectPtr<UChangeWeaponWidget> ChangeWeaponWidget;

	// 캐릭터와 컨트롤러를 분리한 ECharacterCameraMode::ECCM_SeparateController 시 bool 값 변경을 통해 사용
	UPROPERTY(EditAnywhere)
		bool bCanLookInput = false;

private:
};
