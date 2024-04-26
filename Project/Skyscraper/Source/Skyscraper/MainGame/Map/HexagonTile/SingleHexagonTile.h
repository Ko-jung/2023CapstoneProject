// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SingleHexagonTile.generated.h"

UCLASS()
class SKYSCRAPER_API ASingleHexagonTile : public AActor
{
	GENERATED_BODY()


public:	
	// Sets default values for this actor's properties
	ASingleHexagonTile();

	/* ¡ﬂæ” ¿∞∞¢≈∏¿œø° ¥Î«— static mesh */
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* HexagonTileStaticMesh;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
