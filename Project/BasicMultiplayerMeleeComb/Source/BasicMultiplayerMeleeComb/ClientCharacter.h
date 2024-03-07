// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicCharacter.h"
#include "ClientCharacter.generated.h"

/**
 * 내가 조종할 캐릭터
 */
UCLASS()
class BASICMULTIPLAYERMELEECOMB_API AClientCharacter : public ABasicCharacter
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
