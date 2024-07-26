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
#include "Components/HierarchicalInstancedStaticMeshComponent.h"

// Item Object
#include "Skyscraper/MainGame/Item/ItemFactory/ItemFactory.h"
#include "Skyscraper/MainGame/Item/ItemObject/ItemObject.h"
#include "Skyscraper/MainGame/Map/Furniture/Furniture.h"

void AMainGameMode::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("Called AMainGameMode::BeginPlay()"));

	SkillActorSerialNum = 0;

	GetHexagonTileOnLevel();

	Super::BeginPlay();

	// Get Socket Instance
	USocketGameInstance* instance = static_cast<USocketGameInstance*>(GetGameInstance());
	if (!instance->GetIsConnect())
	{
		// Super::BeginPlay();
		m_Socket->InitializeManager();
		HexagonTile->Init();
		GetWindowsOnLevel();
		return;
	}
	PlayerSelectInfo = instance->GetSelectInfo();
	m_Socket = instance->GetSocket();
	SerialNum = instance->GetSerialNum();
	m_Socket->SetGamemode(this);
	m_Socket->StartListen();

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

	Characters.Init(nullptr, PlayerSelectInfo.Num());

	// Move to ProcessBuildingInfo
	/*for (int i = 0; i < PlayerSelectInfo.Num(); i++)
	{
		SpawnCharacter(i);
	}*/
	
	// For Get Building Info
	PRequestPacket PRP(COMP_OP::OP_BUILDINGINFO);
	m_Socket->Send(&PRP, PRP.PacketSize);

	PRequestPacket PRP2(COMP_OP::OP_SETTIMER);
	m_Socket->Send(&PRP2, PRP2.PacketSize);

	TileDropTimer = 0.f;
	TileDropLevel = 0;

	UE_LOG(LogTemp, Warning, TEXT("End Called AMainGameMode::BeginPlay()"));
}

void AMainGameMode::Tick(float Deltatime)
{
	Super::Tick(Deltatime);

	if (!GetIsConnected())
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
	//UE_LOG(LogTemp, Warning, TEXT("Called AMainGameMode::ProcessFunc()"));
	Packet* packet;
	while (FuncQueue.try_pop(packet))
	{
		switch (packet->PacketType)
		{
		case (BYTE)COMP_OP::OP_BUILDINGINFO:
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
			//	UE_LOG(LogTemp, Warning, TEXT("COMP_OP::OP_PLAYERPOSITION Array Error"));
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
		case (BYTE)COMP_OP::OP_CHANGEDSKILLACTORHP:
		{
			PChangedSkillActorHP* PCHP = static_cast<PChangedSkillActorHP*>(packet);
			uint8 TargetOwner = PCHP->ChangedSkillActorOwner;
			if (Characters.IsValidIndex(TargetOwner) && Characters[TargetOwner])
			{
				Characters[TargetOwner]->SkillActorDamaged(PCHP->AfterHP);
			}
			break;
		}
		case (BYTE)COMP_OP::OP_CHANGEDPLAYERSTATE:
		{
			ProcessChangedCharacterState(static_cast<PChangedPlayerState*>(packet));
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
			ProcessSpawnObject(PSO);
			break;
		}
		case (BYTE)COMP_OP::OP_CHANGEANIMMONTAGE:
		{
			PChangeAnimMontage PCAM;
			memcpy(&PCAM, packet, sizeof(PCAM));
			if(Characters.IsValidIndex(PCAM.ChangedPlayerSerial) && Characters[PCAM.ChangedPlayerSerial])
				Characters[PCAM.ChangedPlayerSerial]->SetMontage(PCAM.eAnimMontage, PCAM.SectionNum);
			break;
		}
		case (BYTE)COMP_OP::OP_SWAPWEAPON:
		{
			PSwapWeapon PSW;
			memcpy(&PSW, packet, sizeof(PSW));
			if (Characters.IsValidIndex(PSW.SwapingPlayer) && Characters[PSW.SwapingPlayer])
			{
				Characters[PSW.SwapingPlayer]->SwapWeapon(PSW.SwapWeapon);
				UE_LOG(LogTemp, Warning, TEXT("Recv COMP_OP::OP_SWAPWEAPON Changer is %s"), *UKismetSystemLibrary::GetDisplayName(Characters[PSW.SwapingPlayer]));
			}
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
				bool IsTeamA = SerialNum < MAXPLAYER / 2;
				controller->AddGameResultWidget(PFG.IsTeamAWin == IsTeamA);
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
		case (BYTE)COMP_OP::OP_REMOVEOBJECT:
		{
			PRemoveObject PRO;
			memcpy(&PRO, packet, sizeof(PRO));
			ProcessRemoveObject(PRO);
			break;
		}
		case (BYTE)COMP_OP::OP_SKILLINTERACT:
		{
			UE_LOG(LogTemp, Warning, TEXT("COMP_OP::OP_DETECTING"));
			PSkillInteract PKI;
			memcpy(&PKI, packet, sizeof(PKI));
			ProcessSkillInteract(PKI);
			break;
		}
		default:
			UE_LOG(LogTemp, Warning, TEXT("AMainGameMode::ProcessFunc() switch Default. Type Is %d"), packet->PacketType);
			break;
		}
		delete packet;
	}
	//UE_LOG(LogTemp, Warning, TEXT("End Called AMainGameMode::ProcessFunc()"));
}

void AMainGameMode::GoToLobby()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("LobbyLevel"));
}

