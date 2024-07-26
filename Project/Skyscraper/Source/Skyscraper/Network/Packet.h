// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"

#include "../Enum/EOperator.h"
#include "../Enum/EHealthState.h"
#include "../Enum/ESkillActor.h"
#include "../Enum/ECharacterSelect.h"
#include "../Enum/EMeleeSelect.h"
#include "../Enum/ERangeSelect.h"
#include "../Enum/ETimer.h"
#include "../Enum/ECharacterAnimMontage.h"
#include "../Enum/ESwapWeapon.h"
#include "../Enum/EBreakType.h"
#include "../Enum/ELoginResult.h"

// USTRUCT()
struct PVector
{
	// GENERATED_BODY()

	float X;
	float Y;
	float Z;
	PVector() { X = Y = Z = 0.f; }
	PVector(float x, float y, float z) { X = x; Y = y; Z = z; }

	// Unreal Code
	PVector(FVector vector) { X = vector.X; Y = vector.Y; Z = vector.Z; }
	PVector(FRotator vector) { X = vector.Pitch; Y = vector.Yaw; Z = vector.Roll; }
};

#pragma pack(push, 1)
// USTRUCT()
struct Packet
{
	// GENERATED_BODY()

	BYTE PacketSize;
	BYTE PacketType;

	Packet() :PacketType((int)COMP_OP::OP_RECV) { PacketSize = sizeof(Packet); }
	Packet(COMP_OP op) : PacketType((int)op) { PacketSize = sizeof(Packet); }
};

// USTRUCT()
struct PTransform
{
	// GENERATED_BODY()

public:
	PVector Location;

	PVector Rotate;

	PTransform() { Location.X = Location.Y = Location.Z = Rotate.X = Rotate.Y = Rotate.Z = 0.f; }
	PTransform(float x, float y, float z) : Location{ x, y, z } { Rotate = PVector{}; }
	PTransform(float x, float y, float z, float rx, float ry, float rz)
		: Location{ x, y, z }, Rotate{ rx, ry, rz } {}
};

// USTRUCT()
struct PPlayerPosition : Packet, PTransform
{
	// GENERATED_BODY()

	BYTE PlayerSerial;
	float PlayerSpeed;
	//float PlayerXDirection;
	PVector ControllerRotator;

	// EPlayerState PlayerState;

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

// USTRUCT()
struct PDamagedPlayer : Packet
{
	// GENERATED_BODY()

	BYTE ChangedPlayerSerial;
	bool IsMelee;
	char WeaponEnum;

	PDamagedPlayer() : Packet(COMP_OP::OP_DAMAGEDPLAYER), ChangedPlayerSerial(-1), IsMelee(true), WeaponEnum(-1) { PacketSize = sizeof(PDamagedPlayer); }
	PDamagedPlayer(BYTE serial, bool isMelee, char weaponEnum) : Packet(COMP_OP::OP_DAMAGEDPLAYER),
		ChangedPlayerSerial(serial), IsMelee(isMelee), WeaponEnum(weaponEnum) {
		PacketSize = sizeof(PDamagedPlayer);
	}
};

struct PDamagedSkillActor : Packet
{
	BYTE SkillActorOwner;
	ESkillActor SkillActor;
	WORD SkillActorSerial;
	bool IsMelee;
	char WeaponEnum;

	PDamagedSkillActor() : Packet(COMP_OP::OP_DAMAGEDSKILLACTOR), SkillActorOwner(0), SkillActor(ESkillActor::BP_NULL),
		SkillActorSerial(0), IsMelee(false), WeaponEnum(0) { PacketSize = sizeof(PDamagedSkillActor); }
};

// Send If Character Damaged
// USTRUCT()
struct PChangedPlayerHP : Packet
{
	// GENERATED_BODY()

	BYTE AttackerSerial;
	BYTE ChangedPlayerSerial;
	float AfterHP;

	PChangedPlayerHP() : Packet(COMP_OP::OP_CHANGEDPLAYERHP), AttackerSerial(0),ChangedPlayerSerial(-1), AfterHP(-1.f) { PacketSize = sizeof(PChangedPlayerHP); }
	PChangedPlayerHP(int changedPlayerSerial, float afterHP) : Packet(COMP_OP::OP_CHANGEDPLAYERHP),
		ChangedPlayerSerial(changedPlayerSerial), AfterHP(afterHP) {
		PacketSize = sizeof(PChangedPlayerHP);
	}
};

struct PChangedSkillActorHP : Packet
{
	BYTE ChangedSkillActorOwner;
	BYTE ChangedSkillActorSerial;
	float AfterHP;

	PChangedSkillActorHP() : Packet(COMP_OP::OP_CHANGEDSKILLACTORHP), ChangedSkillActorOwner(0), ChangedSkillActorSerial(-1), AfterHP(-1.f) { PacketSize = sizeof(PChangedSkillActorHP); }
};

// Send If Character Dead or ReSpawn
// USTRUCT()
struct PChangedPlayerState : Packet
{
	// GENERATED_BODY()

