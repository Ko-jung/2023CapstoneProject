#include "../../Common/Define.h"

#include "PacketMgr.h"
#include "ClientMgr.h"
#include "TimerMgr.h"
#include "RoomMgr.h"

#include "../ClientInfo.h"
#include "../TimerEvent.h"

void PacketMgr::ProcessPacket(Packet* p, ClientInfo* c)
{
	switch (p->PacketType)
	{
	case (int)COMP_OP::OP_POSITION:

		break;
	case (int)COMP_OP::OP_PLAYERPOSITION:
	{
		PPlayerPosition PPP;
		MEMCPYBUFTOPACKET(PPP);
		//ClientMgr::Instance()->ProcessMove(c->GetClientNum(), PPP);

		ClientMgr::Instance()->SendPacketToAllExceptSelf(c->GetClientNum(), &PPP, sizeof(PPP));
		if (ClientMgr::Instance()->CheckFallDie(c->GetClientNum(), PPP))
		{
			ProcessingPlayerDead(c->GetClientNum());
		}
	break;
	}
	case (int)COMP_OP::OP_DISCONNECT:
	{
		PDisconnect disconnect;
		MEMCPYBUFTOPACKET(disconnect);
		ClientMgr::Instance()->Disconnect(c->GetClientNum());
		break;
	}
	case (int)COMP_OP::OP_SELECTWEAPONINFO:
	{
		PPlayerSelectInfo PPS;
		MEMCPYBUFTOPACKET(PPS, ReadByte);

		int id = c->GetClientNum();

		int SendPlayerRoomNum = id / MAXPLAYER;
		bool IsDuplicate = ClientMgr::Instance()->CheckSelectDuplication(id, PPS.PickedCharacter);

		if (IsDuplicate)
		{
			PPS.PickedCharacter = c->GetECharacter();
		}
		else
		{
			c->SetECharacter(PPS.PickedCharacter);
		}

		// Send To Other Player Pick State
		ClientMgr::Instance()->SendPacketToAllSocketsInRoom(SendPlayerRoomNum, &PPS, sizeof(PPS));
	break;
	}
	case (int)COMP_OP::OP_DAMAGEDPLAYER:
	{
		PDamagedPlayer PDP;
		MEMCPYBUFTOPACKET(PDP, ReadByte);
		BYTE TargetPlayerSerialNum = PDP.ChangedPlayerSerial;
		int id = c->GetClientNum();

		const float Damage = GetWeaponDamage(id, PDP.IsMelee, PDP.WeaponEnum);
		auto& clients = ClientMgr::Instance()->GetClients();

		int SendPlayerRoomNum = id / MAXPLAYER;
		int TargetPlayerId = TargetPlayerSerialNum + SendPlayerRoomNum * MAXPLAYER;	// 0번 방 * 6 + TargetNum
		
		// Already Dead
		if (clients[TargetPlayerId]->GetCurrnetHp() < 0.001f) return;

		bool IsDead = clients[TargetPlayerId]->TakeDamage(Damage);
		PChangedPlayerHP PCPHP(TargetPlayerSerialNum, clients[TargetPlayerId]->GetCurrnetHp());
		PCPHP.AttackerSerial = id % MAXPLAYER;
		ClientMgr::Instance()->SendPacketToAllSocketsInRoom(id / MAXPLAYER, &PCPHP, sizeof(PCPHP));

		if (IsDead)
		{
			ProcessingPlayerDead(TargetPlayerId);
		}
		break;
	}
	case (int)COMP_OP::OP_DAMAGEDSKILLACTOR:
	{
		PDamagedSkillActor PDSA;
		MEMCPYBUFTOPACKET(PDSA);
		ProcessDamagedSkillActor(PDSA, c->GetClientNum());
		break;
	}
	case (int)COMP_OP::OP_SPAWNOBJECT:
	{
		PSpawnObject PSO;
		MEMCPYBUFTOPACKET(PSO);
		PSO.SerialNum = RoomMgr::Instance()->GetNowSkillActorSerial(c->GetClientNum() / MAXPLAYER);
		//ClientMgr::Instance()->SendPacketToAllExceptSelf(c->GetClientNum(), &PSO, sizeof(PSO));
		ClientMgr::Instance()->SendPacketToAllSocketsInRoom(c->GetClientNum() / MAXPLAYER, &PSO, sizeof(PSO));
		break;
	}
	case (int)COMP_OP::OP_CHANGEANIMMONTAGE:
	{
		//PChangeAnimMontage PCAM;
		//MEMCPYBUFTOPACKET(PCAM);

		ClientMgr::Instance()->SendPacketToAllExceptSelf(c->GetClientNum(), p, sizeof(PChangeAnimMontage));
		break;
	}
	case (int)COMP_OP::OP_SWAPWEAPON:
	{
		// PSwapWeapon PSW;
		// MEMCPYBUFTOPACKET(PSW);
		ClientMgr::Instance()->SendPacketToAllExceptSelf(c->GetClientNum(), p, sizeof(PSwapWeapon));
		break;
	}
	case (int)COMP_OP::OP_REQUESTPACKET:
	{
		PRequestPacket PRP;
		MEMCPYBUFTOPACKET(PRP);
		ProcessRequest(PRP, c->GetClientNum());
		break;
	}
	case (int)COMP_OP::OP_STUNDOWNSTATE:
	{
		PStunDownState PSDS;
		MEMCPYBUFTOPACKET(PSDS);
		ClientMgr::Instance()->ProcessStunDown(c->GetClientNum(), PSDS);
		break;
	}
	case (int)COMP_OP::OP_USEITEM:
	{
		PUseItem PUI;
		MEMCPYBUFTOPACKET(PUI);
		ClientMgr::Instance()->ProcessItem(c->GetClientNum() / MAXPLAYER, PUI);
		break;
	}
	case (int)COMP_OP::OP_GETITEM:
	{
		PGetItem PGI;
		MEMCPYBUFTOPACKET(PGI);
		ClientMgr::Instance()->SendPacketToAllSocketsInRoom(c->GetClientNum() / MAXPLAYER, &PGI, sizeof(PGI));
		break;
	}
	case (int)COMP_OP::OP_BREAKOBJECT:
	{
		PBreakObject PBO;
		MEMCPYBUFTOPACKET(PBO);
		ClientMgr::Instance()->SendPacketToAllSocketsInRoom(c->GetClientNum() / MAXPLAYER, &PBO, sizeof(PBO));
		break;
	}
	case (int)COMP_OP::OP_REMOVEOBJECT:
	{
		PRemoveObject PRO;
		MEMCPYBUFTOPACKET(PRO);
		ClientMgr::Instance()->SendPacketToAllExceptSelf(c->GetClientNum(), &PRO, sizeof(PRO));
		break;
	}
	case (int)COMP_OP::OP_SKILLINTERACT:
	{
		PSkillInteract PSI;
		MEMCPYBUFTOPACKET(PSI);
		ProcessingSkillInteract(c, PSI);
		break;
	}
	case (int)COMP_OP::OP_OBJECTINTERACT:
	{
		PObjectInteract POI;
		MEMCPYBUFTOPACKET(POI);
		ClientMgr::Instance()->SendPacketToAllExceptSelf(c->GetClientNum(), &POI, sizeof(POI));
		break;
	}
	default:
	{
		if (p->PacketSize == 0)
		{
			cout << "[" << c->ClientNum << "] Recv PacketSize : 0" << endl;
			ClientMgr::Instance()->Init(c->ClientNum);
		}
		else
		{
			LogUtil::PrintLog("PacketMgr::ProcessPacket p->PacketType is DEFAULT");
		}
		break;
	}
	}
}