void AMainGameMode::SpawnCharacter(int TargetSerialNum)
{
	if (!PlayerSelectInfo.IsValidIndex(TargetSerialNum)/* || !Characters.IsValidIndex(TargetSerialNum)*/) return;

	const auto& p = PlayerSelectInfo[TargetSerialNum];

	TSubclassOf<ASkyscraperCharacter>* Class = (TargetSerialNum == SerialNum) ?
		CharacterClass.Find((ECharacterSelect)p->PickedCharacter) :
		AiCharacterClass.Find((ECharacterSelect)p->PickedCharacter);

	// Check Null Character
	if (!Class)
	{
		UE_LOG(LogTemp, Warning, TEXT("%d: Client Select Info Is NULLCHARACTER!"), TargetSerialNum);
		return;
	}

	// Set Team Tag and Spawn Location
	bool IsTeamA = TargetSerialNum < MAXPLAYER / 2;
	FName Team;
	FVector Location = HexagonTile->GetSpawnLocation(IsTeamA);

	if (IsTeamA)	Team = TeamName[(int)ETEAM::A];
	else			Team = TeamName[(int)ETEAM::B];
	//Location = SpawnLoction[(int)ETEAM::A];

	ASkyscraperCharacter* character = nullptr;
	while (true)
	{
		FVector SpawnLocation = FVector{FMath::RandRange(Location.X - 300.f, Location.X + 300.f),
										FMath::RandRange(Location.Y - 300.f, Location.Y + 300.f),
										Location.Z};
		FTransform Transform = { FRotator{} , SpawnLocation };

		character = GetWorld()->SpawnActorDeferred<ASkyscraperCharacter>(*Class, Transform);
		if (character)
		{
			if (TargetSerialNum == SerialNum)
			{
				APlayerController* controller = GetWorld()->GetFirstPlayerController();
				if (IsValid(controller->GetPawn()))
				{
					UE_LOG(LogTemp, Warning, TEXT("AMainGameMode::SpawnCharacter %s is Destory!"), *UKismetSystemLibrary::GetDisplayName(controller->GetPawn()));
					controller->GetPawn()->Destroy();
				}
				controller->Possess(character);
				character->FinishSpawning(Transform);
				if (character->IsValidLowLevel())
				{
					ASkyscraperPlayerController* SkyController = Cast<ASkyscraperPlayerController>(controller);
					SkyController->SetPossessingPawn();
					SkyController->AddAllWidget();
					character->AddInputMappingContext();
				}
				else
				{
					character->Destroy();
					continue;
				}
			}
			else
			{
				AAISkyscraperController* controller =
					GetWorld()->SpawnActor<AAISkyscraperController>(AAISkyscraperController::StaticClass(), FVector(), FRotator());
				controller->Possess(character);
				character->FinishSpawning(Transform);
				if (!character->IsValidLowLevel())
				{
					character->Destroy();
					continue;
				}
			}

			character->Tags.Add(Team);

			{	// Post processing
				bool IsEnemy = (SerialNum / (MAXPLAYER / 2)) != (TargetSerialNum / (MAXPLAYER / 2));

				// Allience : 0, Enemy : 1
				character->GetMesh()->CustomDepthStencilValue = IsEnemy;
				// Allience : true, Enemy : false
				character->GetMesh()->bRenderCustomDepth = !IsEnemy;
			}
			break;
		}
	}

	// Set Weapon
		
	// Process Weapon Null
	if (p->PickedMeleeWeapon == EMeleeSelect::EMS_NONE)
	{
		p->PickedMeleeWeapon = (EMeleeSelect)FMath::RandRange((uint8)EMeleeSelect::EMS_Dagger, (uint8)EMeleeSelect::EMS_GreatSword);
	}
	if (p->PickedRangeWeapon == ERangeSelect::ERS_NONE)
	{
		p->PickedRangeWeapon = (ERangeSelect)FMath::RandRange((uint8)ERangeSelect::ERS_SMG, (uint8)ERangeSelect::ERS_RPG);
	}

	character->CombatSystemComponent->SetInitialSelect(p->PickedMeleeWeapon, p->PickedRangeWeapon);

	Characters[TargetSerialNum] = character;


	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	ASkyscraperPlayerController* SkyController = Cast<ASkyscraperPlayerController>(controller);
	if (SkyController)
	{
		SkyController->SetPlayerImage(MAXPLAYER, Characters, SerialNum);
	}
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
	//float XRotate = PlayerPosition.PlayerXDirection;
	FRotator ControllerRotator = { PlayerPosition.ControllerRotator.X,PlayerPosition.ControllerRotator.Y ,PlayerPosition.ControllerRotator.Z};

	if(Characters[Serial])
		Characters[Serial]->SyncTransformAndAnim(transform, speed, ControllerRotator);
}

