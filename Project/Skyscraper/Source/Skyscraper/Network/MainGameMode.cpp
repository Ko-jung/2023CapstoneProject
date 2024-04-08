// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"

#include "SocketGameInstance.h"

#include "../MainGame/Actor/Character/SkyscraperCharacter.h"
#include "../MainGame/Component/Health/HealthComponent.h"

void AMainGameMode::BeginPlay()
{
	USocketGameInstance* instance = static_cast<USocketGameInstance*>(GetGameInstance());
	TArray<PPlayerSelectInfo*> PlayerSelectInfo = instance->GetSelectInfo();
	bIsConnected = instance->GetIsConnect();
	m_Socket = instance->GetSocket();
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
			break;
		case ECharacter::Boomerang:
			Class = BoomerangCharacter;
			break;
		case ECharacter::Detector:
			Class = DetectionCharacter;
			break;
		case ECharacter::Elect:
			Class = ElectricCharacter;
			break;
		case ECharacter::Shield:
			Class = ShieldCharacter;
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

	//if (bIsConnected)
	//{
	//}
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

			Characters[PCPHP->ChangedPlayerSerial]->HealthComponent->ChangeCurrentHp(PCPHP->AfterHP);
			break;
		}
		case ECHANGEDPLAYERSTATE:
		{
			PChangedPlayerState* PCPS = static_cast<PChangedPlayerState*>(argu);

			Characters[PCPS->ChangedPlayerSerial]->HealthComponent->ChangeState(PCPS->State);
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

void AMainGameMode::Test_TakeDamage(int DamageType)
{
	PDamagedPlayer PDP;
	PDP.ChangedPlayerSerial = SerialNum;
	switch (DamageType)
	{
	case 0:
		PDP.IsMelee = true;
		PDP.WeaponEnum = 0;
		break;
	case 1:
		PDP.IsMelee = true;
		PDP.WeaponEnum = 1;
		break;
	case 2:
		PDP.IsMelee = true;
		PDP.WeaponEnum = 2;
		break;
	case 3:
		PDP.IsMelee = false;
		PDP.WeaponEnum = 0;
		break;
	case 4:
		PDP.IsMelee = false;
		PDP.WeaponEnum = 1;
		break;
	case 5:
		PDP.IsMelee = false;
		PDP.WeaponEnum = 2;
		break;
	case 6:
	case 7:
	default:
		break;
	}

	UE_LOG(LogTemp, Warning, TEXT("PDP.ChangedPlayerSerial Is %d!"), PDP.ChangedPlayerSerial);
	UE_LOG(LogTemp, Warning, TEXT("sizeof(PDamagedPlayer) Is %d!, sizeof(PDP) Is %d!"), sizeof(PDamagedPlayer), sizeof(PDP));
	m_Socket->Send(&PDP, sizeof(PDamagedPlayer));
}

void AMainGameMode::Test_TakeDamageACharacter(ASkyscraperCharacter* DamageType)
{

}
