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
	m_Socket->SetGamemode(this);
	m_Socket->StartListen();

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

	SendPlayerLocation();

	ProcessFunc();
}

void AMainGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AMainGameMode::ProcessFunc()
{
	std::pair<EFunction, Packet*> EFunc;
	while (FuncQueue.try_pop(EFunc))
	{
		EFunction func = EFunc.first;
		Packet* argu = EFunc.second;

		switch (func)
		{
		case EPLAYERTRANSFORM:
		{
			PPlayerPosition* PPP = static_cast<PPlayerPosition*>(argu);
			SetPlayerPosition(*PPP);
			break;
		}
		case ECHANGEDPLAYERHP:
		{
			PChangedPlayerHP* PCPHP = static_cast<PChangedPlayerHP*>(argu);

			// Set Player HP
			break;
		}
		default:
			break;
		}
		delete argu;
	}
}

void AMainGameMode::SetPlayerPosition(PPlayerPosition PlayerPosition)
{
	int32 Serial = PlayerPosition.PlayerSerial;
	FVector Location{ PlayerPosition.x, PlayerPosition.y, PlayerPosition.z };
	FRotator Rotate{ PlayerPosition.rx, PlayerPosition.ry, PlayerPosition.rz };
	EPlayerState state = PlayerPosition.PlayerState;
	// EnumPlayerState ArguState;

	FTransform transform{ Rotate, Location, FVector(1.f,1.f,1.f) };

	float speed = PlayerPosition.PlayerSpeed;

	Characters[Serial]->SyncTransformAndAnim(transform, speed);
}

void AMainGameMode::SendPlayerLocation()
{
	FVector location = Characters[SerialNum]->GetActorLocation();
	FRotator rotate = Characters[SerialNum]->GetActorRotation();
	int speed = Characters[SerialNum]->GetSpeed();
	//FRotator rotate = transform.GetRotation();

	PPlayerPosition PlayerPosition;
	PlayerPosition.PlayerSerial = SerialNum;

	PlayerPosition.x = location.X;
	PlayerPosition.y = location.Y;
	PlayerPosition.z = location.Z;

	PlayerPosition.rx = rotate.Pitch;
	PlayerPosition.ry = rotate.Yaw;
	PlayerPosition.rz = rotate.Roll;


	PlayerPosition.PlayerSpeed = speed;

	m_Socket->Send(&PlayerPosition, sizeof(PPlayerPosition));
}
