// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NetworkGameMode.h"
#include "SkyscraperGameMode.generated.h"

UCLASS(minimalapi)
class ASkyscraperGameMode : public ANetworkGameMode
{
	GENERATED_BODY()

public:
	ASkyscraperGameMode();

	//virtual void PushQueue(EFunction e, Packet* etc);
	virtual void ProcessFunc();

	virtual void BeginPlay() override;
	virtual void Tick(float) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void ProcessSelectInfo(Packet* argu);

	void UpdateSelectInfo(ECharacter	Character);
	void UpdateSelectInfo(EMeleeWeapon	MeleeWeapon);
	void UpdateSelectInfo(ERangeWeapon	RangeWeapon);

private:
	TArray<PPlayerSelectInfo*> PlayerSelectInfo;
};



