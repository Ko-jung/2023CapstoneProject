// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Skyscraper/Enum/EItemEffect.h"
#include "Skyscraper/Enum/EMeleeSelect.h"
#include "Skyscraper/Enum/ERangeSelect.h"
#include "SkyscraperPlayerController.generated.h"

class ULockOnWidget;
class UItemWidget;
class AHexagonTile;
class UGameResultWidget;
class UChangeWeaponWidget;
class UMiniMapWidget;
class UTimeAndKillCountWidget;
class ASkyscraperCharacter;
class UMainCombatWidget;
/**
 * 
 */
UCLASS()
class SKYSCRAPER_API ASkyscraperPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASkyscraperPlayerController();

	FORCEINLINE ASkyscraperCharacter* GetPossessingPawn() const { return PossessingPawn; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UTimeAndKillCountWidget* GetTimeAndKillCountWidget() const { return TimeAndKillCountWidget; }

	UFUNCTION(BlueprintCallable)
		UMiniMapWidget* GetMiniMapWidget() const;
	UFUNCTION(BlueprintCallable)
		ULockOnWidget* GetLockOnWidget() const;

	UFUNCTION(BlueprintCallable)
	void AddChangeWeaponWidget();
	UFUNCTION(BlueprintCallable)
	void RemoveChangeWeaponWidget();

	void ChangePlayerMeleeWeapon(EMeleeSelect NewMeleeSelect) const;
	void ChangePlayerRangeWeapon(ERangeSelect NewRangeSelect) const;

	UFUNCTION(BlueprintCallable)
	void AddGameResultWidget(const FText& WinnerText);

	UFUNCTION(BlueprintCallable)
		void SetObserveMode(bool bToObserveMode);

	UFUNCTION()
		void SetSpectatorMode(bool bSetMode, AActor* DamageCauser = nullptr);
	UFUNCTION()
		void PressSetSpecatatorButton();
	UFUNCTION()
		void PressChangeWeaponButton();

	UFUNCTION(BlueprintCallable)
		void SetItemImage(EItemEffect ItemEffect);


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:

public:
	void UpdateImage();
	void UpdateImage(int index);

protected:
	// 소유한 GetPawn() 에 대하여 형변환
	UPROPERTY()
	ASkyscraperCharacter* PossessingPawn;

	// MainCombat Widget 클래스 및 변수
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> MainCombatWidgetClass;
	UPROPERTY()
		TObjectPtr<UMainCombatWidget> MainCombatWidget;

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

	// ChangeWeapon Widget 클래스 및 변수
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> GameResultWidgetClass;
	UPROPERTY()
		TObjectPtr<UGameResultWidget> GameResultWidget;

	// Item Widget 클래스 및 변수
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> ItemWidgetClass;
	UPROPERTY()
		TObjectPtr<UItemWidget> ItemWidget;

	// LockOn Widget 클래스 및 변수
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> LockOnWidgetClass;
	UPROPERTY()
		TObjectPtr<ULockOnWidget> LockOnWidget;

	UPROPERTY()
		TObjectPtr<AHexagonTile> HexagonTile;

	// 관전 가능에 대한 bool 변수
	UPROPERTY()
		bool bSpectatorMode;
	// 사망시킨 플레이어
	UPROPERTY()
		AActor* DamageCauser;
private:
	UPROPERTY()
		FRotator LastRotator;


// ========== 2019180016 ========== 
public:
	void SetPossessingPawn();
	void SetPlayerImage(int MaxPlayer, TArray<class ASkyscraperCharacter*> PlayerSelect, int SerialNum);
	void AddAllWidget();
//=================================
};
