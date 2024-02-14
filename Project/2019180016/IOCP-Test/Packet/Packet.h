#pragma once

#include <iostream>
#include "../Packet/EnumDef.h"

using std::cout;
using std::endl;

struct Packet
{
	int PacketType;

	Packet() {}
	Packet(COMP_OP op) : PacketType((int)op) {}
};

// TODO: 회전 값도 넣어줘야함
struct PPosition : Packet
{
	float x;
	float y;
	float z;

	PPosition() : Packet(COMP_OP::OP_POSITION){ x = y = z = 0.f; }
	PPosition(float x, float y, float z) : Packet(COMP_OP::OP_POSITION)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

#pragma pack(push, 1)
struct PSpawnObject : Packet
{
	EObject SpawnObject;
	float x;
	float y;
	float z;

	PSpawnObject() : Packet(COMP_OP::OP_OBJECTSPAWN) { SpawnObject = EObject::BP_Cube; x = y = z = 0.f; }
	PSpawnObject(EObject EO, float x, float y, float z) : Packet(COMP_OP::OP_OBJECTSPAWN)
	{
		this->SpawnObject	= EO;
		this->x				= x	;
		this->y				= y	;
		this->z				= z	;
	}
};
#pragma pack(pop)

struct PPlayerJoin : Packet
{
	BYTE PlayerSerial;

	PPlayerJoin(BYTE serial) : Packet(COMP_OP::OP_PLAYERJOIN) { PlayerSerial = serial; }
};