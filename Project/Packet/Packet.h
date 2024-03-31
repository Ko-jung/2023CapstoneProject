#pragma once

#include <iostream>
#include "EnumDef.h"

using std::cout;
using std::endl;

#pragma pack(push, 1)
struct Packet
{
	BYTE PacketType;
	//int PacketType;
	int RoomNum;

	Packet() :PacketType((int)COMP_OP::OP_RECV), RoomNum(-1) {}
	Packet(COMP_OP op) : PacketType((int)op), RoomNum(-1) {}
};
#pragma pack(pop)

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

struct PDamagedPlayer : Packet
{
	int ChangedPlayerSerial;
	bool IsMelee;
	char WeaponEnum;

	PDamagedPlayer() : Packet(COMP_OP::OP_DAMAGEDPLAYER), ChangedPlayerSerial(-1), IsMelee(true), WeaponEnum(-1){ }
	PDamagedPlayer(int serial, bool isMelee, char weaponEnum) : Packet(COMP_OP::OP_CHANGEDPLAYERHP),
		ChangedPlayerSerial(serial), IsMelee(isMelee), WeaponEnum(weaponEnum) { }
};

struct PChangedPlayerHP : Packet
{
	int ChangedPlayerSerial;
	float AfterHP;

	PChangedPlayerHP() : Packet(COMP_OP::OP_DAMAGEDPLAYER), ChangedPlayerSerial(-1), AfterHP(-1.f) {}
	PChangedPlayerHP(int changedPlayerSerial, float afterHP) : Packet(COMP_OP::OP_DAMAGEDPLAYER),
		ChangedPlayerSerial(changedPlayerSerial), AfterHP(afterHP) {}
};

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

struct PPlayerSelectInfo : Packet
{
	ECharacter PickedCharacter;
	EMeleeWeapon PickedMeleeWeapon;
	ERangeWeapon PickedRangeWeapon;
	BYTE ClientNum;

	PPlayerSelectInfo(ECharacter c, EMeleeWeapon meele, ERangeWeapon range, BYTE sendClientNum) :
		Packet(COMP_OP::OP_SELECTWEAPONINFO),
		PickedCharacter(c),
		PickedMeleeWeapon(meele),
		PickedRangeWeapon(range),
		ClientNum(sendClientNum)
	{}

	PPlayerSelectInfo() : Packet(COMP_OP::OP_SELECTWEAPONINFO),
		PickedCharacter(ECharacter::NullCharacter),
		PickedMeleeWeapon(EMeleeWeapon::NullWeapon),
		PickedRangeWeapon(ERangeWeapon::NullWeapon),
		ClientNum(-1)
	{}
}; 

// contained empty room num in RoomNum
struct PEmptyRoomNum : Packet
{
	PEmptyRoomNum() :Packet(COMP_OP::OP_SS_EMPTYROOMNUM) {}
};

#pragma pack(push, 1)
// 
struct PSetTimer : Packet
{
	ETimer TimerType;
	float SecondsUntilActivation;	// ex) 캐릭터 선택 창의 제한시간 (40s)
	PSetTimer() :Packet(COMP_OP::OP_SETTIMER), SecondsUntilActivation(0.f), TimerType(ETimer::DefaultTimer) {}
	PSetTimer(ETimer type, float secondTime) : Packet(COMP_OP::OP_SETTIMER), SecondsUntilActivation(secondTime), TimerType(type) {}
};
#pragma pack(pop)