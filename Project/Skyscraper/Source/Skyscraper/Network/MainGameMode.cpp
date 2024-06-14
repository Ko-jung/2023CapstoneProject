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
#include "Skyscraper/MainGame/Core/AISkyscraperController.h"

// Processing Building Info From Server
#include "Skyscraper/MainGame/Map/HexagonTile/HexagonTile.h"
#include "Kismet/GameplayStatics.h"

// Setting Game UI On Controller
#include "../MainGame/Core/SkyscraperPlayerController.h"
#include "Skyscraper/MainGame/Widget/TimeAndKillCount/TimeAndKillCountWidget.h"

// Input mode
#include "Blueprint/WidgetBlueprintLibrary.h"

// Minimap
#include "Skyscraper/MainGame/Widget/MiniMap/MiniMapWidget.h"

// Windows Array
#include "EngineUtils.h"
#include "Components/StaticMeshComponent.h"
#include "Skyscraper/MainGame/Map/Building/SingleBuildingFloor.h"

void AMainGameMode::BeginPlay()
{
	UE_LOG(LogClass, Warning, TEXT("Called AMainGameMode::BeginPlay()"));

	GetHexagonTileOnLevel();

	// Get Socket Instance
	USocketGameInstance* instance = static_cast<USocketGameInstance*>(GetGameInstance());
	bIsConnected = instance->GetIsConnect();
	if (!bIsConnected)
	{
		// Super::BeginPlay();
		HexagonTile->Init();
		GetWindowsOnLevel();
		return;
	}
	PlayerSelectInfo = instance->GetSelectInfo();
	m_Socket = instance->GetSocket();
	SerialNum = instance->GetSerialNum();
	m_Socket->SetGamemode(this);
	m_Socket->StartListen();

	Super::BeginPlay();

	// Set FullScreen Mode
	PlayerController = Cast<ASkyscraperPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController)
	{
		PlayerController->SetShowMouseCursor(false);
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
	}
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
	// For Get Building Info
	PRequestPacket PRP2(COMP_OP::OP_SETTIMER);
	m_Socket->Send(&PRP2, PRP2.PacketSize);

	TileDropTimer = 0.f;
	TileDropLevel = 0;

	UE_LOG(LogClass, Warning, TEXT("End Called AMainGameMode::BeginPlay()"));
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

	UpdateUI(Deltatime);
}

void AMainGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AMainGameMode::ProcessFunc()
{
	UE_LOG(LogClass, Warning, TEXT("Called AMainGameMode::ProcessFunc()"));
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
			GetWindowsOnLevel();
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
				Characters[PCAM.ChangedPlayerSerial]->SetMontage(PCAM.eAnimMontage, PCAM.SectionNum);
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
		case (BYTE)COMP_OP::OP_STUNDOWNSTATE:
		{
			PStunDownState PSDS;
			memcpy(&PSDS, packet, sizeof(PSDS));
			if (Characters[PSDS.TargetSerialNum])
			{
				FVector Dirction{ PSDS.Direction.X, PSDS.Direction.Y, PSDS.Direction.Z };
				if (PSDS.IsStun)
				{
					Characters[PSDS.TargetSerialNum]->ApplyStun(PSDS.StunTime, Dirction);
				}
				else
				{
					Characters[PSDS.TargetSerialNum]->ApplyDown(Dirction);
				}
			}
			break;
		}		
		case (BYTE)COMP_OP::OP_SETTIMER:
		{
			PSetTimer PST;
			memcpy(&PST, packet, sizeof(PST));
			switch (PST.TimerType)
			{
			case ETimer::TileDropTimer:
			{
				TileDropTimer = PST.SecondsUntilActivation;
				break;
			}
			default:
				break;
			}
			break;
		}
		case (BYTE)COMP_OP::OP_TILEDROP:
		{
			PTileDrop PTD;
			memcpy(&PTD, packet, sizeof(PTD));
			ProcessTileDrop(PTD);
			if(++TileDropLevel >= 4) TileDropLevel = 4;
			break;
		}
		case (BYTE)COMP_OP::OP_SPAWNITEM:
		{
			PSpawnItem PSI;
			memcpy(&PSI, packet, sizeof(PSI));
			ProcessSpawnItem(PSI);
			break;
		}
		case (BYTE)COMP_OP::OP_USEITEM:
		{
			PUseItem PUI;
			memcpy(&PUI, packet, sizeof(PUI));
			ProcessUseItem(PUI);
			break;
		}
		case (BYTE)COMP_OP::OP_GETITEM:
		{
			PGetItem PGI;
			memcpy(&PGI, packet, sizeof(PGI));
			ProcessGetItem(PGI);
			break;
		}
		case (BYTE)COMP_OP::OP_FINISHGAME:
		{
			PFinishGame PFG;
			memcpy(&PFG, packet, sizeof(PFG));
			ASkyscraperPlayerController* controller = Cast<ASkyscraperPlayerController>(GetWorld()->GetFirstPlayerController());
			if (controller)
			{
				FText Result;
				if (PFG.IsTeamAWin)
					Result = FText::FromString(L"Win A Team");
				else
					Result = FText::FromString(L"Win B Team");

				controller->AddGameResultWidget(Result);
			}
			break;
		}
		case (BYTE)COMP_OP::OP_BREAKOBJECT:
		{
			PBreakObject PBO;
			memcpy(&PBO, packet, sizeof(PBO));
			ProcessBreakObject(PBO);
			break;
		}
		default:
			UE_LOG(LogTemp, Warning, TEXT("AMainGameMode::ProcessFunc() switch Default"));
			break;
		}
		delete packet;
	}
	UE_LOG(LogClass, Warning, TEXT("End Called AMainGameMode::ProcessFunc()"));
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