void AMainGameMode::ProcessSpawnObject(PSpawnObject PSO)
{
	AActor* NewActor;
	bool IsSpecial{ true };
	if (PSO.SpawnObject == ESkillActor::BP_ElectTrap || PSO.SpawnObject == ESkillActor::BP_DetectorMine)
	{
		IsSpecial = false;
	}
	Characters[PSO.ObjectSpawner]->SkillActorSpawnUsingPacket(IsSpecial,
																FVector{PSO.Location.X,PSO.Location. Y,PSO.Location. Z},
																FVector{ PSO.ForwardVec.X,PSO.ForwardVec.Y,PSO.ForwardVec.Z },
																NewActor);

	SkillActors.Add({ PSO.SerialNum, NewActor });
	UE_LOG(LogTemp, Warning, TEXT("SkillActors.Add pair{%d, %s}"), PSO.SerialNum, *UKismetSystemLibrary::GetDisplayName(NewActor));

	 //if (PSO.SerialNum == SerialNum)
	 //{
	 //	UE_LOG(LogTemp, Warning, TEXT("Skill Actor Spawner Is this!"));
	 //	return;
	 //}
	 //
	 //FName Team;
	 //if (PSO.SerialNum < MAXPLAYER / 2)	Team = TeamName[(int)ETEAM::A];
	 //else								Team = TeamName[(int)ETEAM::B];
	 //
	 //FVector Location{ PSO.Location.X, PSO.Location.Y, PSO.Location.Z };
	 //FVector Forward{ PSO.ForwardVec.X, PSO.ForwardVec.Y, PSO.ForwardVec.Z };
	 //ESkillActor SkillActor = PSO.SpawnObject;
	 //
	 //SpawnSkillActor(SkillActor, Location, Forward, Characters[PSO.SerialNum], Team);
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
		PlayerController->RemoveChangeWeaponWidget();
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
	PlayerController->SetPlayerImage(MAXPLAYER, Characters, SerialNum);
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
	if (!Characters.IsValidIndex(PUI.UsePlayerSerial)) return;

	//Characters[PUI.UsePlayerSerial];
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("{0} Character Use ITEM!"), (int)PUI.UsePlayerSerial));
	UE_LOG(LogTemp, Warning, TEXT("%d Character Use Item!"), (int)PUI.UsePlayerSerial);

	bool IsSameTeam = (SerialNum / (MAXPLAYER / 2)) == (PUI.UsePlayerSerial / (MAXPLAYER / 2));
	ASkyscraperCharacter* TargetCharacter = Characters[PUI.UsePlayerSerial];

	if (!TargetCharacter) return;
	
	if (PUI.Effect == (BYTE)EItemEffect::EIE_Tile_Break)
	{
		ProcessTileBreakItem(PUI.ItemLevel);
	}
	else if (UItemObject* Object = UItemFactory::CreateItem((EItemEffect)PUI.Effect, (EItemRareLevel)PUI.ItemLevel))
	{
		Object->DoItemEffect(TargetCharacter);
	}
}

