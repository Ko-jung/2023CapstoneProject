// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NetworkManager.h"

#include "SocketGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API USocketGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init();
	
public:
	void SetSelectInfo(TArray<PPlayerSelectInfo*> s) { SelectInfo = s; }
	void SetSocket(NetworkManager* s) { Socket = s; }

	TArray<PPlayerSelectInfo*> GetSelectInfo() { return SelectInfo; }
	NetworkManager* GetSocket() { return Socket; }

private:
	TArray<PPlayerSelectInfo*>	SelectInfo;
	NetworkManager*				Socket;
};