void PacketMgr::ProcessRequest(PRequestPacket PRP, int id)
{
	switch (PRP.RequestOp)
	{
	case COMP_OP::OP_BUILDINGINFO:
	{
		int ArraySize;
		BYTE* BuildingExist = RoomMgr::Instance()->GetBuildingExist(id / MAXPLAYER, ArraySize);

		PBuildingInfo PBI(ArraySize);
		memcpy(PBI.BuildInfo, BuildingExist, ArraySize);
		ClientMgr::Instance()->Send(id, &PBI, PBI.PacketSize);

		// TODO: Pool 사용 또는 Room 내부에 변수를 하나 더 생성
		delete BuildingExist;
		break;
	}
	case COMP_OP::OP_TILEDROP:
	{
		int RoomNum = id / MAXPLAYER;
		int CenterIndex;
		BYTE TileDropLevel = RoomMgr::Instance()->GetTileDropCenterIndex(RoomNum, CenterIndex);

		PTileDrop PTD(TileDropLevel, CenterIndex);
		ClientMgr::Instance()->SendPacketToAllSocketsInRoom(RoomNum, &PTD, sizeof(PTD));

		PSetTimer PST(ETimer::TileDropTimer, 300.f);
		ClientMgr::Instance()->Send(id, &PST, sizeof(PST));
		break;
	}
	case COMP_OP::OP_SETTIMER:
	{
		int RoomNum = id / MAXPLAYER;
		float durationTime = RoomMgr::Instance()->GetRoomElapsedTime(RoomNum);

		PSetTimer PST(ETimer::TileDropTimer, 300.f - durationTime);
		ClientMgr::Instance()->Send(id, &PST, sizeof(PST));
		break;
	}
	case COMP_OP::OP_SPAWNITEM:
	{
		int RoomNum = id / MAXPLAYER;
		RoomMgr::Instance()->RequestSendItemSpawn(RoomNum);
		break;
	}
	case COMP_OP::OP_FINISHGAME:
	{
		int RoomNum = id / MAXPLAYER;
		PFinishGame PFG;
		ClientMgr::Instance()->SendPacketToAllSocketsInRoom(RoomNum, &PFG, sizeof(PFG));
		break;
	}
	case COMP_OP::OP_JOINPLAYERINSKILLTEST:
	{
		PJoinPlayerInSkillTest NewPlayer;
		NewPlayer.ClientNum = id % MAXPLAYER;
		ClientMgr::Instance()->SendPacketToAllSocketsInRoom(id / MAXPLAYER, &NewPlayer, NewPlayer.PacketSize);
		ClientMgr::Instance()->SendOldPlayerList(id);
		break;
	}
	default:
		break;
	}
}

