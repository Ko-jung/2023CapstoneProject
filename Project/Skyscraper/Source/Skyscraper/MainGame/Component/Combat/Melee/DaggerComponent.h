// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainMeleeComponent.h"
#include "DaggerComponent.generated.h"

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API UDaggerComponent : public UMainMeleeComponent
{
	GENERATED_BODY()

	// ���� ���⿡ ���� ����
	UPROPERTY()
		USkeletalMeshComponent* SubWeaponMeshComponent;
	UPROPERTY()
		FName SubWeaponSocketName;
public:
	UDaggerComponent();

protected:
	virtual void BeginPlay() override;

	// ���� ���� skeletal mesh�� visible�� �������ִ� �Լ�
	virtual void SetWeaponHiddenInGame(bool bNewHidden) const override;
};
