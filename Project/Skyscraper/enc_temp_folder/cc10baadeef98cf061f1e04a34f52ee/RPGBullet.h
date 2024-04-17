// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RPGBullet.generated.h"

class UProjectileMovementComponent;

UCLASS()
class SKYSCRAPER_API ARPGBullet : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UStaticMeshComponent> BulletStaticMesh;
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UParticleSystemComponent> FireParticleComponent;
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UParticleSystemComponent> SteamParticleComponent;
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere)
		FVector InitVelocity;
	UPROPERTY(VisibleAnywhere)
		float InitSpeed;
	UPROPERTY(VisibleAnywhere)
		float Damage;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UParticleSystem> ExplodeParticle;
public:	
	// Sets default values for this actor's properties
	ARPGBullet();

	virtual void PostInitializeComponents() override;
	void Initialize(FVector getInitVelocity, float getInitSpeed, float getDamage);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void Explode(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