void PacketMgr::SendStartGame(int RoomNum, int ClientNum, void* etc)
{
	PStartGame PSG;
	ClientMgr::Instance()->SendPacketToAllSocketsInRoom(RoomNum, &PSG, sizeof(PSG));

	RoomMgr::Instance()->StartTime(RoomNum);
}

// TODO: RoomMgr로 이동
void PacketMgr::SendTileDrop(int RoomNum, BYTE TileDropLevel)
{
	BYTE TDLevel = RoomMgr::Instance()->GetTileDropLevel(RoomNum);
	// 이미 Exec 함수로 호출하였다.
	if (TDLevel >= TileDropLevel) return;

	float NextTimer{};

	if (TDLevel < 2)	NextTimer = 300.f;	//300
	else				NextTimer = 60.f;	//60

	int CenterIndex;
	TDLevel = RoomMgr::Instance()->GetTileDropCenterIndex(RoomNum, CenterIndex);

	PTileDrop PTD(TileDropLevel, BYTE(CenterIndex));
	ClientMgr::Instance()->SendPacketToAllSocketsInRoom(RoomNum, &PTD, sizeof(PTD));

	PSetTimer PST(ETimer::TileDropTimer, NextTimer);
	ClientMgr::Instance()->SendPacketToAllSocketsInRoom(RoomNum, &PST, sizeof(PST));

	if (TDLevel != 9)
	{
		TimerEvent NewTileDropTimer(std::chrono::seconds((int)NextTimer),
			std::bind(&PacketMgr::SendTileDrop, this, RoomNum, TDLevel + 1));
		TimerMgr::Instance()->Insert(NewTileDropTimer);
	}
}

