// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"

#include "SocketGameInstance.h"

#include "../MainGame/Actor/Character/SkyscraperCharacter.h"
#include "../MainGame/Component/Health/HealthComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/GameUserSettings.h"

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

	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	UGameUserSettings::GetGameUserSettings()->SetFullscreenMode(EWindowMode::WindowedFullscreen);
	UGameUserSettings::GetGameUserSettings()->ApplySettings(false);

	// Spawn Characters
	FActorSpawnParameters spawnParams;
	FRotator rotator;
	FVector spawnLocation{ 0.f,0.f,100.f };

	int i = 0;
	for (const auto& p : PlayerSelectInfo)
	{
		bool CanAddTag = true;

		FName Team;
		if (i < MAXPLAYER / 2)	Team = FName{ "TeamA" };
		else					Team = FName{ "TeamB" };

		TSubclassOf<class ASkyscraperCharacter> Class;
		spawnLocation.Y = i * 200;
		switch (p->PickedCharacter)
		{
		case ECharacter::Assassin:
			(i == SerialNum) ? Class = AssassinCharacter : Class = AIAssassinCharacter;
			break;
		case ECharacter::Boomerang:
			(i == SerialNum) ? Class = BoomerangCharacter : Class = AIBoomerangCharacter;
			//Class = BoomerangCharacter;
			break;
		case ECharacter::Detector:
			(i == SerialNum) ? Class = DetectionCharacter : Class = AIDetectionCharacter;
			break;
		case ECharacter::Elect:
			(i == SerialNum) ? Class = ElectricCharacter : Class = AIElectricCharacter;
			break;
		case ECharacter::Shield:
			(i == SerialNum) ? Class = ShieldCharacter : Class = AIShieldCharacter;
			break;
		case ECharacter::Wind:
			(i == SerialNum) ? Class = WindCharacter : Class = AIWindCharacter;
			break;
		case ECharacter::NullCharacter:
			UE_LOG(LogClass, Warning, TEXT("%d: Client Select Info Is NULLCHARACTER!"), i);
			CanAddTag = false;
			break;
		default:
			break;
		}
		Characters.Add(GetWorld()->SpawnActor<ASkyscraperCharacter>(Class, spawnLocation, rotator, spawnParams));
		if(CanAddTag) Characters[i]->Tags.Add(Team);
		// Characters[i]->Tags.Init(Team, 0);
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
	ProcessFunc();
	SendPlayerLocation();

}

void AMainGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AMainGameMode::ProcessFunc()
{
	Packet* packet;
	while (FuncQueue.try_pop(packet))
	{
		switch (packet->PacketType)
		{
		case (BYTE)COMP_OP::OP_PLAYERPOSITION:
		{
			PPlayerPosition PPP;
			memcpy(&PPP, packet, sizeof(PPP));
			if (PPP.PlayerSerial >= MAXPLAYER || PPP.PlayerSerial < 0)
			{
				UE_LOG(LogClass, Warning, TEXT("COMP_OP::OP_PLAYERPOSITION Array Error"));
				continue;
			}
			SetPlayerPosition(PPP);
			break;
		}
		case (BYTE)COMP_OP::OP_CHANGEDPLAYERHP:
		{
			PChangedPlayerHP* PCPHP = static_cast<PChangedPlayerHP*>(packet);
			if (PCPHP->ChangedPlayerSerial >= MAXPLAYER || PCPHP->ChangedPlayerSerial < 0)
			{
				UE_LOG(LogClass, Warning, TEXT("Array Error"));
				continue;
			}
			Characters[PCPHP->ChangedPlayerSerial]->HealthComponent->ChangeCurrentHp(PCPHP->AfterHP);
			break;
		}
		case (BYTE)COMP_OP::OP_CHANGEDPLAYERSTATE:
		{
			PChangedPlayerState* PCPS = static_cast<PChangedPlayerState*>(packet);

			if (PCPS->ChangedPlayerSerial >= MAXPLAYER || PCPS->ChangedPlayerSerial < 0)
			{
				UE_LOG(LogClass, Warning, TEXT("Array Error"));
				continue;
			}

			Characters[PCPS->ChangedPlayerSerial]->HealthComponent->ChangeState(PCPS->State);
			break;
		}
		case (BYTE)COMP_OP::OP_DAMAGEDPLAYER:
		{
			//PDamagedPlayer* PDP = static_cast<PDamagedPlayer*>(packet);
			//m_Socket->Send(PDP, sizeof(PDamagedPlayer));
			m_Socket->Send(packet, sizeof(PDamagedPlayer));
			break;
		}
		case (BYTE)COMP_OP::OP_SPAWNOBJECT:
		{
			PSpawnObject PSO;
			memcpy(&PSO, packet, sizeof(PSO));

			if (PSO.SerialNum>= MAXPLAYER || PSO.SerialNum < 0)
			{
				UE_LOG(LogClass, Warning, TEXT("Array Error"));
				continue;
			}

			ProcessSpawnObject(PSO);
			UE_LOG(LogTemp, Warning, TEXT("ProcessSpawnObject called!"));
			break;
		}
		default:
			UE_LOG(LogTemp, Warning, TEXT("AMainGameMode::ProcessFunc() switch Default"));
			break;
		}
		delete packet;
	}
}