void AMainGameMode::ProcessGetItem(PGetItem PGI)
{
	int8 Index = HexagonTile->GetItemTileIndex(PGI.ItemSerialNum);
	UE_LOG(LogTemp, Warning, TEXT("%d Item Removed on Map!"), Index);
	if (Index == -1) return;

	HexagonTile->RemoveItem(PGI.ItemSerialNum);

	PlayerController->UpdateImage(Index);
}

void AMainGameMode::ProcessBreakObject(PBreakObject PBO)
{
	// Find Windows using LOCATION
	//FVector ObjectLocation{ PBO.ObjectLocation.X, PBO.ObjectLocation.Y,PBO.ObjectLocation.Z };

	if (!WindowMeshComponents.IsValidIndex(PBO.ObjectSerial))
	{
		UE_LOG(LogTemp, Warning, TEXT("! WindowMeshComponents.IsValidIndex(%d)"), PBO.ObjectSerial);
		return;
	}

	UHierarchicalInstancedStaticMeshComponent* TargetObject = WindowMeshComponents[PBO.ObjectSerial];
	if (!IsValid(TargetObject)) return;

	UE_LOG(LogTemp, Warning, TEXT("TargetObject is %s"), *TargetObject->GetStaticMesh()->GetName());

	// Break Window 
	ASingleBuildingFloor* SBFloor = Cast<ASingleBuildingFloor>(TargetObject->GetOwner());
	if (!SBFloor)
	{
		UE_LOG(LogTemp, Warning, TEXT("SBFloor is nullptr"));
		return;
	}

	SBFloor->DoCollapseWindow(TargetObject, PBO.ObjectSerialChildIndex, FVector{ PBO.Direction.X, PBO.Direction.Y, PBO.Direction.Z });
	//TargetObject->DestroyComponent();
}

void AMainGameMode::ProcessRemoveObject(PRemoveObject PRO)
{
	UE_LOG(LogTemp, Warning, TEXT("AMainGameMode::ProcessRemoveObject"));
	if (auto ppActor = SkillActors.Find(PRO.ObjectSerial))
	{
		SkillActors.Remove(PRO.ObjectSerial);
		if (IsValid(*ppActor))
		{
			(*ppActor)->Destroy();
			SpawnSkillEffect(ESkillActor::BP_ElectTrap, FVector{ PRO.ObjectLocation.X,PRO.ObjectLocation.Y,PRO.ObjectLocation.Z });
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ppActor is InValid"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SerialNum %d is not In SkillActors"), PRO.ObjectSerial);
	}
}

void AMainGameMode::ProcessSkillInteract(PSkillInteract PKI)
{
	switch (PKI.SkillActor)
	{
	case ESkillActor::BP_DetectorMine:
		ProcessDetecting(PKI.InteractedPlayerSerial);
		break;
	case ESkillActor::BP_ShieldSphere:
		break;
	default:
		break;
	}
}

void AMainGameMode::ProcessDetecting(const uint8 DetectedSerial)
{
	if (Characters.IsValidIndex(DetectedSerial))
	{
		UE_LOG(LogTemp, Warning, TEXT("AMainGameMode::ProcessDetecting"));
		Characters[DetectedSerial]->CustomDepthOn();
	}
}