	BYTE ChangedPlayerSerial;
	EHealthState State;

	PChangedPlayerState() : Packet(COMP_OP::OP_CHANGEDPLAYERSTATE), ChangedPlayerSerial(-1), State(EHealthState::EHS_LIVING) { PacketSize = sizeof(PChangedPlayerState); }
	PChangedPlayerState(int serial, EHealthState state) :
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
	PStunDownState(BYTE targetNum, FVector direction, float stunTime, bool isStun)
		: Packet(COMP_OP::OP_STUNDOWNSTATE), TargetSerialNum(targetNum), StunTime(stunTime), IsStun(isStun)
	{
		Direction.X = (float)direction.X; 
		Direction.Y = (float)direction.Y; 
		Direction.Z = (float)direction.Z;
		PacketSize = sizeof(PStunDownState);
	}
};

// USTRUCT()
struct PSpawnObject : Packet, PTransform
{
	// GENERATED_BODY()
	ESkillActor SpawnObject;
	PVector ForwardVec;
	WORD SerialNum;
	BYTE ObjectSpawner;

	PSpawnObject() : Packet(COMP_OP::OP_SPAWNOBJECT), PTransform(), SpawnObject(ESkillActor::BP_NULL), SerialNum(-1), ObjectSpawner(-1)
	{ PacketSize = sizeof(PSpawnObject); }
};

// USTRUCT()
struct PPlayerJoin : Packet
{
	// GENERATED_BODY()

	BYTE PlayerSerial;

	PPlayerJoin() : Packet(COMP_OP::OP_PLAYERJOIN) { PlayerSerial = -1; PacketSize = sizeof(PPlayerJoin); }
	PPlayerJoin(BYTE serial) : Packet(COMP_OP::OP_PLAYERJOIN) { PlayerSerial = serial; PacketSize = sizeof(PPlayerJoin); }
};

// USTRUCT()
struct PDisconnect : Packet
{
	PDisconnect() : Packet(COMP_OP::OP_DISCONNECT) { PacketSize = sizeof(PDisconnect); }
	//PDisconnect(WORD serial) : Packet(COMP_OP::OP_DISCONNECT) {
	//	DisconnectPlayerSerial = serial; PacketSize = sizeof(PDisconnect);
	//}
};

// USTRUCT()
struct PStartMatching : Packet
{
	// GENERATED_BODY()

	PStartMatching() : Packet(COMP_OP::OP_STARTMATCHING) { PacketSize = sizeof(PStartMatching); }
};

// USTRUCT()
struct PCancleMatching : Packet
{
	// GENERATED_BODY()

	PCancleMatching() : Packet(COMP_OP::OP_CANCLEMATCHING) { }
};

// USTRUCT()
struct PStartGame : Packet
{
	// GENERATED_BODY()

	PStartGame() : Packet(COMP_OP::OP_STARTGAME) { }
};

struct PFinishGame : Packet
{
	bool IsTeamAWin;
	PFinishGame() : Packet(COMP_OP::OP_FINISHGAME), IsTeamAWin(false) { PacketSize = sizeof(PFinishGame); }
	PFinishGame(bool winner) : Packet(COMP_OP::OP_FINISHGAME), IsTeamAWin(winner) { PacketSize = sizeof(PFinishGame); }
};

// USTRUCT()
struct PTileDrop : Packet
{
	BYTE TileDropLevel;
	BYTE CenterIndex;
	PTileDrop() : Packet(COMP_OP::OP_TILEDROP), TileDropLevel(0), CenterIndex(0) { PacketSize = sizeof(PTileDrop); }
	PTileDrop(BYTE TileDropLevel, BYTE CenterIndex) : Packet(COMP_OP::OP_TILEDROP), TileDropLevel(TileDropLevel), CenterIndex(CenterIndex)
	{ PacketSize = sizeof(PTileDrop); }
};

// contained room num in RoomNum
// USTRUCT()
struct PConnectToGameserver : Packet
{
	// GENERATED_BODY()

	PConnectToGameserver() : Packet(COMP_OP::OP_CONNECTTOGAMESERVER) {  }
};

// USTRUCT()
struct PPlayerSelectInfo : Packet
{
	// GENERATED_BODY()

	BYTE PickedCharacter;
	//ECharacterSelect PickedCharacter;
	EMeleeSelect PickedMeleeWeapon;
	ERangeSelect PickedRangeWeapon;
	BYTE ClientNum;

	PPlayerSelectInfo(ECharacterSelect c, EMeleeSelect meele, ERangeSelect range, BYTE sendClientNum) :
		Packet(COMP_OP::OP_SELECTWEAPONINFO),
		PickedCharacter((BYTE)c),
		PickedMeleeWeapon(meele),
		PickedRangeWeapon(range),
		ClientNum(sendClientNum)
	{
		PacketSize = sizeof(PPlayerSelectInfo);
	}

