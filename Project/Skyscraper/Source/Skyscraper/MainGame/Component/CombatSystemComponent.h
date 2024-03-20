// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Skyscraper/SkyscraperCharacter.h"
#include "CombatSystemComponent.generated.h"

class ASkyscraperCharacter;
UCLASS
( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SKYSCRAPER_API UCombatSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatSystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
		ASkyscraperCharacter* OwnerCharacter;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE USkeletalMeshComponent* GetOwnerMeshComponent() { return OwnerCharacter->GetMesh(); }
	FORCEINLINE APlayerController* GetOwnerPlayerController() { return Cast<APlayerController>(OwnerCharacter->GetController()); }
};
