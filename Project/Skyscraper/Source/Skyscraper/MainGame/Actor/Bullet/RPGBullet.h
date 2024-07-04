// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RPGBullet.generated.h"

class UNiagaraSystem;
class UProjectileMovementComponent;

UCLASS()
class SKYSCRAPER_API ARPGBullet : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	ARPGBullet();

	virtual void PostInitializeComponents() override;
	void Initialize(AActor* getFireCharacter, FVector getInitVelocity, float getInitSpeed, float getDamage);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// StaticMesh Overlap 이벤트 발생시 실행될 함수
	UFUNCTION()
		void OverlapExplode(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// StaticMesh Hit 이벤트 발생시 실행될 함수
	UFUNCTION()
		void HitExplode(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// 탄 폭발에 대한 함수
	void BulletExplode();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

protected:
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
		float EffectiveDistance;
	UPROPERTY()
		float CurrentDistance;

	UPROPERTY(VisibleAnywhere)
		AActor* FireCharacter;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UParticleSystem> ExplodeParticle;

	TObjectPtr<UNiagaraSystem> NS_Explosion;


private:

};
