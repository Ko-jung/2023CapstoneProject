// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "TrainingBot.generated.h"

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API ATrainingBot : public ASkyscraperCharacter
{
	GENERATED_BODY()
	
public:
	ATrainingBot();

	virtual void DoStun(const AActor* Attacker, const float StunTime, const FVector StunDirection) const;
	virtual void DoDown(const AActor* Attacker, const FVector& DownDirection) const;
	
	// 2019180016
	void SetTimer();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	FTransform BotBeginTransform;

	UPROPERTY(EditAnywhere)
	float ResetTimer;

	float DamagedTimer;
	//================

public:
protected:
private:
};
