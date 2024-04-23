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
	// ������
	AFloatingTile();

	/* SpawnActorDeferred �� Initialize �Լ� */
	void Initialize(FVector GetMovementOffset);

	/* BeginPlay�� ����� �Լ� */
	void SetInitialSetting();

protected:
	// Begin Play
	virtual void BeginPlay() override;

	/* ���� Ÿ�� static mesh */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default")
		TObjectPtr<UStaticMeshComponent> StaticMesh;

	/** ������ġ�κ��� ������ �Ÿ� */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default", meta = (ExposeOnSpawn = "true"))
		FVector MovementOffset;

	/* ���� ���⿡ ���� bool */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		bool MoveToEnd;

	/* �ӵ� */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		double Speed;

	/* ���� ��ġ */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		FVector InitStartLocation;

	/* �ݴ��� ��ġ */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		FVector InitEndLocation;

	/* ���� ��ǥ ���� */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		FVector TargetLocation;

	//�ӽ� Ÿ�̸� �ڵ�
	FTimerHandle TimerHandle;


public:	
	// Tick
	virtual void Tick(float DeltaTime) override;

};
