// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"

#include "SocketGameInstance.h"

#include "MainGame/Actor/Character/SkyscraperCharacter.h"

void AMainGameMode::BeginPlay()
{
	USocketGameInstance* instance = static_cast<USocketGameInstance*>(GetGameInstance());
	TArray<PPlayerSelectInfo*> PlayerSelectInfo = instance->GetSelectInfo();
	m_Socket = instance->GetSocket();
	bIsConnected = instance->GetIsConnect();

	Super::BeginPlay();

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
			Characters.Add(GetWorld()->SpawnActor<ASkyscraperCharacter>(AssassinCharacter, spawnLocation, rotator, spawnParams));
			break;
		case ECharacter::Boomerang:
			Characters.Add(GetWorld()->SpawnActor<ASkyscraperCharacter>(BoomerangCharacter, spawnLocation, rotator, spawnParams));
			break;
		case ECharacter::Detector:
			Characters.Add(GetWorld()->SpawnActor<ASkyscraperCharacter>(DetectionCharacter, spawnLocation, rotator, spawnParams));
			break;
		case ECharacter::Elect:
			Characters.Add(GetWorld()->SpawnActor<ASkyscraperCharacter>(ElectricCharacter, spawnLocation, rotator, spawnParams));
			break;
		case ECharacter::Shield:
			Characters.Add(GetWorld()->SpawnActor<ASkyscraperCharacter>(ShieldCharacter, spawnLocation, rotator, spawnParams));
			break;
		case ECharacter::Wind:
			Characters.Add(GetWorld()->SpawnActor<ASkyscraperCharacter>(WindCharacter, spawnLocation, rotator, spawnParams));
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
