#pragma once

#include <iostream>
#include "EnumDef.h"

using std::cout;
using std::endl;

// Using in Packet
#pragma pack(push, 1)
struct PVector
{
	float X;
	float Y;
	float Z;
	PVector() { X = Y = Z = 0.f; }
	PVector(float x, float y, float z) { X = x; Y = y; Z = z; }
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Packet
{
	BYTE PacketSize;
	BYTE PacketType;

	Packet() :PacketType((int)COMP_OP::OP_RECV) { PacketSize = sizeof(Packet); }
	Packet(COMP_OP op) : PacketType((int)op) { PacketSize = sizeof(Packet); }
};

struct PTransform
{
	PVector Location;

	PVector Rotate;

	PTransform() { Location.X = Location.Y = Location.Z = Rotate.X = Rotate.Y = Rotate.Z = 0.f; }
	PTransform(float x, float y, float z) : Location{ x, y, z } { Rotate = PVector{}; }
	PTransform(float x, float y, float z, float rx, float ry, float rz)
		: Location{ x, y, z }, Rotate{ rx, ry, rz } {}
};

//struct PPosition : Packet, PTransform
//{
//	EObject ObjectType;
//
//	PPosition() : Packet(COMP_OP::OP_POSITION), ObjectType(EObject::BP_NULL) { Location = Rotate = PVector{}; PacketSize = sizeof(PPosition); }
//	PPosition(float x, float y, float z) : Packet(COMP_OP::OP_POSITION), PTransform(x, y, z), ObjectType(EObject::BP_NULL) { PacketSize = sizeof(PPosition); }
//	PPosition(float x, float y, float z, float rx, float ry, float rz)
//		: Packet(COMP_OP::OP_POSITION), PTransform(x, y, z, rx, ry, rz), ObjectType(EObject::BP_NULL)
//	{
//		PacketSize = sizeof(PPosition);
//	}
//};

struct PPlayerPosition : Packet, PTransform
{
	BYTE PlayerSerial;
	float PlayerSpeed;
	float PlayerXDirection;

	//EPlayerState PlayerState;

	PPlayerPosition()
		: Packet(COMP_OP::OP_PLAYERPOSITION), PTransform(), PlayerSpeed(0.f)//, PlayerState(EPlayerState::Stay)
	{
		PacketSize = sizeof(PPlayerPosition);
	}
	PPlayerPosition(float x, float y, float z, float speed/*, EPlayerState state = EPlayerState::Stay*/)
		: Packet(COMP_OP::OP_PLAYERPOSITION), PTransform(x, y, z), PlayerSpeed(speed)//, PlayerState(state)
	{
		PacketSize = sizeof(PPlayerPosition);
	}
	PPlayerPosition(float x, float y, float z, float rx, float ry, float rz, float speed/*, EPlayerState state = EPlayerState::Stay*/)
		: Packet(COMP_OP::OP_PLAYERPOSITION), PTransform(x, y, z, rx, ry, rz), PlayerSpeed(speed)//, PlayerState(state)
	{
		PacketSize = sizeof(PPlayerPosition);
	}
};

struct PDamagedPlayer : Packet
{
	BYTE ChangedPlayerSerial;
	bool IsMelee;
	char WeaponEnum;

	PDamagedPlayer() : Packet(COMP_OP::OP_DAMAGEDPLAYER), ChangedPlayerSerial(-1), IsMelee(true), WeaponEnum(-1) { PacketSize = sizeof(PDamagedPlayer); }
	PDamagedPlayer(BYTE serial, bool isMelee, char weaponEnum) : Packet(COMP_OP::OP_DAMAGEDPLAYER),
		ChangedPlayerSerial(serial), IsMelee(isMelee), WeaponEnum(weaponEnum) {
		PacketSize = sizeof(PDamagedPlayer);
	}
};

// Send If Character Damaged
struct PChangedPlayerHP : Packet
{
	BYTE ChangedPlayerSerial;
	float AfterHP;

