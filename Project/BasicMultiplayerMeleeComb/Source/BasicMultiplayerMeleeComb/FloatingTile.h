// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingTile.generated.h"

UCLASS()
class BASICMULTIPLAYERMELEECOMB_API AFloatingTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

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

};
