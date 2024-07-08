// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillSyncTestGameMode.h"
#include "NetworkManager.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
void ASkillSyncTestGameMode::BeginPlay()
{
	Super::BeginPlay();

	m_Socket->InitializeManager();
	m_Socket->SetState(ENetworkState::MainGame);
	Connect(GAME_SERVER_IP, GAME_SERVER_PORT);

	Characters.Init(nullptr, MAXPLAYER);
	PlayerSelectInfo.Init(nullptr, MAXPLAYER);

	PRequestPacket JoinRequest(COMP_OP::OP_JOINPLAYERINSKILLTEST);
	Send(&JoinRequest, JoinRequest.PacketSize);
}

void ASkillSyncTestGameMode::Tick(float)
{
	ProcessFunc();
}

void ASkillSyncTestGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ASkillSyncTestGameMode::ProcessFunc()
{
	//UE_LOG(LogClass, Warning, TEXT("Called AMainGameMode::ProcessFunc()"));
	Packet* packet;
	while (FuncQueue.try_pop(packet))
	{
		switch (packet->PacketType)
		{
		case (BYTE)COMP_OP::OP_JOINPLAYERINSKILLTEST:
		{
			PJoinPlayerInSkillTest* NewPlayer = reinterpret_cast<PJoinPlayerInSkillTest*>(packet);
			if (SerialNum == -1)
			{
				SerialNum = NewPlayer->ClientNum;
				PPlayerSelectInfo* NewSelectInfo = new PPlayerSelectInfo;
				NewSelectInfo->PickedCharacter = (ECharacterSelect)PlayerCharacter;
				NewSelectInfo->PickedMeleeWeapon = EMeleeSelect::EMS_Dagger;
				NewSelectInfo->PickedRangeWeapon = ERangeSelect::ERS_SMG;
				NewSelectInfo->ClientNum = SerialNum;
				PlayerSelectInfo[SerialNum] = NewSelectInfo;
				SpawnCharacter(SerialNum);

				Characters[SerialNum]->SetActorLocation(
					FVector{ FMath::RandRange(-100.f, 100.f),
							 FMath::RandRange(-100.f, 100.f),
												100.f });
			}
			else
			{
				if (PlayerSelectInfo.IsValidIndex(NewPlayer->ClientNum) && Characters.IsValidIndex(NewPlayer->ClientNum))
				{
					PPlayerSelectInfo* NewSelectInfo = new PPlayerSelectInfo;
					NewSelectInfo->PickedCharacter = NewPlayer->PickedCharacter;
					NewSelectInfo->PickedMeleeWeapon = NewPlayer->PickedMeleeWeapon;
					NewSelectInfo->PickedRangeWeapon = NewPlayer->PickedRangeWeapon;
					NewSelectInfo->ClientNum = NewPlayer->ClientNum;

					PlayerSelectInfo[NewPlayer->ClientNum] = NewSelectInfo;
					SpawnCharacter(NewPlayer->ClientNum);

					Characters[NewPlayer->ClientNum]->SetActorLocation(
						FVector{ FMath::RandRange(-100.f, 100.f),
								 FMath::RandRange(-100.f, 100.f),
													100.f });
				}
				else
				{
					UE_LOG(LogClass, Warning, TEXT("ASkillSyncTestGameMode::ProcessFunc() Characters.IsValidIndex(NewPlayer->ClientNum) Error!"));
				}
			}
			break;
		}
		case (BYTE)COMP_OP::OP_PLAYERPOSITION:
		{
			PPlayerPosition PPP;
			memcpy(&PPP, packet, sizeof(PPP));
			SetPlayerPosition(PPP);
			break;
		}
		case (BYTE)COMP_OP::OP_CHANGEDPLAYERSTATE:
		{
			ProcessChangedCharacterState(static_cast<PChangedPlayerState*>(packet));
			break;
		}
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
			if (Characters[PCAM.ChangedPlayerSerial])
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
	//UE_LOG(LogClass, Warning, TEXT("End Called AMainGameMode::ProcessFunc()"));
}