void PacketMgr::GameBeginProcessing(int NowClientId)
{
	// 너무 빨리 보내면 못 받는다
	TimerEvent TE1(std::chrono::seconds(1),
		std::bind(&PacketMgr::SendSelectTime, this, NowClientId, (float)SELECTTIMESECOND));
	TimerMgr::Instance()->Insert(TE1);

	TimerEvent TE2(std::chrono::seconds(SELECTTIMESECOND),
		std::bind(&PacketMgr::SendStartGame, this, NowClientId / MAXPLAYER, NowClientId % MAXPLAYER, nullptr));
	TimerMgr::Instance()->Insert(TE2);

	// ======== Tile Drop ========
	TimerEvent TileDrop1Timer(std::chrono::seconds((300 + SELECTTIMESECOND)),
		std::bind(&PacketMgr::SendTileDrop, this, NowClientId / MAXPLAYER, 1));
	TimerMgr::Instance()->Insert(TileDrop1Timer);

	// TimerEvent TileDrop2Timer(std::chrono::seconds(120 + SELECTTIMESECOND),
	// 	std::bind(&PacketMgr::SendTileDrop, this, NowClientId / MAXPLAYER, 2));
	// TimerMgr::Instance()->Insert(TileDrop2Timer);
	// 
	// TimerEvent TileDrop3Timer(std::chrono::seconds(180 + SELECTTIMESECOND),
	// 	std::bind(&PacketMgr::SendTileDrop, this, NowClientId / MAXPLAYER, 3));
	// TimerMgr::Instance()->Insert(TileDrop3Timer);
	//============================

	// ======== new Room =========
	RoomMgr::Instance()->AddRoom(NowClientId / MAXPLAYER);
	//============================

	// collision Group
}

void PacketMgr::ProcessingPlayerDead(int ClientId)
{
	cout << ClientId << "Is Dead" << endl;

	// Add Kill
	RoomMgr::Instance()->AddKillCount(ClientId);

	// Check Game End
	// TODO: ADDKILLCOUNT와 동시에 하게
	if (int Winner = RoomMgr::Instance()->IsEndGame(ClientId / MAXPLAYER) != 0)
	{
		PFinishGame PFG;
		if (Winner > 0)
			PFG.IsTeamAWin = true;
		else
			PFG.IsTeamAWin = false;
		ClientMgr::Instance()->SendPacketToAllSocketsInRoom(ClientId / MAXPLAYER, &PFG, sizeof(PFG));
	}


	// Respawn Timer 10s, GodMode 3s
	TimerEvent RespawnTimer(std::chrono::seconds(10), std::bind(&PacketMgr::SendSpawn, this, ClientId));
	TimerEvent GodmodeTimer(std::chrono::seconds(13), std::bind(&PacketMgr::SendOffInvincibility, this, ClientId));

	if (RoomMgr::Instance()->GetTileDropLevel(ClientId / MAXPLAYER) < 2)
	{
		TimerMgr::Instance()->Insert(RespawnTimer);
		TimerMgr::Instance()->Insert(GodmodeTimer);
	}
	else
	{
		if (int Winner = RoomMgr::Instance()->CharacterDead(ClientId) != 0)
		{
			PFinishGame PFG;
			if (Winner > 0)
				PFG.IsTeamAWin = true;
			else
				PFG.IsTeamAWin = false;
			ClientMgr::Instance()->SendPacketToAllSocketsInRoom(ClientId / MAXPLAYER, &PFG, sizeof(PFG));
		}
	}

	// Send Dead state
	//ClientMgr::Instance()->ChangeState(ClientId, ECharacterState::DEAD);
	PChangedPlayerState PCPS(ClientId % MAXPLAYER, ECharacterState::DEAD);
	ClientMgr::Instance()->SendPacketToAllSocketsInRoom(ClientId / MAXPLAYER, &PCPS, sizeof(PCPS));
}

void PacketMgr::ProcessingSkillInteract(ClientInfo* c, PSkillInteract PSI)
{
	switch (PSI.SkillActor)
	{
	case ESkillActor::BP_DetectorMine:
		ClientMgr::Instance()->SendPacketToAllience(c->GetClientNum(), &PSI, sizeof(PSI));
		ClientMgr::Instance()->Send((c->GetClientNum() / MAXPLAYER) * MAXPLAYER + PSI.InteractedPlayerSerial, &PSI, sizeof(PSI));
		break;
	case ESkillActor::BP_ShieldSphere:
		ClientMgr::Instance()->ProcessShieldSphereHeal(c->GetClientNum(), PSI);
		break;
	default:
		break;
	}
}

