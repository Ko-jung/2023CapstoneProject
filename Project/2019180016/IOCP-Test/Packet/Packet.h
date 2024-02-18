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

// TODO: ȸ�� ���� �־������
struct PPosition : Packet
{
	float x;
	float y;
	float z;

	float rx;
	float ry;
	float rz;

	PPosition() : Packet(COMP_OP::OP_POSITION){ x = y = z = rx = ry = rz = 0.f; }
	PPosition(float x, float y, float z) :Packet(COMP_OP::OP_POSITION)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		rx = ry = rz = 0.f;
	}
	PPosition(float x, float y, float z, float rx, float ry, float rz) : Packet(COMP_OP::OP_POSITION)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->rx = rx;
		this->ry = ry;
		this->rz = rz;
	}
};

#pragma pack(push, 1)
struct PPlayerPosition : PPosition
{
	int PlayerSerial;
	EPlayerState PlayerState;

	PPlayerPosition()
		: PPosition(), PlayerState(EPlayerState::Stay)
	{
		PacketType = (int)COMP_OP::OP_PLAYERPOSITION;
	}
	PPlayerPosition(float x, float y, float z , EPlayerState state = EPlayerState::Stay)
		: PPosition(x, y, z), PlayerState(state)
	{
		PacketType = (int)COMP_OP::OP_PLAYERPOSITION;
	}
	PPlayerPosition(float x, float y, float z, float rx, float ry, float rz, EPlayerState state = EPlayerState::Stay)
		: PPosition(x, y, z, rx, ry, rz)
	{
		PacketType = (int)COMP_OP::OP_PLAYERPOSITION;
	}
};
#pragma pack(pop)

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

	PPlayerJoin()			 : Packet(COMP_OP::OP_PLAYERJOIN) { PlayerSerial = -1; }
	PPlayerJoin(BYTE serial) : Packet(COMP_OP::OP_PLAYERJOIN) { PlayerSerial = serial; }
};