void AMainGameMode::ProcessTileBreakItem(const uint8 TargetSerial)
{	// 게임 플레이 중 타일 붕괴 아이템이 등장할 때에만 작동하는 함수이므로 GetAllActorsOfClass를 사용
	TArray<AActor*> TargetActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFurniture::StaticClass(), TargetActors);

	bool bUseItem{ false };
	for (AActor* Actor : TargetActors)
	{
		if (AFurniture* Furniture = Cast<AFurniture>(Actor))
		{
			if (Furniture->CollapseByTileCollapseItem(Characters[TargetSerial]))
			{
				bUseItem = true;
				break;
			}
		}
	}
}

//void AMainGameMode::ProcessRelocateObject(PRelocateObject PRO)
//{
//	if (AActor** ppTarget = SkillActors.Find(PRO.ObjectSerial))
//	{
//		AActor* SkillActor = *ppTarget;
//		SkillActor->SetActorLocation(FVector{ PRO.Location.X,PRO.Location.Y,PRO.Location.Z });
//		SkillActor->SetActorRotation(FRotator{ PRO.Rotation.X,PRO.Rotation.Y,PRO.Rotation.Z });
//
//
//	}
//	else
//	{
//		UE_LOG(LogTemp, Warning, TEXT("SkillActors Key<%d> Can't FIND!"), PRO.ObjectSerial);
//	}
//}

void AMainGameMode::GetHexagonTileOnLevel()
{
	AHexagonTile* Hexagon = Cast<AHexagonTile>(UGameplayStatics::GetActorOfClass(this, AHexagonTile::StaticClass()));
	if (!Hexagon)
	{
		UE_LOG(LogTemp, Warning, TEXT("AMainGameMode::GetHexagonTileOnLevel() AHexagonTIle Cast FAILED!"));
		return;
	}

	HexagonTile = Hexagon;
}