void AMainGameMode::GoToLobby()
{

	UGameplayStatics::OpenLevel(GetWorld(), FName("LobbyLevel"));
}

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
		APlayerController* controller = GetWorld()->GetFirstPlayerController();
		controller->Possess(character);

		ASkyscraperPlayerController* SkyController = Cast<ASkyscraperPlayerController>(controller);
		SkyController->SetPossessingPawn();

		character->AddInputMappingContext();
	}
	else
	{
		AAISkyscraperController* controller =
			GetWorld()->SpawnActor<AAISkyscraperController>(AAISkyscraperController::StaticClass(), FVector(), FRotator());
		controller->Possess(character);
	}

	// Set Weapon
	character->CombatSystemComponent->SetInitialSelect(PlayerSelectInfo[TargetSerialNum]->PickedMeleeWeapon, PlayerSelectInfo[TargetSerialNum]->PickedRangeWeapon);

	Characters[TargetSerialNum] = character;
}

void AMainGameMode::UpdateUI(float Deltatime)
{
	if (TileDropTimer > 0.f)
		TileDropTimer -= Deltatime;
	if (PlayerController)
	{
		PlayerController->GetTimeAndKillCountWidget()->SetTimeText(	((int)TileDropTimer) / 60,
																	((int)TileDropTimer) % 60);
		PlayerController->GetTimeAndKillCountWidget()->SetCollapseLevelText(TileDropLevel + 1);
		if (SerialNum < MAXPLAYER / 2)
		{
			PlayerController->GetTimeAndKillCountWidget()->SetFriendlyKillCountText(KillCount[(int)ETEAM::A]);
			PlayerController->GetTimeAndKillCountWidget()->SetEnemyKillCountText(KillCount[(int)ETEAM::B]);
		}
		else
		{
			PlayerController->GetTimeAndKillCountWidget()->SetFriendlyKillCountText(KillCount[(int)ETEAM::B]);
			PlayerController->GetTimeAndKillCountWidget()->SetEnemyKillCountText(KillCount[(int)ETEAM::A]);
		}
	}
	else
	{
		PlayerController = Cast<ASkyscraperPlayerController>(GetWorld()->GetFirstPlayerController());
	}
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
		if (PCPS->ChangedPlayerSerial < MAXPLAYER / 2)	++KillCount[(int)ETEAM::B];
		else											++KillCount[(int)ETEAM::A];

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
	HexagonTile->InitialSettings(PBI->BuildInfo, PBI->BuildInfoSize);

	for (int i = 0; i < PlayerSelectInfo.Num(); i++)
	{
		SpawnCharacter(i);
	}

	PlayerController->UpdateImage();
}

void AMainGameMode::ProcessTileDrop(PTileDrop PTD)
{ 
	if (PTD.TileDropLevel < 3)
	{
		HexagonTile->CollapseTilesAndActors(PTD.TileDropLevel, PTD.CenterIndex);
	}
	else
	{
		HexagonTile->CollapseLevel3(PTD.CenterIndex);
	}
}

