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

	// 송수신 처리용 함수
public:
	void JoinOtherPlayer(int serial);

	UFUNCTION(BlueprintCallable)
	void SpawnOtherPlayer();

	UFUNCTION(BlueprintCallable)
	void Disconnect();

public:
	virtual void BeginPlay() override;
	virtual void Tick(float) override;

	UPROPERTY(EditAnywhere)
	UStaticMesh* BlueprintTempCube;

	UPROPERTY(BlueprintReadWrite)
	FVector CubeVec;

	UPROPERTY(EditAnywhere)
	ACharacter* SpawnPlayerCharacter;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SpawnPlayer();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AOtherPlayerCharacter> OtherPlayerCharacterClass;

private:
	ClientSocketMgr* m_Socket;
	bool m_bIsConnected;

	TArray<class AClientController*> ClientControllers;
	//TMap<int, class AClientController*> ClientControllers;
};
