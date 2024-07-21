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
	void ProcessRequest(PRequestPacket PRP, int id);

	void GameBeginProcessing(int NowClientNum);
	void ProcessingPlayerDead(int ClientId);
	void ProcessingSkillInteract(ClientInfo* c, PSkillInteract PSI);
	void ProcessDamagedSkillActor(PDamagedSkillActor PDSA, const int id);

private:
	// Timer Func
	void SendSelectTime(int NowClientNum, float time);
	void SendSpawn(int TargetClientID);
	void SendOffInvincibility(int TargetClientID);
	void SendStartGame(int RoomNum, int ClientNum, void* etc);
	void SendTileDrop(int RoomNum, BYTE TileDropLevel);

	const float GetWeaponDamage(int Id, const bool& isMelee, const int& weaponEnum);
};

