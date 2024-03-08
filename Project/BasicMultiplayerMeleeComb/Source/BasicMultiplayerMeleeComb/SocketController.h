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

UENUM(BlueprintType)
enum class EnumPlayerState : uint8 {
	EStay       UMETA(DisplayName = "Stay"),
	EWalk       UMETA(DisplayName = "Walk"),
	EJump		UMETA(DisplayName = "Jump"),
	ERun		UMETA(DisplayName = "Run"),
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

	void JoinOtherPlayer(int serial);
	void SetOwnSerialNum(int serial);
	void SetPlayerPosition(PPlayerPosition PlayerPosition);

	UFUNCTION(BlueprintCallable)
	void Disconnect();

	void PushQueue(EFunction e, Packet* etc);
	void ProcessFunc();

protected:
	/* Key Input */
	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> IMC_Default;
	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_Move;
	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_Look;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

public:
	UPROPERTY(BlueprintReadWrite)
	int SerialNum;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AClientCharacter> ClientCharacter;

private:
	class NetworkMgr* NetworkManager;
	bool IsConnected;

	concurrency::concurrent_queue<std::pair<EFunction, Packet*>> FuncQueue;
};