void AMainGameMode::GetWindowsOnLevel()
{
	for (TActorIterator<ASingleBuildingFloor> It(GetWorld()); It; ++It)
	{
		ASingleBuildingFloor* SingleBuildingFloor = *It;

		TArray<UHierarchicalInstancedStaticMeshComponent*> HISMWindows;
		SingleBuildingFloor->GetComponents<UHierarchicalInstancedStaticMeshComponent>(HISMWindows);

		// Find Window
		for (UHierarchicalInstancedStaticMeshComponent* MeshComponent : HISMWindows)
		{
			if (MeshComponent && MeshComponent->GetName() == ("HISM_Window"))
			{
				WindowMeshComponents.Add(MeshComponent);
			}
		}
	}

	WindowMeshComponents.Sort([](const UHierarchicalInstancedStaticMeshComponent& A, const UHierarchicalInstancedStaticMeshComponent& B) {
		return A.GetOwner()->GetName() < B.GetOwner()->GetName();
		});
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

TArray<ASkyscraperCharacter*> AMainGameMode::GetAllienceCharacters()
{
	TArray<ASkyscraperCharacter*> ReturnArray;
	if (SerialNum < MAXPLAYER / 2)
	{
		ReturnArray.Add(Characters[0]);
		ReturnArray.Add(Characters[1]);
		ReturnArray.Add(Characters[2]);
	}
	else
	{
		ReturnArray.Add(Characters[3]);
		ReturnArray.Add(Characters[4]);
		ReturnArray.Add(Characters[5]);
	}
	return ReturnArray;
}

TArray<ASkyscraperCharacter*> AMainGameMode::GetEnemyCharacters()
{
	TArray<ASkyscraperCharacter*> ReturnArray;
	if (SerialNum < MAXPLAYER / 2)
	{
		ReturnArray.Add(Characters[3]);
		ReturnArray.Add(Characters[4]);
		ReturnArray.Add(Characters[5]);
	}
	else
	{
		ReturnArray.Add(Characters[0]);
		ReturnArray.Add(Characters[1]);
		ReturnArray.Add(Characters[2]);
	}
	return ReturnArray;
}

void AMainGameMode::SendPlayerLocation()
{
	if (!Characters.IsValidIndex(SerialNum) || !Characters[SerialNum]) return;

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

	// FVector Velo = Characters[SerialNum]->GetVelocity();
	// PlayerPosition.PlayerXDirection = CalculateDirection({ Velo.X,Velo.Y,0.f }, Characters[SerialNum]->GetActorRotation());

	PlayerPosition.ControllerRotator = Characters[SerialNum]->Controller->GetControlRotation();

	m_Socket->Send(&PlayerPosition, sizeof(PPlayerPosition));
}

void AMainGameMode::SendPlayerSwapWeaponInfo()
{
	if (!Characters.IsValidIndex(SerialNum)) return;

	ASkyscraperCharacter* PossessCharacter = Characters[SerialNum];

	ESwapWeapon WeaponType;
	uint8 EquippedWeapon;

	if (PossessCharacter && PossessCharacter->CheckHoldWeapon(WeaponType, EquippedWeapon))
	{
		PSwapWeapon PSW(SerialNum, WeaponType);
		m_Socket->Send(&PSW, sizeof(PSW));

		UE_LOG(LogTemp, Warning, TEXT("Sending Swap Weapon!"));
	}
}

void AMainGameMode::SendSkillActorSpawn(const AActor* Sender, ESkillActor SkillActor, FVector SpawnLocation, FVector ForwardVec)
{
	if (Characters[SerialNum] != Sender) return;

	 PSpawnObject PSO;
	 
	 PSO.SpawnObject = SkillActor;
	 PSO.Location.X = SpawnLocation.X;	PSO.Location.Y = SpawnLocation.Y;	PSO.Location.Z = SpawnLocation.Z;
	 PSO.ForwardVec.X = ForwardVec.X;	PSO.ForwardVec.Y = ForwardVec.Y;	PSO.ForwardVec.Z = ForwardVec.Z;	 
	 PSO.ObjectSpawner = SerialNum;


	 if (m_Socket)
	 {
		 m_Socket->Send(&PSO, sizeof(PSO));
	 }
	 else
	 {
		 static uint16 Serial{0};
		 PSO.SerialNum = Serial++;
		 ProcessSpawnObject(PSO);
	 }
}

void AMainGameMode::SendAnimMontageStatus(const AActor* Sender, ECharacterAnimMontage eAnimMontage, int Section)
{
	if (Characters.IsEmpty())
	{
		return;
	}

	if (!GetIsConnected())
	{
		UE_LOG(LogTemp, Warning, TEXT("AMainGameMode::SendAnimMontageStatus() GetIsConnected() is FALSE"));
		return;
	}

	if (Sender != Characters[SerialNum])
	{
		UE_LOG(LogTemp, Warning, TEXT("AMainGameMode::SendAnimMontageStatus() Sender != Characters[SerialNum]"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Sending Anim Motage Status"));

	PChangeAnimMontage PCAM;

	PCAM.ChangedPlayerSerial = SerialNum;
	PCAM.eAnimMontage = eAnimMontage;
	PCAM.SectionNum = Section;

	Send(&PCAM, sizeof(PCAM));
}

bool AMainGameMode::SendTakeDamage(AActor* Sender, AActor* Target)
{

	if (!m_Socket->GetIsConnected() || Sender != Characters[SerialNum])
	{
		UE_LOG(LogTemp, Warning, TEXT("SendTakeDamage Sender != Characters[SerialNum]"));
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
	UE_LOG(LogTemp, Warning, TEXT("Send Weapon Damage"));
	return true;
}

void AMainGameMode::SendSkillInteract(const AActor* Sender, const ESkillActor SkillActor)
{
	if (!Characters.IsValidIndex(SerialNum) || Sender != Characters[SerialNum])
	{
		UE_LOG(LogTemp, Warning, TEXT("SendSkillInteract Sender != Characters[SerialNum]"));
		return;
	}

	PSkillInteract PSI;
	PSI.SkillActor = SkillActor;
	PSI.InteractedPlayerSerial = SerialNum;
	Send(&PSI, PSI.PacketSize);
}

void AMainGameMode::SendDamagedSkillActor(const AActor* Sender, const AActor* SkillActorOwner, const ESkillActor& SkillActorType, const AActor* SkillActor)
{
	if (!Characters.IsValidIndex(SerialNum) || Characters[SerialNum] != Sender)
	{
		//UE_LOG(LogTemp, Warning, TEXT("AMainGameMode::SendDamagedSkillActor SenderSerial == -1"));
		return;
	}

	int OwnerSerial = GetIndex(SkillActorOwner);
	if (OwnerSerial == -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("AMainGameMode::SendDamagedSkillActor OwnerSerial == -1"));
		return;
	}

	int SkillActorSerial{ -1 };
	for (const auto& sa : SkillActors)
	{
		if (sa.Value == SkillActor)
		{
			SkillActorSerial = sa.Key;
		}
	}
	if (SkillActorType != ESkillActor::BP_Shield && SkillActorSerial == -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("AMainGameMode::SendDamagedSkillActor SkillActorSerial == -1"));
		return;
	}

	ESwapWeapon weaponType;
	uint8 equippedWeapon;
	Characters[SerialNum]->CheckHoldWeapon(weaponType, equippedWeapon);

	PDamagedSkillActor PDSA;
	PDSA.SkillActorOwner = OwnerSerial;
	PDSA.SkillActor = SkillActorType;
	PDSA.SkillActorSerial = SkillActorSerial;
	PDSA.IsMelee = ((weaponType == ESwapWeapon::MeleeWeapon) ? true : false);
	PDSA.WeaponEnum = equippedWeapon;

	Send(&PDSA, PDSA.PacketSize);
}

void AMainGameMode::SendTileBreakItem(const AActor* Sender, uint8 TargetSerial)
{
	if (!Characters.IsValidIndex(SerialNum) || Sender != Characters[SerialNum]) return;

	if (SerialNum < MAXPLAYER / 2)
	{
		TargetSerial += MAXPLAYER / 2;
	}

	PUseItem PUI;
	PUI.Effect = (BYTE)EItemEffect::EIE_Tile_Break;
	PUI.ItemLevel = TargetSerial;
	PUI.UsePlayerSerial = SerialNum;
	Send(&PUI, PUI.PacketSize);
}

void AMainGameMode::SendDetecting(AActor* Sender, AActor* Target)
{
	if (Sender != Characters[SerialNum])
	{
		UE_LOG(LogTemp, Warning, TEXT("SendDetecting Sender != Characters[SerialNum]"));
		return;
	}

	int TargetSerial{ -1 };
	for (int i = 0; i < Characters.Num(); i++)
	{
		const auto& c = Characters[i];
		if (c == Target)
		{
			TargetSerial = i;
		}
	}
	if (TargetSerial == -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("AMainGameMode::SendDetecting TargetSerial == -1"));
	}

	PSkillInteract PSI;
	PSI.SkillActor = ESkillActor::BP_DetectorMine;
	PSI.InteractedPlayerSerial = TargetSerial;
	if (m_Socket)
	{
		Send(&PSI, PSI.PacketSize);
	}
	else
	{
		ProcessSkillInteract(PSI);
	}
}

void AMainGameMode::SendRemoveSkillActor(AActor* TargetActor)
{
	// ���� �����̷� Serial ��ȣ�� ������������
	// �ϴ� ����

	uint16 TargetSerialNum{ 0 };
	if (m_Socket)
	{
		for (const auto& SkillActorPair : SkillActors)
		{
			if (SkillActorPair.Value == TargetActor)
			{
				TargetSerialNum = SkillActorPair.Key;
				break;
			}
		}

		PRemoveObject PRO;
		PRO.ObjectSerial = TargetSerialNum;
		PRO.ObjectType = EObjectType::SkillActor;
		PRO.ObjectLocation = TargetActor->GetActorLocation();
		m_Socket->Send(&PRO, PRO.PacketSize);
	}
	SpawnSkillEffect(ESkillActor::BP_ElectTrap, TargetActor->GetActorLocation());
	SkillActors.Remove(TargetSerialNum);
}

void AMainGameMode::ChangeMeleeWeapon(EMeleeSelect NewMeleeSelect)
{
	if (PlayerSelectInfo.IsValidIndex(SerialNum))
	{
		PlayerSelectInfo[SerialNum]->PickedMeleeWeapon = NewMeleeSelect;
	}
}

void AMainGameMode::ChangeRangeWeapon(ERangeSelect NewRangeSelect)
{
	if (PlayerSelectInfo.IsValidIndex(SerialNum))
	{
		PlayerSelectInfo[SerialNum]->PickedRangeWeapon = NewRangeSelect;
	}
}

void AMainGameMode::SendStunDown(const AActor* Attacker, const AActor* Target, const FVector& Dirction, bool IsStun, float StunTime)
{
	int TargetSerialNum = GetIndex(Target);
	if (TargetSerialNum == -1) return;

	if (!m_Socket->GetIsConnected() || Characters.IsEmpty() || Attacker != Characters[SerialNum]) return;

	PStunDownState PSDS{ (BYTE)TargetSerialNum, Dirction, StunTime, IsStun };
	m_Socket->Send(&PSDS, sizeof(PSDS));
}

bool AMainGameMode::SendUseItem(const AActor* Sender, uint8 Effect, uint8 RareLevel)
{
	PUseItem PUI(SerialNum, (BYTE)Effect, (BYTE)RareLevel);
	if (!m_Socket->GetIsConnected() || Characters.IsEmpty() || Sender != Characters[SerialNum])
	{
		ProcessUseItem(PUI);
		return false;
	}

	m_Socket->Send(&PUI, sizeof(PUI));
	return true;
}

void AMainGameMode::SendGetItem(const AActor* Sender, const AActor* Item)
{
	if (!m_Socket->GetIsConnected() || Characters.IsEmpty() || Sender != Characters[SerialNum]) return;

	PGetItem PGI(HexagonTile->FindItemSerialNum(Item));
	m_Socket->Send(&PGI, sizeof(PGI));
}
   
void AMainGameMode::SendBreakObject(const AActor* Sender, const UPrimitiveComponent* BreakTarget, EObjectType BreakType)
{
	FVector Direction = (BreakTarget->GetComponentLocation() - Sender->GetActorLocation()).GetSafeNormal();

	if (!m_Socket->GetIsConnected())
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

void AMainGameMode::SendBreakObject(const AActor* Sender, const UPrimitiveComponent* BreakHISMTarget, int32 TargetIndex, EObjectType BreakType)
{
	FVector Direction = (BreakHISMTarget->GetComponentLocation() - Sender->GetActorLocation()).GetSafeNormal();

	if (!m_Socket->GetIsConnected())
	{
		PBreakObject PBO;
		int WindowIndex = GetWindowsIndex(BreakHISMTarget);
		PBO.ObjectType = BreakType;
		PBO.ObjectSerial = WindowIndex;
		PBO.ObjectSerialChildIndex = TargetIndex;
		PBO.Direction = Direction;
		ProcessBreakObject(PBO);
		return;
	}
	
	if (Characters.IsEmpty() || Sender != Characters[SerialNum]) return;

	int WindowIndex = GetWindowsIndex(BreakHISMTarget);
	PBreakObject PBO(BreakType, WindowIndex, Direction);
	PBO.ObjectSerialChildIndex = TargetIndex;
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
		UE_LOG(LogTemp, Warning, TEXT("AMainGameMode::GetIndex Cant find Target Actor ID"));
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

void AMainGameMode::PrintWidgets()
{
	TArray<UUserWidget*> FoundWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UUserWidget::StaticClass(), false);

	for (UUserWidget* Widget : FoundWidgets)
	{
		UE_LOG(LogTemp, Warning, TEXT("AMainGameMode::PrintWidgets() Found Widget: %s"), *Widget->GetName());
	}
}

void AMainGameMode::SpawnSkillActor_Implementation(ESkillActor SkillActor, FVector SpawnLocation, FVector ForwardVec, ASkyscraperCharacter* Spawner, FName Team) {}
void AMainGameMode::SpawnSkillEffect_Implementation(ESkillActor SkillActor, FVector SpawnLocation) {}