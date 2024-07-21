// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skyscraper/MainGame/Actor/LootingItem/LootingItemActor.h"
#include "ElevatorActor.generated.h"

UCLASS()
class SKYSCRAPER_API AElevatorActor : public ALootingItemActor
{
	GENERATED_BODY()

public:
	AElevatorActor();

	FORCEINLINE void InitializeElevator(const FVector& Destination) { ElevatorDestination = Destination; }

	virtual void ItemInteraction(AActor* InteractionActor) override;
protected:
	virtual void SetProgressBarPercent() const override;
private:
	void ElevatorTimerAction();
	
	void ApplyElevator(ASkyscraperCharacter* InteractionCharacter);

public:
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		TObjectPtr<UStaticMeshComponent> LeftDoor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TObjectPtr<UStaticMeshComponent> RightDoor;

	float DoorOffset = 75.0f;

	UPROPERTY()
		FTimerHandle TimerHandle;

	UPROPERTY()
		FVector ElevatorDestination;

	UPROPERTY()
		FVector ElevatorLocationOffset;

	UPROPERTY()
		TSubclassOf<UUserWidget> FadeInWidgetClass;

	UPROPERTY()
		ASkyscraperCharacter* ElevatorApplyCharacter;
private:
};
