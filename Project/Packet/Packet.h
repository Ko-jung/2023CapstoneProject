#pragma once

#include <iostream>
#include "EnumDef.h"

using std::cout;
using std::endl;

struct Packet
{
	int PacketType;
	int RoomNum;

	Packet() :PacketType((int)COMP_OP::OP_RECV), RoomNum(-1) {}
	Packet(COMP_OP op) : PacketType((int)op), RoomNum(-1) {}
};

struct PTransform
{
	float x;
	float y;
	float z;

	float rx;
	float ry;
	float rz;

	PTransform() { x = y = z = rx = ry = rz = 0.f; }
	PTransform(float x, float y, float z) : x(x), y(y), z(z) { rx = ry = rz = 0.f; }
	PTransform(float x, float y, float z, float rx, float ry, float rz)
		: x(x), y(y), z(z), rx(rx), ry(ry), rz(rz)
	{}
};

struct PPosition : Packet, PTransform
{
	EObject ObjectType;

	PPosition() : Packet(COMP_OP::OP_POSITION), ObjectType(EObject::BP_Cube) { x = y = z = rx = ry = rz = 0.f; }
	PPosition(float x, float y, float z) : Packet(COMP_OP::OP_POSITION), PTransform(x, y, z), ObjectType(EObject::BP_Cube) {}
	PPosition(float x, float y, float z, float rx, float ry, float rz)
		: Packet(COMP_OP::OP_POSITION), PTransform(x, y, z, rx, ry, rz), ObjectType(EObject::BP_Cube)
	{}
};

#pragma pack(push, 1)
struct PPlayerPosition : Packet, PTransform
{
	int PlayerSerial;
	float PlayerSpeed;

	EPlayerState PlayerState;

	PPlayerPosition() : Packet(COMP_OP::OP_PLAYERPOSITION), PTransform(), PlayerState(EPlayerState::Stay) { }
	PPlayerPosition(float x, float y, float z, float speed, EPlayerState state = EPlayerState::Stay)
		: Packet(COMP_OP::OP_PLAYERPOSITION), PTransform(x, y, z), PlayerState(state), PlayerSpeed(speed)
	{ }
	PPlayerPosition(float x, float y, float z, float rx, float ry, float rz, float speed, EPlayerState state = EPlayerState::Stay)
		: Packet(COMP_OP::OP_PLAYERPOSITION), PTransform(x, y, z, rx, ry, rz), PlayerSpeed(speed)
	{ }
};
#pragma pack(pop)

#pragma pack(push, 1)
struct PSpawnObject : Packet, PTransform
{
	EObject SpawnObject;

	PSpawnObject() : Packet(COMP_OP::OP_OBJECTSPAWN), PTransform() { SpawnObject = EObject::BP_Cube; x = y = z = 0.f; }
	PSpawnObject(EObject EO, float x, float y, float z) : Packet(COMP_OP::OP_OBJECTSPAWN), PTransform(x, y, z)
	{
		this->SpawnObject = EO;
	}
};
#pragma pack(pop)

struct PPlayerJoin : Packet
{
	BYTE PlayerSerial;

	PPlayerJoin() : Packet(COMP_OP::OP_PLAYERJOIN) { PlayerSerial = -1; }
	PPlayerJoin(BYTE serial) : Packet(COMP_OP::OP_PLAYERJOIN) { PlayerSerial = serial; }
};

struct PDisconnect : Packet
{
	WORD DisconnectPlayerSerial;

	//PDisconnect() : Packet(COMP_OP::OP_DISCONNECT) { PlayerSerial = -1; }
	PDisconnect(WORD serial) : Packet(COMP_OP::OP_DISCONNECT) { DisconnectPlayerSerial = serial; }
};

struct PStartMatching : Packet
{
	PStartMatching() : Packet(COMP_OP::OP_STARTMATCHING) {}
};

struct PCancleMatching : Packet
{
	PCancleMatching() : Packet(COMP_OP::OP_CANCLEMATCHING) {}
};

struct PStartGame : Packet
{
	PStartGame() : Packet(COMP_OP::OP_STARTGAME) {}
};

struct PTileDrop : Packet
{
	PTileDrop() : Packet(COMP_OP::OP_TILEDROP) {}
};

// contained room num in RoomNum
struct PConnectToGameserver : Packet
{
	PConnectToGameserver() : Packet(COMP_OP::OP_CONNECTTOGAMESERVER) {}
};

struct PPlayerPickInfo : Packet
{
	ECharacter PickedCharacter;
	EMeleeWeapon PickedMeleeWeapon;
	ERangeWeapon PickedRangeWeapon;

	PPlayerPickInfo(ECharacter c, EMeleeWeapon meele, ERangeWeapon range) :
		Packet(COMP_OP::OP_PICKCHARACTER),
		PickedCharacter(c),
		PickedMeleeWeapon(meele),
		PickedRangeWeapon(range)
	{}

	PPlayerPickInfo() : Packet(COMP_OP::OP_PICKCHARACTER),
		PickedCharacter(ECharacter::NullCharacter),
		PickedMeleeWeapon(EMeleeWeapon::NullWeapon),
		PickedRangeWeapon(ERangeWeapon::NullWeapon)
	{}
};

// contained empty room num in RoomNum
struct PEmptyRoomNum : Packet
{
	PEmptyRoomNum() :Packet(COMP_OP::OP_SS_EMPTYROOMNUM) {}
};