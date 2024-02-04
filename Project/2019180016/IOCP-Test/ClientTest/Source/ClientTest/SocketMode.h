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

public:
	virtual void BeginPlay() override;
	virtual void Tick(float) override;

	UPROPERTY(EditAnywhere)
	UStaticMesh* BlueprintTempCube;

	UPROPERTY(BlueprintReadWrite)
	FVector CubeVec;	
private:
	ClientSocketMgr* m_Socket;
	bool m_bIsConnected;
};
