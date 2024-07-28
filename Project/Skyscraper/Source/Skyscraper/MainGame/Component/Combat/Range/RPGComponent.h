// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainRangeComponent.h"
#include "RPGComponent.generated.h"

class UNiagaraSystem;
class ARPGBullet;
/**
 * 
 */
UCLASS()
class SKYSCRAPER_API URPGComponent : public UMainRangeComponent
{
	GENERATED_BODY()

	TSubclassOf<ARPGBullet> RPGBulletBPClass;
	static TSubclassOf<ARPGBullet>* pRPGBulletBPClass;
public:
	URPGComponent();

	virtual void Fire(float fBaseDamage) override;
	virtual void SetInitialValue() override;

	void SpawnEffectAndSound(FVector SpawnLocation);

	static void Fire(UWorld* World, AActor* FireCharacter, FTransform Transform, FVector Direction, float fBaseDamage);
protected:

private:

public:

protected:
	UPROPERTY()
		TObjectPtr<UNiagaraSystem> NS_RPGBackblast;

private:

};
