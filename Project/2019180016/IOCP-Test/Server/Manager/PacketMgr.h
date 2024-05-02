#pragma once

#include "../../../../Common/EnumDef.h"

#define MEMCPYBUFTOPACKET(packet) memcpy(&packet, p, sizeof(packet))

//Packet* GetPacket(COMP_OP op);

class PacketMgr
{
	SingleTon(PacketMgr)

public:
	PacketMgr() {}
	~PacketMgr() {}

public:
	void ProcessPacket(Packet* p, class ClientInfo* c);

	void GameBeginProcessing(int NowClientNum);
	void PlayerDeadProcessing(int ClientId);

private:
	// Timer Func
	void SendSelectTime(int NowClientNum, float time);
	void SendSpawn(int TargetClientID);
	void SendOffInvincibility(int TargetClientID);
	void SendStartGame(int RoomNum, int ClientNum, void* etc);

	const int GetWeaponDamage(const bool& isMelee, const int& weaponEnum);
};

