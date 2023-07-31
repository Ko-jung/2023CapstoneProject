// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyBasePawn.generated.h"

class UCapsuleComponent;
class AProjectile;

UCLASS()
class UDEMYSECTION05_API AMyBasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyBasePawn();

	void HandleDestruction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void RotateTurret(FVector LookAtTarget) const;
	void Fire();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> ProjectileSpawnPoint;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly,Category="Combat")
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat Effect");
	TObjectPtr<UParticleSystem> DeathParticles;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<USoundBase> DeathSound;

	UPROPERTY(EditAnywhere, Category = "Camera Shake")
	TSubclassOf<UCameraShakeBase> DeathCameraShakeClass;
};
