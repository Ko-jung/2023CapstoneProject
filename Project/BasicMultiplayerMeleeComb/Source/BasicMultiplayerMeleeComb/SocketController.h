// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <concurrent_queue.h>
#include "../../Packet/Packet.h"

#include "SocketController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

enum EFunction
{
	ESPAWNPLAYER,
	EBPPOSSESS,
	EPLAYERTRANSFORM,
};

/**
 * 
 */
UCLASS()
class BASICMULTIPLAYERMELEECOMB_API ASocketController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason);
	virtual void Tick(float) override;

	void PushQueue(EFunction e, Packet* etc);
	void ProcessFunc();

private:
	class NetworkMgr* NetworkManager;

	concurrency::concurrent_queue<std::pair<EFunction, Packet*>> FuncQueue;
};
