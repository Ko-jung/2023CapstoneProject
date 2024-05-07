// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"

#include "SocketGameInstance.h"

#include "../MainGame/Actor/Character/SkyscraperCharacter.h"
#include "../MainGame/Component/Health/HealthComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/GameUserSettings.h"

// Montage Sync
#include "../MainGame/Component/Combat/CombatSystemComponent.h"
#include "Skyscraper/MainGame/Core/SkyscraperPlayerController.h"

// Processing Building Info From Server
#include "Skyscraper/MainGame/Map/HexagonTile/HexagonTile.h"
#include "Kismet/GameplayStatics.h"

void AMainGameMode::BeginPlay()
{
	GetHexagonTileOnLevel();

	// Get Socket Instance
	USocketGameInstance* instance = static_cast<USocketGameInstance*>(GetGameInstance());
	bIsConnected = instance->GetIsConnect();
	if (!bIsConnected)
	{
		// Super::BeginPlay();
		HexagonTile->Init();
		return;
	}
	PlayerSelectInfo = instance->GetSelectInfo();
	m_Socket = instance->GetSocket();
	SerialNum = instance->GetSerialNum();
	m_Socket->SetGamemode(this);
	m_Socket->StartListen();

	Super::BeginPlay();

	// Set FullScreen Mode
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	UGameUserSettings::GetGameUserSettings()->SetFullscreenMode(EWindowMode::WindowedFullscreen);
	UGameUserSettings::GetGameUserSettings()->ApplySettings(false);

	// Define Team Name
	TeamName[(int)ETEAM::A] = FName("TeamA");
	TeamName[(int)ETEAM::B] = FName("TeamB");

	Characters.Init(nullptr, MAXPLAYER);

	// Move to ProcessBuildingInfo
	/*for (int i = 0; i < PlayerSelectInfo.Num(); i++)
	{
		SpawnCharacter(i);
	}*/
	
	// For Get Building Info
	PRequestPacket PRP(COMP_OP::OP_BUILDINGINFO);
	m_Socket->Send(&PRP, PRP.PacketSize);
}

