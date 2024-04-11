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
	void StartGame(int RoomNum, int ClientNum, void* etc);

	void GameBeginProcessing(int NowClientNum);

private:
	void SendSelectTime(int NowClientNum, float time);

	int GetWeaponDamage(bool isMelee, int weaponEnum);
};

