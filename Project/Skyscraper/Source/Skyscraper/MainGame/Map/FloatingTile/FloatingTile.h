// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingTile.generated.h"

UCLASS()
class SKYSCRAPER_API AFloatingTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// 생성자
	AFloatingTile();

	/* SpawnActorDeferred 시 Initialize 함수 */
	void Initialize(FVector GetMovementOffset);

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

	/* 시작 위치 */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		FVector InitStartLocation;

	/* 반대편 위치 */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		FVector InitEndLocation;

	/* 현재 목표 지점 */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		FVector TargetLocation;

	//임시 타이머 핸들
	FTimerHandle TimerHandle;


public:	
	// Tick
	virtual void Tick(float DeltaTime) override;

};
