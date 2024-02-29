// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ClientSocketMgr.h"

#include <concurrent_queue.h>
#include <queue>
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

#include "SocketMode.generated.h"


/**
 * 
 */
UCLASS()
class CLIENTTEST_API ASocketMode : public AGameModeBase
{
	GENERATED_BODY()

	// �ۼ��� ó���� �Լ�
public:
	void JoinOtherPlayer(int serial);
	void SetOwnSerialNum(int serial);
	void SetPlayerPosition(PPlayerPosition PlayerPosition);

	UFUNCTION(BlueprintCallable)
	void Disconnect();

public:
	virtual void BeginPlay() override;
	virtual void Tick(float) override;

	void PushQueue(EFunction e, Packet* etc);
	void ProcessFunc();

	UPROPERTY(BlueprintReadWrite)
	FVector CubeVec;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SpawnPlayer(int serial);

	UFUNCTION(BlueprintNativeEvent)
	void TestPrintHelloUseNative();

	UFUNCTION(BlueprintNativeEvent)
	void BPGetAllActorsOfThirdPerson();

	UFUNCTION(BlueprintNativeEvent)
	void BPSetPlayerPosition(int serial, FVector location, FRotator rotate, EnumPlayerState state);

	UFUNCTION(BlueprintNativeEvent)
	void BPPossess(int serial);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AOtherPlayerCharacter> OtherPlayerCharacterClass;

	UPROPERTY(BlueprintReadWrite)
	int SerialNum;

	UPROPERTY(BlueprintReadWrite)
	TArray<FTransform> ClientTransform;

	UPROPERTY(BlueprintReadWrite)
	TArray<EnumPlayerState> ClientState;

private:
	ClientSocketMgr* m_Socket;
	bool m_bIsConnected;

	concurrency::concurrent_queue<std::pair<EFunction, Packet*>> FuncQueue;
};
