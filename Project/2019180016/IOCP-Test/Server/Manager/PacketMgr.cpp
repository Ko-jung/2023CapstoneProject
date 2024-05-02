#include "../../Common/Define.h"

#include "PacketMgr.h"
#include "ClientMgr.h"
#include "TimerMgr.h"
#include "RoomMgr.h"

#include "../ClientInfo.h"
#include "../TimerEvent.h"

//Packet* PacketMgr::GetPacket(COMP_OP op)
//{
//	switch (op)
//	{
//	case COMP_OP::OP_POSITION:
//		return new PPosition();
//	case COMP_OP::OP_OBJECTSPAWN:
//		return new PSpawnObject();
//	default:
//		cout << "PacketMgr::GetPacket Cant Find COMP_OP!" << endl;
//		return nullptr;
//	}
//}

//Packet* GetPacket(COMP_OP op)
//{
//	switch (op)
//	{
//	case COMP_OP::OP_POSITION:
//		return new PPosition();
//	case COMP_OP::OP_OBJECTSPAWN:
//		return new PSpawnObject();
//	default:
//		cout << "GetPacket Cant Find COMP_OP!" << endl;
//		return nullptr;
//	}
//}

void PacketMgr::ProcessPacket(Packet* p, ClientInfo* c)
{
	switch (p->PacketType)
	{
	case (int)COMP_OP::OP_POSITION:

		break;
	case (int)COMP_OP::OP_PLAYERPOSITION:
	{
		PPlayerPosition PPP;
		//memcpy(&PPP, c->GetExp()->_wsa_buf.buf, sizeof(PPP));
		MEMCPYBUFTOPACKET(PPP);
		ClientMgr::Instance()->SendPacketToAllExceptSelf(c->GetClientNum(), &PPP, sizeof(PPP));
		//ClientMgr::Instance()->SendPacketToAllSocketsInRoom(c->GetClientNum() / 6, &PPP, sizeof(PPP));
	}
	break;
	case (int)COMP_OP::OP_DISCONNECT:
	{
		PDisconnect disconnect(-1);
		MEMCPYBUFTOPACKET(disconnect);
		ClientMgr::Instance()->Disconnect(disconnect.DisconnectPlayerSerial);
	}
	break;
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
	}
	break;
	case (int)COMP_OP::OP_DAMAGEDPLAYER:
	{
		PDamagedPlayer PDP;
		MEMCPYBUFTOPACKET(PDP, ReadByte);
		BYTE TargetPlayerSerialNum = PDP.ChangedPlayerSerial;
		const int Damage = GetWeaponDamage(PDP.IsMelee, PDP.WeaponEnum);
		auto& clients = ClientMgr::Instance()->GetClients();

		int id = c->GetClientNum();
		int SendPlayerRoomNum = id / MAXPLAYER;
		int TargetPlayerId = TargetPlayerSerialNum + SendPlayerRoomNum * MAXPLAYER;	// 0번 방 * 6 + TargetNum

		bool IsDead = clients[TargetPlayerId]->TakeDamage(Damage);
		PChangedPlayerHP PCPHP(TargetPlayerSerialNum, clients[TargetPlayerId]->GetCurrnetHp());
		ClientMgr::Instance()->SendPacketToAllSocketsInRoom(id / MAXPLAYER, &PCPHP, sizeof(PCPHP));

		if (IsDead)
		{
			PlayerDeadProcessing(TargetPlayerId);
		}
	}
	break;
	case (int)COMP_OP::OP_SPAWNOBJECT:
	{
		PSpawnObject PSO;
		MEMCPYBUFTOPACKET(PSO);
		ClientMgr::Instance()->SendPacketToAllSocketsInRoom(c->GetClientNum() / MAXPLAYER, &PSO, sizeof(PSO));
		break;
	}
	case (int)COMP_OP::OP_CHANGEANIMMONTAGE:
	{
		// PChangeAnimMontage PCAM;
		// MEMCPYBUFTOPACKET(PCAM);
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
	default:
		LogUtil::PrintLog("abc");
		break;
	}
}

void PacketMgr::SendStartGame(int RoomNum, int ClientNum, void* etc)
{
	PStartGame PSG;
	ClientMgr::Instance()->SendPacketToAllSocketsInRoom(RoomNum, &PSG, sizeof(PSG));
}

void PacketMgr::GameBeginProcessing(int NowClientNum)
{
	// 너무 빨리 보내면 못 받는다
	TimerEvent TE1(std::chrono::seconds(1),
		std::bind(&PacketMgr::SendSelectTime, this, NowClientNum, 20.f));
	TimerMgr::Instance()->Insert(TE1);

	TimerEvent TE2(std::chrono::seconds(20),
		std::bind(&PacketMgr::SendStartGame, this, NowClientNum / MAXPLAYER, NowClientNum % MAXPLAYER, nullptr));
	TimerMgr::Instance()->Insert(TE2);

	// ===Tile Drop Timers========

	//============================

	// ===new Room's Kill Count===
	RoomMgr::Instance()->AddRoom(NowClientNum / MAXPLAYER);
	//============================

	// collision Group
}

void PacketMgr::PlayerDeadProcessing(int ClientId)
{
	// Add Kill
	RoomMgr::Instance()->AddKillCount(ClientId);

	// Check Game End


	// Respawn Timer 10s, GodMode 3s
	TimerEvent RespawnTimer(std::chrono::seconds(10), std::bind(&PacketMgr::SendSpawn, this, ClientId));
	TimerEvent GodmodeTimer(std::chrono::seconds(13), std::bind(&PacketMgr::SendOffInvincibility, this, ClientId));

	TimerMgr::Instance()->Insert(RespawnTimer);
	TimerMgr::Instance()->Insert(GodmodeTimer);

	// Send Dead state
	PChangedPlayerState PCPS(ClientId % MAXPLAYER, ECharacterState::DEAD);
	ClientMgr::Instance()->SendPacketToAllSocketsInRoom(ClientId / MAXPLAYER, &PCPS, sizeof(PCPS));
}

const int PacketMgr::GetWeaponDamage(const bool& isMelee, const int& weaponEnum)
{
	if (isMelee)
	{
		switch (weaponEnum)
		{
		case (int)EMeleeWeapon::Dagger:
			return 120;
		case (int)EMeleeWeapon::Greatsword:
			return 200;
		case (int)EMeleeWeapon::Katana:
			return 150;
		default:
			return 0;
		}
	}
	else
	{
		switch (weaponEnum)
		{
		case (int)ERangeWeapon::AssaultRifle:
			return 100;
		case (int)ERangeWeapon::RPG:
			return 300;
		case (int)ERangeWeapon::SubmachineGun:
			return 50;
		default:
			return 0;
		}
	}
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

	PChangedPlayerState PCPS(TargetClientID, ECharacterState::INVINCIBILITY);
	ClientMgr::Instance()->SendPacketToAllSocketsInRoom(TargetClientID / MAXPLAYER, &PCPS, sizeof(PCPS));
}

void PacketMgr::SendOffInvincibility(int TargetClientID)
{
	PChangedPlayerState PCPS(TargetClientID, ECharacterState::LIVING);
	ClientMgr::Instance()->SendPacketToAllSocketsInRoom(TargetClientID / MAXPLAYER, &PCPS, sizeof(PCPS));
}