	PChangedPlayerHP() : Packet(COMP_OP::OP_CHANGEDPLAYERHP), ChangedPlayerSerial(-1), AfterHP(-1.f) { PacketSize = sizeof(PChangedPlayerHP); }
	PChangedPlayerHP(int changedPlayerSerial, float afterHP) : Packet(COMP_OP::OP_CHANGEDPLAYERHP),
		ChangedPlayerSerial(changedPlayerSerial), AfterHP(afterHP) {
		PacketSize = sizeof(PChangedPlayerHP);
	}
};

// Send If Character Dead or ReSpawn
struct PChangedPlayerState : Packet
{
	BYTE ChangedPlayerSerial;
	ECharacterState State;

	PChangedPlayerState() : Packet(COMP_OP::OP_CHANGEDPLAYERSTATE), ChangedPlayerSerial(-1), State(ECharacterState::LIVING) { PacketSize = sizeof(PChangedPlayerState); }
	PChangedPlayerState(int serial, ECharacterState state) :
		Packet(COMP_OP::OP_CHANGEDPLAYERSTATE), ChangedPlayerSerial(serial), State(state) {
		PacketSize = sizeof(PChangedPlayerState);
	}
};

struct PStunDownState : Packet
{
	BYTE TargetSerialNum;
	PVector Direction;
	float StunTime;
	bool IsStun;

	PStunDownState() : Packet(COMP_OP::OP_STUNDOWNSTATE), TargetSerialNum(0), Direction{ PVector{} }, StunTime(0.f), IsStun(true) { PacketSize = sizeof(PStunDownState); }
	PStunDownState(BYTE targetNum, PVector direction, float stunTime, bool isStun) : Packet(COMP_OP::OP_STUNDOWNSTATE),
		TargetSerialNum(targetNum), Direction{ direction }, StunTime(stunTime), IsStun(isStun) { PacketSize = sizeof(PStunDownState); }
};

struct PSpawnObject : Packet, PTransform
{
	EObject SpawnObject;
	PVector ForwardVec;
	BYTE SerialNum;

	PSpawnObject() : Packet(COMP_OP::OP_SPAWNOBJECT), PTransform(), SerialNum(-1) { SpawnObject = EObject::BP_NULL; Location = PVector{}; PacketSize = sizeof(PSpawnObject); }
	// PSpawnObject(EObject EO, PVector Location, PVector Forward) : Packet(COMP_OP::OP_SPAWNOBJECT), PTransform(Location.X, Location.Y, Location.Z)
	// {
	// 	this->SpawnObject = EO;
	// 	PacketSize = sizeof(PSpawnObject);
	// }
};

struct PPlayerJoin : Packet
{
	BYTE PlayerSerial;

	PPlayerJoin() : Packet(COMP_OP::OP_PLAYERJOIN) { PlayerSerial = -1; PacketSize = sizeof(PPlayerJoin); }
	PPlayerJoin(BYTE serial) : Packet(COMP_OP::OP_PLAYERJOIN) { PlayerSerial = serial; PacketSize = sizeof(PPlayerJoin); }
};

struct PDisconnect : Packet
{
	//WORD DisconnectPlayerSerial;

