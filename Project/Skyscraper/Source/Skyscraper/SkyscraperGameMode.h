// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Network/NetworkGameMode.h"
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
	void SendSelectInfo();

	void UpdateSelectInfo(ECharacterSelect Character);
	void UpdateSelectInfo(EMeleeSelect MeleeWeapon);
	void UpdateSelectInfo(ERangeSelect RangeWeapon);

	TArray<PPlayerSelectInfo*>& GetPlayerSelectInfo() { return PlayerSelectInfo; }

	UPROPERTY(BlueprintReadOnly)
	double SelectTimer;

	UPROPERTY(EditAnywhere)
	bool IsBeConnect;
private:
	// Memory Leak
	TArray<PPlayerSelectInfo*> PlayerSelectInfo;
};



