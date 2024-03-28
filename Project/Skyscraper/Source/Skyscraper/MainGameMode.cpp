// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"

#include "SocketGameInstance.h"

#include "MainGame/Actor/Character/SkyscraperCharacter.h"

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	USocketGameInstance* instance = static_cast<USocketGameInstance*>(GetGameInstance());
	TArray<PPlayerSelectInfo*> PlayerSelectInfo = instance->GetSelectInfo();
	m_Socket = instance->GetSocket();

	// Spawn Characters
	FActorSpawnParameters spawnParams;
	FRotator rotator;
	FVector spawnLocation = FVector::ZeroVector;

	int i = 0;
	for (const auto& p : PlayerSelectInfo)
	{
		switch (p->PickedCharacter)
		{

			case ECharacter::Assassin:
				Characters[i] = GetWorld()->SpawnActor<ASkyscraperCharacter>(AssassinCharacter, spawnLocation, rotator, spawnParams);
				break;
			case ECharacter::Boomerang:
				Characters[i] = GetWorld()->SpawnActor<ASkyscraperCharacter>(BoomerangCharacter, spawnLocation, rotator, spawnParams);
				break;
			case ECharacter::Detector:
				Characters[i] = GetWorld()->SpawnActor<ASkyscraperCharacter>(DetectionCharacter, spawnLocation, rotator, spawnParams);
				break;
			case ECharacter::Elect:
				Characters[i] = GetWorld()->SpawnActor<ASkyscraperCharacter>(ElectricCharacter, spawnLocation, rotator, spawnParams);
				break;
			case ECharacter::Shield:
				Characters[i] = GetWorld()->SpawnActor<ASkyscraperCharacter>(ShieldCharacter, spawnLocation, rotator, spawnParams);
				break;
			case ECharacter::Wind:
				Characters[i] = GetWorld()->SpawnActor<ASkyscraperCharacter>(WindCharacter, spawnLocation, rotator, spawnParams);
				break;
			case ECharacter::NullCharacter:
				UE_LOG(LogClass, Warning, TEXT("%d: Client Select Info Is NULLCHARACTER!"), i);
				break;
		default:
			break;
		}
		i++;
	}
}

void AMainGameMode::Tick(float Deltatime)
{
	Super::Tick(Deltatime);
}

void AMainGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
