// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MainRangeComp.generated.h"

//class UOwnerGetterComp;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BASICMULTIPLAYERMELEECOMB_API UMainRangeComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMainRangeComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//UPROPERTY()
	//TObjectPtr<UOwnerGetterComp> OwnerGetterComp;
	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
