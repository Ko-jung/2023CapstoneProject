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
	SerialNum = instance->GetSerialNum();

	Super::BeginPlay();

	// Spawn Characters
	FActorSpawnParameters spawnParams;
	FRotator rotator;
	FVector spawnLocation{ 0.f,0.f,100.f };

	int i = 0;
	for (const auto& p : PlayerSelectInfo)
	{
		TSubclassOf<class ASkyscraperCharacter> Class;
		spawnLocation.Y = i * 200;
		switch (p->PickedCharacter)
		{
		case ECharacter::Assassin:
			Class = AssassinCharacter;
			//Characters.Add(GetWorld()->SpawnActor<ASkyscraperCharacter>(AssassinCharacter, spawnLocation, rotator, spawnParams));
			break;
		case ECharacter::Boomerang:
			Class = BoomerangCharacter;
			//Characters.Add(GetWorld()->SpawnActor<ASkyscraperCharacter>(BoomerangCharacter, spawnLocation, rotator, spawnParams));
			break;
		case ECharacter::Detector:
			Class = DetectionCharacter;
			//Characters.Add(GetWorld()->SpawnActor<ASkyscraperCharacter>(DetectionCharacter, spawnLocation, rotator, spawnParams));
			break;
		case ECharacter::Elect:
			Class = ElectricCharacter;
			//Characters.Add(GetWorld()->SpawnActor<ASkyscraperCharacter>(ElectricCharacter, spawnLocation, rotator, spawnParams));
			break;
		case ECharacter::Shield:
			Class = ShieldCharacter;
			//Characters.Add(GetWorld()->SpawnActor<ASkyscraperCharacter>(ShieldCharacter, spawnLocation, rotator, spawnParams));
			break;
		case ECharacter::Wind:
			Class = WindCharacter;
			break;
		case ECharacter::NullCharacter:
			UE_LOG(LogClass, Warning, TEXT("%d: Client Select Info Is NULLCHARACTER!"), i);
			break;
		default:
			break;
		}
		Characters.Add(GetWorld()->SpawnActor<ASkyscraperCharacter>(Class, spawnLocation, rotator, spawnParams));
		i++;
	}
	GetWorld()->GetFirstPlayerController()->Possess(Characters[SerialNum]);
}

void AMainGameMode::Tick(float Deltatime)
{
	Super::Tick(Deltatime);
}

void AMainGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}