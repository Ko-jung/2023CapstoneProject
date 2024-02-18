// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ClientSocketMgr.h"

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

	UPROPERTY(BlueprintReadWrite)
	FVector CubeVec;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SpawnPlayer(int serial);

	UFUNCTION(BlueprintNativeEvent)
	void TestPrintHelloUseNative();

	UFUNCTION(BlueprintNativeEvent)
	void BPGetAllActorsOfThirdPerson();

	UFUNCTION(BlueprintNativeEvent)
	void BPSetPlayerPosition(int serial, FVector location, FRotator rotate);

	UFUNCTION(BlueprintNativeEvent)
	void BPPossess(int serial);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AOtherPlayerCharacter> OtherPlayerCharacterClass;

	UPROPERTY(BlueprintReadWrite)
	int SerialNum;

private:
	ClientSocketMgr* m_Socket;
	bool m_bIsConnected;

	TArray<class AClientController*> ClientControllers;
	//TMap<int, class AClientController*> ClientControllers;
};