void AMainGameMode::ProcessSpawnItem(PSpawnItem PSI)
{
	HexagonTile->SpawnItem(PSI.Item, PSI.SpawnCount);
	
	for (int i = 0; i < PSI.SpawnCount; i++)
	{
		PlayerController->GetMiniMapWidget()->SetTileImage(PSI.Item[i].TileIndex, ETileImageType::ETIT_Item);
	}
}

void AMainGameMode::ProcessUseItem(PUseItem PUI)
{
	//Characters[PUI.UsePlayerSerial];
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("{0} Character Use ITEM!"), (int)PUI.UsePlayerSerial));
}

void AMainGameMode::ProcessGetItem(PGetItem PGI)
{
	HexagonTile->RemoveItem(PGI.ItemSerialNum);

	//PlayerController->UpdateImage(PGI.)
}

void AMainGameMode::ProcessBreakObject(PBreakObject PBO)
{
	// Find Windows using LOCATION
	//FVector ObjectLocation{ PBO.ObjectLocation.X, PBO.ObjectLocation.Y,PBO.ObjectLocation.Z };
	UStaticMeshComponent* TargetObject = WindowMeshComponents[PBO.ObjectSerial];

	if (!TargetObject)
	{
		UE_LOG(LogClass, Warning, TEXT("TargetObject is NULL"));
		return;
	}

	UE_LOG(LogClass, Warning, TEXT("TargetObject is %s"), *TargetObject->GetStaticMesh()->GetName());

	// Break Window 
	ASingleBuildingFloor* SBFloor = Cast<ASingleBuildingFloor>(TargetObject->GetOwner());
	if (!SBFloor)
	{
		UE_LOG(LogClass, Warning, TEXT("SBFloor is nullptr"));
		return;
	}

	SBFloor->DoCollapseWindow(TargetObject, FVector{ PBO.Direction.X, PBO.Direction.Y, PBO.Direction.Z });
	//TargetObject->DestroyComponent();
}

void AMainGameMode::GetHexagonTileOnLevel()
{
	AHexagonTile* Hexagon = Cast<AHexagonTile>(UGameplayStatics::GetActorOfClass(this, AHexagonTile::StaticClass()));
	if (!Hexagon)
	{
		UE_LOG(LogClass, Warning, TEXT("AMainGameMode::GetHexagonTileOnLevel() AHexagonTIle Cast FAILED!"));
		return;
	}

	HexagonTile = Hexagon;
}

void AMainGameMode::GetWindowsOnLevel()
{
	for (TActorIterator<ASingleBuildingFloor> It(GetWorld()); It; ++It)
	{
		ASingleBuildingFloor* SingleBuildingFloor = *It;

		TArray<UStaticMeshComponent*> MeshComponents;
		SingleBuildingFloor->GetComponents<UStaticMeshComponent>(MeshComponents);

		// Find Window
		for (UStaticMeshComponent* MeshComponent : MeshComponents)
		{
			if (MeshComponent && MeshComponent->GetStaticMesh()->GetName().StartsWith("map_3_window"))
			{
				WindowMeshComponents.Add(MeshComponent);
			}
		}
	}
}

int AMainGameMode::GetWindowsIndex(const UPrimitiveComponent* Target)
{
	for (int i = 0; i < WindowMeshComponents.Num(); i++)
	{
		if (WindowMeshComponents[i] == Target)
			return i;
	}
	return -1;
}

//UStaticMeshComponent* AMainGameMode::GetStaticMeshComponentByLocation(FVector Location, EBreakType BreakType)
//{
//	switch (BreakType)
//	{
//	case EBreakType::Window:
//	{
//		for (UStaticMeshComponent* StaticMeshComponent : WindowMeshComponents)
//		{
//			FVector ComponentLocation = StaticMeshComponent->GetComponentLocation();
//			if (FVector::Dist(Location, ComponentLocation) < 25.f)
//			{
//				return StaticMeshComponent;
//			}
//		}
//		break;
//	}
//	default:
//		return nullptr;
//	}
//	return nullptr;
//}

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

void AMainGameMode::SendAnimMontageStatus(const AActor* Sender, ECharacterAnimMontage eAnimMontage, int Section)
{
	if (!bIsConnected)
		return;

	if (Sender != Characters[SerialNum])
		return;

	UE_LOG(LogClass, Warning, TEXT("Sending Anim Motage Status"));

	PChangeAnimMontage PCAM;

	PCAM.ChangedPlayerSerial = SerialNum;
	PCAM.eAnimMontage = eAnimMontage;
	PCAM.SectionNum = Section;

	Send(&PCAM, sizeof(PCAM));
}

