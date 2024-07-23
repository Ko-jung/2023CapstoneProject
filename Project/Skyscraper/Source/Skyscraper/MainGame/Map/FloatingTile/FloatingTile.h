// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Skyscraper/MainGame/Interface/Destructible/Collapsible.h"
#include "FloatingTile.generated.h"

class UNiagaraComponent;
class UGeometryCollection;

UCLASS()
class SKYSCRAPER_API AFloatingTile : public AActor, public ICollapsible
{
	GENERATED_BODY()
	
public:	
	// 생성자
	AFloatingTile();

	/* SpawnActorDeferred 시 Initialize 함수 */
	void Initialize(FVector GetMovementOffset);
	void InitializeProperty(double speed, float MoveTime, float WaitTime);

	/* BeginPlay시 실행될 함수 */
	void SetInitialSetting();

protected:
	// Begin Play
	virtual void BeginPlay() override;

	/* 부유 타일 static mesh */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default")
		TObjectPtr<UStaticMeshComponent> StaticMesh;

	/** 시작위치로부터 움직일 거리 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default", meta = (ExposeOnSpawn = "true"))
		FVector MovementOffset;

	/* 진행 방향에 대한 bool */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		bool MoveToEnd;

	/* 속도 */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		double Speed;

	/* 이동 시간 */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		float MoveTime;

	/* 대기 시간 */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		float WaitTime;

	/* 현재 시간 */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		float CurrentTime;

	// ===== 2019180016 =====
	/*위 세 개 속성들이 외부에의해 초기화가 되었는지*/
		bool IsInitProperty;
	// ======================

	/* 시작 위치 */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		FVector InitStartLocation;

	/* 반대편 위치 */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		FVector InitEndLocation;

	//임시 타이머 핸들
	FTimerHandle TimerHandle;

	/* 붕괴 후 생길 Geometry Collection */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Geometry")
		UClass* GC_Tile;

	UPROPERTY()
		TObjectPtr<UNiagaraComponent> NS_BoostEffect;

public:	
	// Tick
	virtual void Tick(float DeltaTime) override;

	// ICollapsible
	virtual void DoCollapse() override;
};