	PDisconnect() : Packet(COMP_OP::OP_DISCONNECT) { PacketSize = sizeof(PDisconnect); }
	//PDisconnect(WORD serial) : Packet(COMP_OP::OP_DISCONNECT) {
	//	DisconnectPlayerSerial = serial; PacketSize = sizeof(PDisconnect);
	//}
};

struct PStartMatching : Packet
{
	PStartMatching() : Packet(COMP_OP::OP_STARTMATCHING) { PacketSize = sizeof(PStartMatching); }
};

struct PCancleMatching : Packet
{
	PCancleMatching() : Packet(COMP_OP::OP_CANCLEMATCHING) { }
};

struct PStartGame : Packet
{
	PStartGame() : Packet(COMP_OP::OP_STARTGAME) { }
};

struct PFinishGame : Packet
{
	bool IsTeamAWin;
	PFinishGame() : Packet(COMP_OP::OP_FINISHGAME), IsTeamAWin(false) { PacketSize = sizeof(PFinishGame); }
	PFinishGame(bool winner) : Packet(COMP_OP::OP_FINISHGAME), IsTeamAWin(winner) { PacketSize = sizeof(PFinishGame); }
};

struct PTileDrop : Packet
{
	BYTE TileDropLevel;
	BYTE CenterIndex;
	PTileDrop() : Packet(COMP_OP::OP_TILEDROP), TileDropLevel(0), CenterIndex(0) { PacketSize = sizeof(PTileDrop); }
	PTileDrop(BYTE TileDropLevel, BYTE CenterIndex) : Packet(COMP_OP::OP_TILEDROP), TileDropLevel(TileDropLevel), CenterIndex(CenterIndex)
	{ PacketSize = sizeof(PTileDrop); }
};

// contained room num in RoomNum
struct PConnectToGameserver : Packet
{
	PConnectToGameserver() : Packet(COMP_OP::OP_CONNECTTOGAMESERVER) {  }
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
	{
		PacketSize = sizeof(PPlayerSelectInfo);
	}

	PPlayerSelectInfo() : Packet(COMP_OP::OP_SELECTWEAPONINFO),
		PickedCharacter(ECharacter::NullCharacter),
		PickedMeleeWeapon(EMeleeWeapon::NullWeapon),
		PickedRangeWeapon(ERangeWeapon::NullWeapon),
		ClientNum(-1)
	{
		PacketSize = sizeof(PPlayerSelectInfo);
	}
};

// contained empty room num in RoomNum
struct PEmptyRoomNum : Packet
{
	int RoomNum;
	PEmptyRoomNum() :Packet(COMP_OP::OP_SS_EMPTYROOMNUM) { PacketSize = sizeof(PEmptyRoomNum); }
};

struct PSetTimer : Packet
{
	ETimer TimerType;
	float SecondsUntilActivation;	// ex) 캐릭터 선택 창의 제한시간 (40s)
	PSetTimer() :Packet(COMP_OP::OP_SETTIMER), TimerType(ETimer::DefaultTimer), SecondsUntilActivation(0.f) { PacketSize = sizeof(PSetTimer); }
	PSetTimer(ETimer type, float secondTime) : Packet(COMP_OP::OP_SETTIMER), TimerType(type), SecondsUntilActivation(secondTime) { PacketSize = sizeof(PSetTimer); }
};

struct PItemInfo
{
	BYTE ItemSerialNum;
	BYTE TileIndex;
	BYTE Floor;
	BYTE Effect;
	BYTE ItemLevel;

	PItemInfo() {};
	PItemInfo(BYTE ItemSerialNum, BYTE TileIndex, BYTE Floor, BYTE Effect, BYTE ItemLevel) :
		ItemSerialNum(ItemSerialNum), TileIndex(TileIndex), Floor(Floor), Effect(Effect), ItemLevel(ItemLevel){}
};
struct PSpawnItem : Packet
{
	PItemInfo Item[5];
	BYTE SpawnCount;

	PSpawnItem() : Packet(COMP_OP::OP_SPAWNITEM), SpawnCount(0) { PacketSize = sizeof(PSpawnItem); }
	PSpawnItem(BYTE SpawnCount) : Packet(COMP_OP::OP_SPAWNITEM), SpawnCount(SpawnCount) { PacketSize = sizeof(PSpawnItem); }
};

struct PUseItem : Packet
{
	BYTE UsePlayerSerial;
	BYTE Effect;
	BYTE ItemLevel;

	PUseItem() : Packet(COMP_OP::OP_USEITEM), UsePlayerSerial(0), Effect(0), ItemLevel(0) { PacketSize = sizeof(PUseItem); }
	PUseItem(BYTE UsePlayerSerial, BYTE Effect, BYTE ItemLevel) :
		Packet(COMP_OP::OP_USEITEM), UsePlayerSerial(UsePlayerSerial), Effect(Effect), ItemLevel(ItemLevel) {
		PacketSize = sizeof(PUseItem);
	}
};

struct PGetItem : Packet
{
	BYTE ItemSerialNum;