void PacketMgr::ProcessDamagedSkillActor(PDamagedSkillActor PDSA, const int id)
{
	int RoomId = id / MAXPLAYER;
	const float Damage = GetWeaponDamage(id, PDSA.IsMelee, PDSA.WeaponEnum);
	switch (PDSA.SkillActor)
	{
	case ESkillActor::BP_Shield:
	{
		PChangedSkillActorHP PCHP;
		PCHP.ChangedSkillActorOwner = PDSA.SkillActorOwner;
		PCHP.ChangedSkillActorSerial = PDSA.SkillActorSerial;
		PCHP.AfterHP = ClientMgr::Instance()->ProcessShieldDamaged(id, PDSA, Damage);
		ClientMgr::Instance()->SendPacketToAllSocketsInRoom(RoomId, &PCHP, PCHP.PacketSize);
		break;
	}
	case ESkillActor::BP_ElectTrap:
		break;
	case ESkillActor::BP_DetectorMine:
		break;
	default:
		break;
	}
}

const float PacketMgr::GetWeaponDamage(int Id, const bool& isMelee, const int& weaponEnum)
{
	float WeaponDamage{ 0.f };
	if (isMelee)
	{
		switch (weaponEnum)
		{
		case (int)EMeleeWeapon::Dagger:
			WeaponDamage = 120;
			break;
		case (int)EMeleeWeapon::Greatsword:
			WeaponDamage = 200;
			break;
		case (int)EMeleeWeapon::Katana:
			WeaponDamage = 150;
			break;
		default:
			WeaponDamage = 0;
			break;
		}
	}
	else
	{
		switch (weaponEnum)
		{
		case (int)ERangeWeapon::AssaultRifle:
			WeaponDamage = 100;
			break;
		case (int)ERangeWeapon::RPG:
			WeaponDamage = 300;
			break;
		case (int)ERangeWeapon::SubmachineGun:
			WeaponDamage = 50;
			break;
		default:
			WeaponDamage = 0;
			break;
		}
	}

	//cout << "[" << Id << "] Damage Is " << WeaponDamage * ClientMgr::Instance()->GetClients()[Id]->Power << endl;
	return WeaponDamage * ClientMgr::Instance()->GetClients()[Id]->Power;
}


//void IOCPServer::SendPlayerJoinPacket(int JoinPlayerSerial)
//{
//	PPlayerJoin JoinPacket(m_iClientId);
//	for (const auto& socket : m_Clients)
//	{
//		if (socket->GetClientNum() != -1)
//		{
//			socket->SendProcess(sizeof(PPlayerJoin), &JoinPacket);
//		}
//	}
//}
//
//void IOCPServer::SendTileDrop(int id)
//{
//	PTileDrop PTD;
//	m_Clients[id]->SendProcess(sizeof(PTileDrop), &PTD);
//}
//

void PacketMgr::SendSelectTime(int NowClientNum, float time)
{
	PSetTimer PST = PSetTimer(ETimer::SelectTimer, time);
	ClientMgr::Instance()->SendPacketToAllSocketsInRoom(NowClientNum / MAXPLAYER, &PST, sizeof(PST));
}

void PacketMgr::SendSpawn(int TargetClientID)
{
	// Set Full HP
	ClientMgr::Instance()->Heal(TargetClientID, -1);

	//ClientMgr::Instance()->ChangeState(TargetClientID, ECharacterState::INVINCIBILITY);
	ClientMgr::Instance()->ChangeState(TargetClientID, ECharacterState::INVINCIBILITY);
	PChangedPlayerState PCPS(TargetClientID, ECharacterState::INVINCIBILITY);
	ClientMgr::Instance()->SendPacketToAllSocketsInRoom(TargetClientID / MAXPLAYER, &PCPS, sizeof(PCPS));
}

void PacketMgr::SendOffInvincibility(int TargetClientID)
{
	ClientMgr::Instance()->ChangeState(TargetClientID, ECharacterState::LIVING);
	PChangedPlayerState PCPS(TargetClientID, ECharacterState::LIVING);
	ClientMgr::Instance()->SendPacketToAllSocketsInRoom(TargetClientID / MAXPLAYER, &PCPS, sizeof(PCPS));
}
