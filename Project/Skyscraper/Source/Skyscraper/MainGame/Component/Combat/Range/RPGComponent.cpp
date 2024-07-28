// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGComponent.h"

#include "NiagaraFunctionLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Skyscraper/MainGame/Actor/Bullet/RPGBullet.h"
#include "Skyscraper/MainGame/Component/Combat/CombatSystemComponent.h"
#include "Skyscraper/Subsystem/SkyscraperEngineSubsystem.h"
#include "Skyscraper/Network/MainGameMode.h"

TSubclassOf<ARPGBullet>* URPGComponent::pRPGBulletBPClass;

URPGComponent::URPGComponent()
{
	AnimMontageKey = ECharacterAnimMontage::ECAM_RPG;

	FireSoundName = TEXT("RPG_Fire");
	ReloadSoundName = TEXT("RPG_Reload");

	ReloadMaxCoolTime = 0.1f;
	BulletMaxCount = 5;
	FireMaxCoolTime = 1.0f;
	ReloadSpeedTime = 5.0f;

	RecoilAboveAmount = 1.0f;
	RecoilBesideAmount = 0.5f;
	RecoilTime = 0.1f;
	RecoilSpeed = 20.0f;

	RangeWeaponType = ERangeSelect::ERS_RPG;

	{ // 총알 에셋 로드s
		static ConstructorHelpers::FClassFinder<ARPGBullet> RPGBulletBPRef(TEXT("/Script/Engine.Blueprint'/Game/2019180031/MainGame/Actor/BP_RPGBullet.BP_RPGBullet_C'"));
		RPGBulletBPClass = RPGBulletBPRef.Class;
	}
	
	{ // 무기 에셋 로드 
		WeaponSocketName = TEXT("RPGSocket");
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> RPGSkeletalMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/2016180023/weapon/gun/rpg.rpg'"));
		WeaponMeshComponent->SetSkeletalMesh(RPGSkeletalMeshRef.Object);
	}

	{
		static ConstructorHelpers::FObjectFinder<UAnimSequence> RPG_Reload_AnimRef(TEXT("/Script/Engine.AnimSequence'/Game/2016180023/weapon/gun/rpg_Anim.rpg_Anim'"));
		WeaponReloadAnim = RPG_Reload_AnimRef.Object;
	}

	{
		static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_RPGBackblastRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/2019180031/MainGame/Fbx/RPGBackblast/NS_RPGBackblast.NS_RPGBackblast'"));
		if(NS_RPGBackblastRef.Succeeded())
		{
			NS_RPGBackblast = NS_RPGBackblastRef.Object;
		}
		
	}
	
	pRPGBulletBPClass = &RPGBulletBPClass;
}

