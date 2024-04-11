#include "../../Common/Define.h"

#include "PacketMgr.h"
#include "ClientMgr.h"
#include "TimerMgr.h"

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
		ClientMgr::Instance()->ProcessPlayerPosition(PPP);
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

		int SendPlayerRoomNum = id / 6;
		ClientMgr::Instance()->GetClients()[id]->SetECharacter(PPS.PickedCharacter);

		// Send To Other Player Pick State
		ClientMgr::Instance()->SendPacketToAllSocketsInRoom(SendPlayerRoomNum, &PPS, sizeof(PPS));
	}
	break;
	case (int)COMP_OP::OP_DAMAGEDPLAYER:
	{
		PDamagedPlayer PDP;
		MEMCPYBUFTOPACKET(PDP, ReadByte);
		BYTE TargetPlayerSerialNum = PDP.ChangedPlayerSerial;
		int Damage = GetWeaponDamage(PDP.IsMelee, PDP.WeaponEnum);
		auto& clients = ClientMgr::Instance()->GetClients();

		int id = c->GetClientNum();
		int SendPlayerRoomNum = id / 6;
		int TargetPlayerId = TargetPlayerSerialNum + SendPlayerRoomNum * MAXPLAYER;	// 0번 방 * 6 + TargetNum

		bool IsDead = clients[TargetPlayerId]->TakeDamage(Damage);
		PChangedPlayerHP PCPHP(TargetPlayerSerialNum, clients[TargetPlayerId]->GetCurrnetHp());
		ClientMgr::Instance()->SendPacketToAllSocketsInRoom(id / 6, &PCPHP, sizeof(PCPHP));

		// 클라 둘 다 보내기 때문에  -> O editor printstring이 각 클라 둘다 찍힘 --- 해결완료
		// 알고보면 두 번 오는거다?  -> X printlog가 한 번만 찍힘. 체력은 결국 한 번만 깎이고 있다는거
		// 왜 서버는 한 번만 받는가? -> 두 개가 연속으로와서 뒷 부분이 짤리나? X -> exp가 달라서 그럴일 없는듯
		//							 -> Possess 하고 있는 클라이언트와 서버의 송수신이 안 되는거였다.
		// Possess 하고 있는 클라이언트와 서버의 송수신이 안 되는거였다. WHY?
		// 진짜 매우 가끔 된다. 매번 보내는 Position을 제거하면 정상 작동

		LogUtil::PrintLog("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");

		if (IsDead)
		{
			PChangedPlayerState PCPS(TargetPlayerSerialNum, ECharacterState::DEAD);
			ClientMgr::Instance()->SendPacketToAllSocketsInRoom(id / 6, &PCPS, sizeof(PCPS));
		}
	}
	break;
	default:
		LogUtil::PrintLog("abc");
		break;
	}
}

void PacketMgr::StartGame(int RoomNum, int ClientNum, void* etc)
{
	PStartGame PSG;
	ClientMgr::Instance()->SendPacketToAllSocketsInRoom(RoomNum, &PSG, sizeof(PSG));
}

void PacketMgr::GameBeginProcessing(int NowClientNum)
{
	// 너무 빨리 보내면 못 받는다
	TimerEvent TE1(std::chrono::seconds(1),
		std::bind(&PacketMgr::SendSelectTime, this, NowClientNum, 40.f));
	TimerMgr::Instance()->Insert(TE1);

	TimerEvent TE2(std::chrono::seconds(40),
		std::bind(&PacketMgr::StartGame, this, NowClientNum / 6, NowClientNum % 6, nullptr));
	TimerMgr::Instance()->Insert(TE2);
}

int PacketMgr::GetWeaponDamage(bool isMelee, int weaponEnum)
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
		case (int)ERangeWeapon::GrenadeLauncher:
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
	ClientMgr::Instance()->SendPacketToAllSocketsInRoom(NowClientNum / 6, &PST, sizeof(PST));
}