//void AMainGameMode::ProcessPosition()
//{
//	Packet* packet;
//	while (not PositionQueue.empty())
//	{
//		if (PositionQueue.try_pop(packet))
//		{
//			switch (packet->PacketType)
//			{
//			case (BYTE)COMP_OP::OP_PLAYERPOSITION:
//			{
//				PPlayerPosition PPP;
//				memcpy(&PPP, packet, sizeof(PPP));
//				if (PPP.PlayerSerial >= MAXPLAYER || PPP.PlayerSerial < 0)
//				{
//					UE_LOG(LogClass, Warning, TEXT("COMP_OP::OP_PLAYERPOSITION Array Error"));
//					continue;
//				}
//				SetPlayerPosition(PPP);
//				break;
//			}
//			}
//		}
//	}
//}

void AMainGameMode::SetPlayerPosition(PPlayerPosition PlayerPosition)
{
	int32 Serial = PlayerPosition.PlayerSerial;
	FVector Location{ PlayerPosition.Location.X, PlayerPosition.Location.Y, PlayerPosition.Location.Z };
	FRotator Rotate{ PlayerPosition.Rotate.X, PlayerPosition.Rotate.Y, PlayerPosition.Rotate.Z };
	EPlayerState state = PlayerPosition.PlayerState;
	// EnumPlayerState ArguState;

	FTransform transform{ Rotate, Location, FVector(1.f,1.f,1.f) };

	float speed = PlayerPosition.PlayerSpeed;
	float XRotate = PlayerPosition.PlayerXDirection;

	Characters[Serial]->SyncTransformAndAnim(transform, speed, XRotate);
}

void AMainGameMode::ProcessSpawnObject(PSpawnObject PSO)
{
	if (PSO.SerialNum == SerialNum)
	{
		UE_LOG(LogClass, Warning, TEXT("Skill Actor Spawner Is this!"));
		return;
	}

	FName Team;
	if (PSO.SerialNum < MAXPLAYER / 2)	Team = FName{ "TeamA" };
	else								Team = FName{ "TeamB" };

	FVector Location{ PSO.Location.X, PSO.Location.Y, PSO.Location.Z };
	FVector Forward{ PSO.ForwardVec.X, PSO.ForwardVec.Y, PSO.ForwardVec.Z };
	ESkillActor SkillActor;

	switch (PSO.SpawnObject)
	{
	case EObject::BP_BoomerangGrab:
	{
		SkillActor = ESkillActor::BP_BoomerangGrab;
		break;
	}
	default:
		SkillActor = ESkillActor::BP_BoomerangGrab;
		break;
	}

	SpawnSkillActor(SkillActor, Location, Forward, Characters[PSO.SerialNum], Team);
}

void AMainGameMode::SendPlayerLocation()
{
	FVector location = Characters[SerialNum]->GetActorLocation();
	FRotator rotate = Characters[SerialNum]->GetActorRotation();
	int speed = Characters[SerialNum]->GetVelocity().Length();
	//FRotator rotate = transform.GetRotation();

	PPlayerPosition PlayerPosition;
	PlayerPosition.PlayerSerial = SerialNum;

	PlayerPosition.Location.X = location.X;
	PlayerPosition.Location.Y = location.Y;
	PlayerPosition.Location.Z = location.Z;

	PlayerPosition.Rotate.X = rotate.Pitch;
	PlayerPosition.Rotate.Y = rotate.Yaw;
	PlayerPosition.Rotate.Z = rotate.Roll;

	PlayerPosition.PlayerSpeed = speed;

	FVector Velo = Characters[SerialNum]->GetVelocity();
	PlayerPosition.PlayerXDirection = CalculateDirection({ Velo.X,Velo.Y,0.f }, Characters[SerialNum]->GetActorRotation());

	m_Socket->Send(&PlayerPosition, sizeof(PPlayerPosition));
}