void URPGComponent::Fire(float fBaseDamage)
{
	if (!OwnerCharacter || !OwnerCharacter->InputEnabled()) return;

	// ===== 2019180016 =====
	// Spawn Bullet On Server
	if (GetOwnerPlayerController())
	{
		AMainGameMode* GameMode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(OwnerCharacter));
		if (GameMode && GameMode->GetIsConnected())
		{
			UseBullet();

			FVector SpawnLocation = OwnerCharacter->GetActorLocation();

			FVector BulletDestination = GetOwnerPlayerController()->GetControlRotation().Vector() * 8000.0f
				+ OwnerCharacter->GetCameraBoom()->GetComponentLocation();

			FVector LocationOffset = OwnerCharacter->GetActorForwardVector() * 225.0f + OwnerCharacter->GetActorRightVector() * 15.0f + FVector{ 0.0f, 0.0f, 50.0f };
			FVector StartLocation = OwnerCharacter->GetActorLocation() + LocationOffset;

			FVector Direction = (BulletDestination - StartLocation);
			Direction.Normalize();

			FRotator Rotation(0.0f, 0.0f, 0.0f);

			FActorSpawnParameters SpawnInfo;
			FTransform SpawnTransform{};
			SpawnTransform.SetLocation(StartLocation);
			SpawnTransform.SetRotation(Rotation.Quaternion());
			SpawnTransform.SetScale3D(FVector(1.0f, 1.0f, 1.0f));

			GameMode->SendSpawnBullet(OwnerCharacter, EObjectType::RPGBullet, SpawnTransform, Direction);
			return;
		}
	}	
	// ======================

	if (!GetOwnerPlayerController())
	{
		FVector Location = OwnerCharacter->GetActorLocation() +
			OwnerCharacter->GetActorForwardVector() * 100 + FVector{0.0f,0.0f,70.0f};
		FTransform SpawnTransform{};
		SpawnTransform.SetLocation(Location);
		ARPGBullet* BulletActor = GetWorld()->SpawnActorDeferred<ARPGBullet>(RPGBulletBPClass, SpawnTransform);
		if (BulletActor)
		{

			BulletActor->Initialize(OwnerCharacter, OwnerCharacter->GetActorForwardVector(), 5000.0f, fBaseDamage);
			BulletActor->FinishSpawning(SpawnTransform);
		}
		return;
	}
		
		

	UseBullet();

	fBaseDamage *= OwnerCharacter->GetPowerBuffValue();

	FVector SpawnLocation = OwnerCharacter->GetActorLocation();

	FVector BulletDestination = GetOwnerPlayerController()->GetControlRotation().Vector() * 8000.0f  
								+ OwnerCharacter->GetCameraBoom()->GetComponentLocation();

	FVector LocationOffset = OwnerCharacter->GetActorForwardVector() * 225.0f + OwnerCharacter->GetActorRightVector() * 15.0f + FVector{0.0f, 0.0f, 50.0f};
	FVector StartLocation = OwnerCharacter->GetActorLocation() + LocationOffset;

	FVector Direction = (BulletDestination - StartLocation);
	Direction.Normalize();
	

	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	//AActor* BulletActor = GetWorld()->SpawnActor<ARPGBullet>(RPGBulletBPClass,Location, Rotation, SpawnInfo);
	FTransform SpawnTransform{};
	SpawnTransform.SetLocation(StartLocation);
	SpawnTransform.SetRotation(Rotation.Quaternion());
	SpawnTransform.SetScale3D(FVector(1.0f, 1.0f, 1.0f));

	ARPGBullet* BulletActor = GetWorld()->SpawnActorDeferred<ARPGBullet>(RPGBulletBPClass, SpawnTransform);
	if(BulletActor)
	{
		BulletActor->Initialize(OwnerCharacter, Direction, 5000.0f, fBaseDamage);
		BulletActor->FinishSpawning(SpawnTransform);
	}

	//Backblast Effect
	{
		if(NS_RPGBackblast)
		{
			FTransform Transform = WeaponMeshComponent->GetSocketTransform(TEXT("BackblastSocket"));
			UNiagaraComponent* FX = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NS_RPGBackblast, Transform.GetLocation(), Transform.Rotator());
		}
	}

	// Play Sound
	{
		if(USkyscraperEngineSubsystem* Subsystem = GEngine->GetEngineSubsystem<USkyscraperEngineSubsystem>())
		{
			if (USoundBase* FireSound = Subsystem->GetSkyscraperSound(FireSoundName))
			{
				if (USoundAttenuation* SoundAttenuation = Subsystem->GetSkyscraperSoundAttenuation())
				{
					UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, SpawnLocation, FRotator{}, 1, 1, 0, SoundAttenuation);
				}
			}
		}
		
	}
}

void URPGComponent::SetInitialValue()
{
	Super::SetInitialValue();

	UCombatSystemComponent* CombatComponent{};
	if (OwnerCharacter)
		CombatComponent = OwnerCharacter->CombatSystemComponent;

	if (CombatComponent)
	{
		FireMaxCoolTime = CombatComponent->RPG_FireTime;
		ReloadSpeedTime = CombatComponent->RPG_ReloadTime;
	}
}

void URPGComponent::Fire(UWorld* World, AActor* FireCharacter, FTransform Transform, FVector Direction, float fBaseDamage)
{
	FActorSpawnParameters SpawnInfo;
	FTransform SpawnTransform{};
	SpawnTransform.SetLocation(Transform.GetLocation());
	SpawnTransform.SetRotation(Transform.GetRotation());
	SpawnTransform.SetScale3D(Transform.GetScale3D());

	ARPGBullet* BulletActor = World->SpawnActorDeferred<ARPGBullet>(*pRPGBulletBPClass, SpawnTransform);
	if (BulletActor)
	{
		BulletActor->Initialize(FireCharacter, Direction, 5000.0f, fBaseDamage);
		BulletActor->FinishSpawning(SpawnTransform);
	}
}
