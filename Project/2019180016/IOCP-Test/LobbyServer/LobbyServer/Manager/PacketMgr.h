#pragma once
#include "../../../Common/Define.h"

class PacketMgr
{
	SingleTon(PacketMgr)

public:
	PacketMgr();

	void ProcessPacket(Packet* p, class LobbyClientInfo* c);
};