void AMainGameMode::SendSkillActorSpawn(ESkillActor SkillActor, FVector SpawnLocation, FVector ForwardVec)
{
	PSpawnObject PSO;
	switch (SkillActor)
	{
	case ESkillActor::BP_BoomerangGrab:
		PSO.SpawnObject = EObject::BP_BoomerangGrab;
		break;
	case ESkillActor::BP_BoomerangCenter:
		PSO.SpawnObject = EObject::BP_BoomerangCenter;
		break;
	case ESkillActor::BP_DetectorMine:
		PSO.SpawnObject = EObject::BP_DetectorMine;
		break;
	case ESkillActor::BP_Shield:
		PSO.SpawnObject = EObject::BP_Shield;
		break;
	case ESkillActor::BP_ShieldSphere:
		PSO.SpawnObject = EObject::BP_ShieldSphere;
		break;
	case ESkillActor::BP_ShieldSphereThrow:
		PSO.SpawnObject = EObject::BP_ShieldSphereThrow;
		break;
	case ESkillActor::BP_WindTornado:
		PSO.SpawnObject = EObject::BP_WindTornado;
		break;
	case ESkillActor::BP_ElectSphereBoom:
		PSO.SpawnObject = EObject::BP_ElectSphereBoom;
		break;
	case ESkillActor::BP_ElectTrap:
		PSO.SpawnObject = EObject::BP_ElectTrap;
		break;
	default:
		break;
	}
	PSO.Location.X = SpawnLocation.X;	PSO.Location.Y = SpawnLocation.Y;	PSO.Location.Z = SpawnLocation.Z;
	PSO.ForwardVec.X = ForwardVec.X;	PSO.ForwardVec.Y = ForwardVec.Y;	PSO.ForwardVec.Z = ForwardVec.Z;
	
	PSO.SerialNum = SerialNum;

	m_Socket->Send(&PSO, sizeof(PSO));
}

void AMainGameMode::SendAnimMontageStatus(ECharacterAnimMontage eAnimMontage)
{
	switch (eAnimMontage)
	{
	case ECharacterAnimMontage::ECAM_Default:
		break;
	case ECharacterAnimMontage::ECAM_DaggerAttack:
		break;
	case ECharacterAnimMontage::ECAM_KatanaAttack:
		break;
	case ECharacterAnimMontage::ECAM_GreatSwordAttack:
		break;
	case ECharacterAnimMontage::ECAM_SMG:
		break;
	case ECharacterAnimMontage::ECAM_Rifle:
		break;
	case ECharacterAnimMontage::ECAM_RPG:
		break;
	case ECharacterAnimMontage::ECAM_Stun:
		break;
	case ECharacterAnimMontage::ECAM_Down:
		break;
	case ECharacterAnimMontage::ECAM_Death:
		break;
	default:
		break;
	}
}

float AMainGameMode::CalculateDirection(const FVector& Velocity, const FRotator& BaseRotation)
{
	if (!Velocity.IsNearlyZero())
	{
		const FMatrix RotMatrix = FRotationMatrix(BaseRotation);
		const FVector ForwardVector = RotMatrix.GetScaledAxis(EAxis::X);
		const FVector RightVector = RotMatrix.GetScaledAxis(EAxis::Y);
		const FVector NormalizedVel = Velocity.GetSafeNormal2D();

		// get a cos(alpha) of forward vector vs velocity
		const float ForwardCosAngle = static_cast<float>(FVector::DotProduct(ForwardVector, NormalizedVel));
		// now get the alpha and convert to degree
		float ForwardDeltaDegree = FMath::RadiansToDegrees(FMath::Acos(ForwardCosAngle));

		// depending on where right vector is, flip it
		const float RightCosAngle = static_cast<float>(FVector::DotProduct(RightVector, NormalizedVel));
		if (RightCosAngle < 0.f)
		{
			ForwardDeltaDegree *= -1.f;
		}

		return ForwardDeltaDegree;
	}

	return 0.f;
}

void AMainGameMode::Test_TakeDamage(int DamageType)
{
	PDamagedPlayer* PDP = new PDamagedPlayer();
	PDP->ChangedPlayerSerial = SerialNum;
	switch (DamageType)
	{
	case 0:
		PDP->IsMelee = true;
		PDP->WeaponEnum = 0;
		break;
	case 1:
		PDP->IsMelee = true;
		PDP->WeaponEnum = 1;
		break;
	case 2:
		PDP->IsMelee = true;
		PDP->WeaponEnum = 2;
		break;
	case 3:
		PDP->IsMelee = false;
		PDP->WeaponEnum = 0;
		break;
	case 4:
		PDP->IsMelee = false;
		PDP->WeaponEnum = 1;
		break;
	case 5:
		PDP->IsMelee = false;
		PDP->WeaponEnum = 2;
		break;
	case 6:
	case 7:
	default:
		break;
	}

	//m_Socket->Send(PDP, sizeof(PDamagedPlayer));
	PushQueue(PDP);
}

void AMainGameMode::SpawnSkillActor_Implementation(ESkillActor SkillActor, FVector SpawnLocation, FVector ForwardVec, ASkyscraperCharacter* Spawner, FName Team) {}