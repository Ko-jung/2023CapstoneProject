#pragma once

#include "../Packet/EnumDef.h"

struct Packet
{
	unsigned char SenderId;
};

// TODO: 회전 값도 넣어줘야함
struct PPosition : Packet
{
	float x;
	float y;
	float z;

	PPosition() { x = y = z = 0.f; }
	PPosition(float x, float y, float z)
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

	PSpawnObject() { SpawnObject = EObject::BP_Cube; x = y = z = 0.f; }
	PSpawnObject(EObject EO, float x, float y, float z)
	{
		this->SpawnObject	= EO;
		this->x				= x	;
		this->y				= y	;
		this->z				= z	;
	}
};
#pragma pack(pop)

Packet* GetPacket(COMP_OP op)
{
	switch (op)
	{
	case COMP_OP::OP_POSITION:
		return new PPosition();
	case COMP_OP::OP_OBJECTSPAWN:
		return new PSpawnObject();
	default:
		cout << "GetPacket Cant Find COMP_OP!" << endl;
		return nullptr;
	}
}