void AMainGameMode::Tick(float Deltatime)
{
	Super::Tick(Deltatime);

	if (!bIsConnected)
	{
		return;
	}

	ProcessFunc();
	SendPlayerSwapWeaponInfo();
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
		case (int)COMP_OP::OP_BUILDINGINFO:
		{
			PBuildingInfo PBI;
			memcpy(&PBI, packet, sizeof(PBI));
			ProcessBuildingInfo(&PBI);
			UE_LOG(LogTemp, Warning, TEXT("Recv COMP_OP::OP_BUILDINGINFO"));
			break;
		}
		case (BYTE)COMP_OP::OP_PLAYERPOSITION:
		{
			PPlayerPosition PPP;
			memcpy(&PPP, packet, sizeof(PPP));
			//if (PPP.PlayerSerial >= MAXPLAYER || PPP.PlayerSerial < 0)
			//{
			//	UE_LOG(LogClass, Warning, TEXT("COMP_OP::OP_PLAYERPOSITION Array Error"));
			//	continue;
			//}
			SetPlayerPosition(PPP);
			break;
		}
		case (BYTE)COMP_OP::OP_CHANGEDPLAYERHP:
		{
			PChangedPlayerHP* PCPHP = static_cast<PChangedPlayerHP*>(packet);
			if (Characters[PCPHP->ChangedPlayerSerial])
				Characters[PCPHP->ChangedPlayerSerial]->HealthComponent->ChangeCurrentHp(PCPHP->AfterHP);
			break;
		}
		case (BYTE)COMP_OP::OP_CHANGEDPLAYERSTATE:
		{
			PChangedPlayerState* PCPS = static_cast<PChangedPlayerState*>(packet);
			ProcessChangedCharacterState(PCPS);
			break;
		}
		//case (BYTE)COMP_OP::OP_DAMAGEDPLAYER:
		//{
		//	//PDamagedPlayer* PDP = static_cast<PDamagedPlayer*>(packet);
		//	//m_Socket->Send(PDP, sizeof(PDamagedPlayer));
		//	m_Socket->Send(packet, sizeof(PDamagedPlayer));
		//	break;
		//}
		case (BYTE)COMP_OP::OP_SPAWNOBJECT:
		{
			PSpawnObject PSO;
			memcpy(&PSO, packet, sizeof(PSO));

			// if (PSO.SerialNum>= MAXPLAYER || PSO.SerialNum < 0)
			// {
			// 	UE_LOG(LogClass, Warning, TEXT("Array Error"));
			// 	continue;
			// }

			ProcessSpawnObject(PSO);
			break;
		}
		case (BYTE)COMP_OP::OP_CHANGEANIMMONTAGE:
		{
			PChangeAnimMontage PCAM;
			memcpy(&PCAM, packet, sizeof(PCAM));
			if(Characters[PCAM.ChangedPlayerSerial])
				Characters[PCAM.ChangedPlayerSerial]->SetMontage(PCAM.eAnimMontage);
			break;
		}
		case (BYTE)COMP_OP::OP_SWAPWEAPON:
		{
			PSwapWeapon PSW;
			memcpy(&PSW, packet, sizeof(PSW));
			if (Characters[PSW.SwapingPlayer])
				Characters[PSW.SwapingPlayer]->SwapWeapon(PSW.SwapWeapon);
			UE_LOG(LogTemp, Warning, TEXT("Recv COMP_OP::OP_SWAPWEAPON"));
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

void AMainGameMode::SpawnCharacter(int TargetSerialNum)
{
	const auto& p = PlayerSelectInfo[TargetSerialNum];

	TSubclassOf<ASkyscraperCharacter>* Class = (TargetSerialNum == SerialNum) ?
		CharacterClass.Find(p->PickedCharacter) :
		AiCharacterClass.Find(p->PickedCharacter);

	// Check Null Character
	if (!Class)
	{
		UE_LOG(LogClass, Warning, TEXT("%d: Client Select Info Is NULLCHARACTER!"), TargetSerialNum);
		return;
	}

	// Set Team Tag and Spawn Location
	bool IsTeamA = TargetSerialNum < MAXPLAYER / 2;
	FName Team;
	FVector Location = HexagonTile->GetSpawnLocation(IsTeamA);
	FActorSpawnParameters spawnParams;

	if (IsTeamA)	Team = TeamName[(int)ETEAM::A];
	else			Team = TeamName[(int)ETEAM::B];
	//Location = SpawnLoction[(int)ETEAM::A];

	ASkyscraperCharacter* character = nullptr;
	while (true)
	{
		FVector SpawnLocation = FVector{FMath::RandRange(Location.X - 100.f, Location.X + 100.f),
										FMath::RandRange(Location.Y - 100.f, Location.Y + 100.f),
										Location.Z};
		character = GetWorld()->SpawnActor<ASkyscraperCharacter>(*Class, SpawnLocation, FRotator{}, spawnParams);

		if (!character) continue;

		character->Tags.Add(Team);
		break;
	}

	if (TargetSerialNum == SerialNum)
	{
		GetWorld()->GetFirstPlayerController()->Possess(character);
		character->AddInputMappingContext();
	}
	else
	{
		ASkyscraperPlayerController* controller =
			GetWorld()->SpawnActor<ASkyscraperPlayerController>(ASkyscraperPlayerController::StaticClass(), FVector(), FRotator());
		controller->Possess(character);
	}

	// Set Weapon
	character->CombatSystemComponent->SetInitialSelect(PlayerSelectInfo[TargetSerialNum]->PickedMeleeWeapon, PlayerSelectInfo[TargetSerialNum]->PickedRangeWeapon);

	Characters[TargetSerialNum] = character;
}

void AMainGameMode::SetPlayerPosition(PPlayerPosition PlayerPosition)
{
	int32 Serial = PlayerPosition.PlayerSerial;
	FVector Location{ PlayerPosition.Location.X, PlayerPosition.Location.Y, PlayerPosition.Location.Z };
	FRotator Rotate{ PlayerPosition.Rotate.X, PlayerPosition.Rotate.Y, PlayerPosition.Rotate.Z };
	// EPlayerState state = PlayerPosition.PlayerState;
	// EnumPlayerState ArguState;

	FTransform transform{ Rotate, Location, FVector(1.f,1.f,1.f) };

	float speed = PlayerPosition.PlayerSpeed;
	float XRotate = PlayerPosition.PlayerXDirection;

	if(Characters[Serial])
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
	if (PSO.SerialNum < MAXPLAYER / 2)	Team = TeamName[(int)ETEAM::A];
	else								Team = TeamName[(int)ETEAM::B];

	FVector Location{ PSO.Location.X, PSO.Location.Y, PSO.Location.Z };
	FVector Forward{ PSO.ForwardVec.X, PSO.ForwardVec.Y, PSO.ForwardVec.Z };
	ESkillActor SkillActor = PSO.SpawnObject;

	SpawnSkillActor(SkillActor, Location, Forward, Characters[PSO.SerialNum], Team);
}

void AMainGameMode::ProcessChangedCharacterState(PChangedPlayerState* PCPS)
{
	if (!Characters[PCPS->ChangedPlayerSerial]) return;

	if (PCPS->State == EHealthState::EHS_DEAD)
	{
		// Add Kill Count
		if (PCPS->ChangedPlayerSerial < MAXPLAYER / 2)	++KillCount[(int)ETEAM::A];
		else											++KillCount[(int)ETEAM::B];

		if (PCPS->ChangedPlayerSerial == SerialNum)
		{
			// Disable Input

		}
	}
	else if (PCPS->State == EHealthState::EHS_INVINCIBILITY)
	{
		// Destroy Character
		if (Characters[PCPS->ChangedPlayerSerial])
		{
			Characters[PCPS->ChangedPlayerSerial]->Destroy();
		}

		// ReSpawn and On INVINCIBILITY
		SpawnCharacter(PCPS->ChangedPlayerSerial);
	}
	//else if (PCPS->State == EHealthState::EHS_LIVING)
	//{
	//	// Off INVINCIBILITY

	//}

	Characters[PCPS->ChangedPlayerSerial]->HealthComponent->ChangeState(PCPS->State);
}

void AMainGameMode::ProcessBuildingInfo(PBuildingInfo* PBI)
{
	HexagonTile->InitialSettings(PBI->BuildInfo);

	for (int i = 0; i < PlayerSelectInfo.Num(); i++)
	{
		SpawnCharacter(i);
	}
}

void AMainGameMode::GetHexagonTileOnLevel()
{
	TArray<AActor*> HexagonTiles;
	UGameplayStatics::GetAllActorsOfClass(this, AHexagonTile::StaticClass(), HexagonTiles);

	for (auto& h : HexagonTiles)
	{
		AHexagonTile* Hexagon = Cast<AHexagonTile>(h);
		if (!Hexagon)
		{
			UE_LOG(LogClass, Warning, TEXT("AHexagonTIle Cast FAILED!"));
			break;
		}

		HexagonTile = Hexagon;
		break;
	}
}

void AMainGameMode::SendPlayerLocation()
{
	if (!Characters[SerialNum]) return;

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

void AMainGameMode::SendPlayerSwapWeaponInfo()
{
	ASkyscraperCharacter* PossessCharacter = Characters[SerialNum];

	ESwapWeapon WeaponType;
	uint8 EquippedWeapon;

	if (PossessCharacter && PossessCharacter->CheckHoldWeapon(WeaponType, EquippedWeapon))
	{
		PSwapWeapon PSW(SerialNum, WeaponType);
		m_Socket->Send(&PSW, sizeof(PSW));

		UE_LOG(LogClass, Warning, TEXT("Sending Swap Weapon!"));
	}
}

void AMainGameMode::SendSkillActorSpawn(ESkillActor SkillActor, FVector SpawnLocation, FVector ForwardVec)
{
	PSpawnObject PSO;

	PSO.SpawnObject = SkillActor;
	PSO.Location.X = SpawnLocation.X;	PSO.Location.Y = SpawnLocation.Y;	PSO.Location.Z = SpawnLocation.Z;
	PSO.ForwardVec.X = ForwardVec.X;	PSO.ForwardVec.Y = ForwardVec.Y;	PSO.ForwardVec.Z = ForwardVec.Z;
	
	PSO.SerialNum = SerialNum;

	m_Socket->Send(&PSO, sizeof(PSO));
}

void AMainGameMode::SendAnimMontageStatus(const AActor* Sender, ECharacterAnimMontage eAnimMontage)
{
	if (!bIsConnected)
		return;

	if (Sender != Characters[SerialNum])
		return;

	UE_LOG(LogClass, Warning, TEXT("Sending Anim Motage Status"));

	PChangeAnimMontage PCAM;

	PCAM.ChangedPlayerSerial = SerialNum;
	PCAM.eAnimMontage = eAnimMontage;

	Send(&PCAM, sizeof(PCAM));
}

void AMainGameMode::SendTakeDamage(AActor* Sender, AActor* Target)
{
	if (Sender != Characters[SerialNum])
	{
		UE_LOG(LogClass, Warning, TEXT("SendTakeDamage Sender != Characters[SerialNum]"));
		return;
	}

	int i = 0;
	{ // Find Target Id
		for (const auto& c : Characters)
		{
			if (c == Target) break;
			i++;
		}
		// Can't Find
		if (i >= MAXPLAYER)
		{
			UE_LOG(LogClass, Warning, TEXT("AMainGameMode::SendTakeDamage Cant find Target Actor ID"));
			return;
		}
	}

	ESwapWeapon weaponType;
	uint8 equippedWeapon;
	Characters[SerialNum]->CheckHoldWeapon(weaponType, equippedWeapon);

	PDamagedPlayer PDP;
	PDP.ChangedPlayerSerial = i;
	PDP.IsMelee = ((weaponType == ESwapWeapon::MeleeWeapon) ? true : false);
	PDP.WeaponEnum = equippedWeapon;

	m_Socket->Send(&PDP, sizeof(PDP));
	UE_LOG(LogClass, Warning, TEXT("Send Weapon Damage"));
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

	m_Socket->Send(PDP, sizeof(PDamagedPlayer));
	//PushQueue(PDP);
}

void AMainGameMode::SpawnSkillActor_Implementation(ESkillActor SkillActor, FVector SpawnLocation, FVector ForwardVec, ASkyscraperCharacter* Spawner, FName Team) {}