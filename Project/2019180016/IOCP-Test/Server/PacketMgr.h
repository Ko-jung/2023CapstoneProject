#pragma once

#include "../../../Common/EnumDef.h"

Packet* GetPacket(COMP_OP op);

class PacketMgr
{
public:
	PacketMgr() {}
	~PacketMgr() {}

public:
	//static class Packet* GetPacket(COMP_OP op);
};