	PPlayerSelectInfo() : Packet(COMP_OP::OP_SELECTWEAPONINFO),
		PickedCharacter((BYTE)ECharacterSelect::ECS_Null),
		PickedMeleeWeapon(EMeleeSelect::EMS_NONE),
		PickedRangeWeapon(ERangeSelect::ERS_NONE),
		ClientNum(-1)
	{
		PacketSize = sizeof(PPlayerSelectInfo);
	}
};

// USTRUCT()
struct PSetTimer : Packet
{
	// GENERATED_BODY()

	ETimer TimerType;
	float SecondsUntilActivation;	// ex) 캐릭터 선택 창의 제한시간 (40s)
	PSetTimer() :Packet(COMP_OP::OP_SETTIMER), TimerType(ETimer::DefaultTimer), SecondsUntilActivation(0.f) { PacketSize = sizeof(PSetTimer); }
	PSetTimer(ETimer type, float secondTime) : Packet(COMP_OP::OP_SETTIMER), TimerType(type), SecondsUntilActivation(secondTime) { PacketSize = sizeof(PSetTimer); }
};

// USTRUCT()
struct PItemInfo
{
	BYTE ItemSerialNum;
	BYTE TileIndex;
	BYTE Floor;
	BYTE Effect;
	BYTE ItemLevel;

	PItemInfo() {};
	PItemInfo(BYTE ItemSerialNum, BYTE TileIndex, BYTE Floor, BYTE Effect, BYTE ItemLevel) :
		ItemSerialNum(ItemSerialNum), TileIndex(TileIndex), Floor(Floor), Effect(Effect), ItemLevel(ItemLevel) {}
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
		Packet(COMP_OP::OP_USEITEM), UsePlayerSerial(UsePlayerSerial), Effect(Effect), ItemLevel(ItemLevel) { PacketSize = sizeof(PUseItem); }
};

struct PGetItem : Packet
{
	BYTE ItemSerialNum;

	PGetItem() : Packet(COMP_OP::OP_GETITEM), ItemSerialNum(0) { PacketSize = sizeof(PGetItem); }
	PGetItem(BYTE SerialNum) : Packet(COMP_OP::OP_GETITEM), ItemSerialNum(SerialNum) { PacketSize = sizeof(PGetItem); }
};

// USTRUCT()
struct PChangeAnimMontage : Packet
{
	// GENERATED_BODY()

	ECharacterAnimMontage eAnimMontage;
	BYTE ChangedPlayerSerial;
	BYTE SectionNum;

	PChangeAnimMontage() : Packet(COMP_OP::OP_CHANGEANIMMONTAGE), eAnimMontage(ECharacterAnimMontage::ECAM_Default), ChangedPlayerSerial(0), SectionNum(0)
	{
		PacketSize = sizeof(PChangeAnimMontage);
	}
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
	EObjectType ObjectType;
	WORD ObjectSerial;
	int ObjectSerialChildIndex;
	PVector Direction;

	PBreakObject() : Packet(COMP_OP::OP_BREAKOBJECT), ObjectType(EObjectType::Window), ObjectSerial(0), ObjectSerialChildIndex(0), Direction(PVector()) { PacketSize = sizeof(PBreakObject); }
	PBreakObject(EObjectType type, WORD WindowSerial, PVector Direction) :
		Packet(COMP_OP::OP_BREAKOBJECT), ObjectType(type), ObjectSerial(WindowSerial), Direction(Direction)
	{ PacketSize = sizeof(PBreakObject); }
};

struct PRemoveObject : Packet
{
	EObjectType ObjectType;
	WORD ObjectSerial;
	PVector ObjectLocation;

	PRemoveObject() : Packet(COMP_OP::OP_REMOVEOBJECT), ObjectType(EObjectType::SkillActor), ObjectSerial(0), ObjectLocation(PVector())
	{ PacketSize = sizeof(PRemoveObject); }
};

struct PSkillInteract : Packet
{
	ESkillActor SkillActor;
	BYTE InteractedPlayerSerial;

	PSkillInteract() : Packet(COMP_OP::OP_SKILLINTERACT), InteractedPlayerSerial(0)
	{ PacketSize = sizeof(PSkillInteract); }
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
	ECharacterSelect PickedCharacter;
	EMeleeSelect PickedMeleeWeapon;
	ERangeSelect PickedRangeWeapon;
	BYTE ClientNum;

	PJoinPlayerInSkillTest() : Packet(COMP_OP::OP_JOINPLAYERINSKILLTEST) { PacketSize = sizeof(PJoinPlayerInSkillTest); }
};

struct PPlayerID : Packet
{
	char IDs[6][30];

	PPlayerID() :Packet(COMP_OP::OP_PLAYERID) { memset(&IDs, 0, sizeof(IDs)); PacketSize = sizeof(PPlayerID); }
};
#pragma pack(pop)