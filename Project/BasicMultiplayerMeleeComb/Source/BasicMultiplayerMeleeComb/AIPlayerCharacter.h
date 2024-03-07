// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClientCharacter.h"
#include "AIPlayerCharacter.generated.h"

/**
 * 외부에서 Transform, 애니메이션을 조종할 캐릭터 (나를 제외한 클라)
 */
UCLASS()
class BASICMULTIPLAYERMELEECOMB_API AAIPlayerCharacter : public AClientCharacter
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	float speed;
};