bool AMainGameMode::SendTakeDamage(AActor* Sender, AActor* Target)
{

	if (!m_Socket || Sender != Characters[SerialNum])
	{
		UE_LOG(LogClass, Warning, TEXT("SendTakeDamage Sender != Characters[SerialNum]"));
		return false;
	}

	int i = GetIndex(Target);
	if (i == -1) return false;

	ESwapWeapon weaponType;
	uint8 equippedWeapon;
	Characters[SerialNum]->CheckHoldWeapon(weaponType, equippedWeapon);

	PDamagedPlayer PDP;
	PDP.ChangedPlayerSerial = i;
	PDP.IsMelee = ((weaponType == ESwapWeapon::MeleeWeapon) ? true : false);
	PDP.WeaponEnum = equippedWeapon;

	m_Socket->Send(&PDP, sizeof(PDP));
	UE_LOG(LogClass, Warning, TEXT("Send Weapon Damage"));
	return true;
}

void AMainGameMode::SendStunDown(const AActor* Attacker, const AActor* Target, const FVector& Dirction, bool IsStun, float StunTime)
{
	int TargetSerialNum = GetIndex(Target);
	if (TargetSerialNum == -1) return;

	if (!m_Socket || Characters.IsEmpty() || Attacker != Characters[SerialNum]) return;

	PStunDownState PSDS{ (BYTE)TargetSerialNum, Dirction, StunTime, IsStun };
	m_Socket->Send(&PSDS, sizeof(PSDS));
}

void AMainGameMode::SendUseItem(const AActor* Sender, uint8 Effect, uint8 RareLevel)
{
	if (!m_Socket || Characters.IsEmpty() || Sender != Characters[SerialNum]) return;

	PUseItem PUI(SerialNum, (BYTE)Effect, (BYTE)RareLevel);
	m_Socket->Send(&PUI, sizeof(PUI));
}

void AMainGameMode::SendGetItem(const AActor* Sender, const AActor* Item)
{
	if (!m_Socket || Characters.IsEmpty() || Sender != Characters[SerialNum]) return;

	PGetItem PGI(HexagonTile->FindItemSerialNum(Item));
	m_Socket->Send(&PGI, sizeof(PGI));
}
   
void AMainGameMode::SendBreakObject(const AActor* Sender, const UPrimitiveComponent* BreakTarget, EBreakType BreakType)
{
	FVector Direction = (BreakTarget->GetComponentLocation() - Sender->GetActorLocation()).GetSafeNormal();

	if (!m_Socket)
	{
		PBreakObject PBO;
		int WindowIndex = GetWindowsIndex(BreakTarget);
		PBO.ObjectType = BreakType;
		PBO.ObjectSerial = WindowIndex;
		PBO.Direction = Direction;
		ProcessBreakObject(PBO);
		return;
	}

	if (Characters.IsEmpty() || Sender != Characters[SerialNum]) return;

	int WindowIndex = GetWindowsIndex(BreakTarget);
	PBreakObject PBO(BreakType, WindowIndex, Direction);
	m_Socket->Send(&PBO, sizeof(PBO));
}

int AMainGameMode::GetIndex(const AActor* target)
{
	int Index = 0;
	for (const auto& c : Characters)
	{
		if (c == target) break;
		Index++;
	}
	// Can't Find
	if (Index >= MAXPLAYER)
	{
		UE_LOG(LogClass, Warning, TEXT("AMainGameMode::GetIndex Cant find Target Actor ID"));
		return -1;
	}

	return Index;
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

void AMainGameMode::RequestTileDrop()
{
	PRequestPacket PRP(COMP_OP::OP_TILEDROP);
	m_Socket->Send(&PRP, sizeof(PRP));
}

void AMainGameMode::RequestSpawnItem()
{
	PRequestPacket PRP(COMP_OP::OP_SPAWNITEM);
	m_Socket->Send(&PRP, sizeof(PRP));
}

void AMainGameMode::RequestFinishGame()
{
	PRequestPacket PRP(COMP_OP::OP_FINISHGAME);
	m_Socket->Send(&PRP, sizeof(PRP));
}

void AMainGameMode::SpawnSkillActor_Implementation(ESkillActor SkillActor, FVector SpawnLocation, FVector ForwardVec, ASkyscraperCharacter* Spawner, FName Team) {}