	PGetItem() : Packet(COMP_OP::OP_GETITEM), ItemSerialNum(0) { PacketSize = sizeof(PGetItem); }
	PGetItem(BYTE SerialNum) : Packet(COMP_OP::OP_GETITEM), ItemSerialNum(SerialNum) { PacketSize = sizeof(PGetItem); }
};

struct PChangeAnimMontage : Packet
{
	EAnimMontage eAnimMontage;
	BYTE ChangedPlayerSerial;
	BYTE SectionNum;

	PChangeAnimMontage() : Packet(COMP_OP::OP_CHANGEANIMMONTAGE), eAnimMontage(EAnimMontage::Default), ChangedPlayerSerial(0), SectionNum(0)
	{ PacketSize = sizeof(PChangeAnimMontage); }
};

struct PSwapWeapon : Packet
{
	BYTE SwapingPlayer;
	ESwapWeapon SwapWeapon;

	PSwapWeapon() : Packet(COMP_OP::OP_SWAPWEAPON), SwapingPlayer(-1), SwapWeapon(ESwapWeapon::NullWeapon) { PacketSize = sizeof(PSwapWeapon); }
	PSwapWeapon(BYTE id, ESwapWeapon weapon) : Packet(COMP_OP::OP_SWAPWEAPON), SwapingPlayer(id), SwapWeapon(weapon) { PacketSize = sizeof(PSwapWeapon); }
};

struct PBuildingInfo : Packet
{
	BYTE BuildInfo[37];
	BYTE BuildInfoSize;

	PBuildingInfo() : Packet(COMP_OP::OP_BUILDINGINFO), BuildInfoSize(37) { PacketSize = sizeof(PBuildingInfo); }
	PBuildingInfo(BYTE size) : Packet(COMP_OP::OP_BUILDINGINFO), BuildInfoSize(size) { PacketSize = sizeof(PBuildingInfo); }
};

struct PRequestPacket : Packet
{
	COMP_OP RequestOp;

	PRequestPacket() : Packet(COMP_OP::OP_REQUESTPACKET) { PacketSize = sizeof(PRequestPacket); }
	PRequestPacket(COMP_OP op) : Packet(COMP_OP::OP_REQUESTPACKET), RequestOp(op) { PacketSize = sizeof(PRequestPacket); }
};

struct PBreakObject : Packet
{
	EBreakType ObjectType;
	WORD ObjectSerial;
	PVector Direction;

	PBreakObject() : Packet(COMP_OP::OP_BREAKOBJECT), ObjectType(EBreakType::Window), ObjectSerial(0), Direction(PVector()) { PacketSize = sizeof(PBreakObject); }
	PBreakObject(EBreakType type, WORD WindowSerial, PVector Direction) :
		Packet(COMP_OP::OP_BREAKOBJECT), ObjectType(type), ObjectSerial(WindowSerial), Direction(Direction) {	PacketSize = sizeof(PBreakObject);	}
};

struct PTryLogin : Packet
{
	char ID[30];
	char Password[30];
	bool IsRegister;

	PTryLogin() :Packet(COMP_OP::OP_TRYLOGIN) { PacketSize = sizeof(PTryLogin); }
};

struct PLoginResult : Packet
{
	char LoginResult;
	bool IsRegister;

	PLoginResult() :Packet(COMP_OP::OP_LOGINRESULT) { PacketSize = sizeof(PLoginResult); }
};

struct PJoinPlayerInSkillTest : Packet
{
	ECharacter PickedCharacter;
	EMeleeWeapon PickedMeleeWeapon;
	ERangeWeapon PickedRangeWeapon;
	BYTE ClientNum;

	PJoinPlayerInSkillTest() : Packet(COMP_OP::OP_JOINPLAYERINSKILLTEST) { PacketSize = sizeof(PJoinPlayerInSkillTest); }
};
#pragma pack(pop)