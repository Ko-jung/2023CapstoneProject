// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OwnerGetterComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BASICMULTIPLAYERMELEECOMB_API UOwnerGetterComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOwnerGetterComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> OwnerClass;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** 소유자 플레이어 컨트롤러 Getter */
	UFUNCTION(BlueprintPure, Category = "Owner")
		APlayerController* GetOwnerPlayerController();

	/** 소유자 카메라 컴퍼넌트 Getter */
	UFUNCTION(BlueprintPure, Category = "Owner")
		UCameraComponent* GetOwnerCameraComponent();
	

	/* 소유자 캐릭터 메쉬 컴퍼넌트 Getter */
	UFUNCTION(BlueprintPure, Category = "Owner")
		USkeletalMeshComponent* GetCharacterMesh();

	/** 소유자 SpringArm 컴퍼넌트 Getter */
	UFUNCTION(BlueprintPure, Category = "Owner")
		USpringArmComponent* GetOwnerSpringArmComponent();





};
