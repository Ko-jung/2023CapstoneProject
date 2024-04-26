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

// USTRUCT()
struct PVector
{
	// GENERATED_BODY()

	float X;
	float Y;
	float Z;
	PVector() { X = Y = Z = 0.f; }
	PVector(float x, float y, float z) { X = x; Y = y; Z = z; }
};

#pragma pack(push, 1)
// USTRUCT()
struct Packet
{
	// GENERATED_BODY()

	BYTE PacketType;
	WORD PacketSize;

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
	float PlayerXDirection;

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

// Send If Character Damaged
// USTRUCT()
struct PChangedPlayerHP : Packet
{
	// GENERATED_BODY()

	BYTE ChangedPlayerSerial;
	float AfterHP;

	PChangedPlayerHP() : Packet(COMP_OP::OP_CHANGEDPLAYERHP), ChangedPlayerSerial(-1), AfterHP(-1.f) { PacketSize = sizeof(PChangedPlayerHP); }
	PChangedPlayerHP(int changedPlayerSerial, float afterHP) : Packet(COMP_OP::OP_CHANGEDPLAYERHP),
		ChangedPlayerSerial(changedPlayerSerial), AfterHP(afterHP) {
		PacketSize = sizeof(PChangedPlayerHP);
	}
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

// USTRUCT()
struct PSpawnObject : Packet, PTransform
{
	// GENERATED_BODY()

	ESkillActor SpawnObject;
	PVector ForwardVec;
	BYTE SerialNum;

	PSpawnObject() : Packet(COMP_OP::OP_SPAWNOBJECT), PTransform(), SerialNum(-1) { SpawnObject = ESkillActor::BP_NULL; Location = PVector{}; PacketSize = sizeof(PSpawnObject); }
	// PSpawnObject(ESkillActor EO, PVector Location, PVector Forward) : Packet(COMP_OP::OP_SPAWNOBJECT), PTransform(Location.X, Location.Y, Location.Z)
	// {
	// 	this->SpawnObject = EO;
	// 	PacketSize = sizeof(PSpawnObject);
	// }
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
	// GENERATED_BODY()

	WORD DisconnectPlayerSerial;

	//PDisconnect() : Packet(COMP_OP::OP_DISCONNECT) { PlayerSerial = -1; }
	PDisconnect(WORD serial) : Packet(COMP_OP::OP_DISCONNECT) {
		DisconnectPlayerSerial = serial; PacketSize = sizeof(PDisconnect);
	}
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

// USTRUCT()
struct PTileDrop : Packet
{
	// GENERATED_BODY()

	PTileDrop() : Packet(COMP_OP::OP_TILEDROP) { }
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

	ECharacterSelect PickedCharacter;
	EMeleeSelect PickedMeleeWeapon;
	ERangeSelect PickedRangeWeapon;
	BYTE ClientNum;

	PPlayerSelectInfo(ECharacterSelect c, EMeleeSelect meele, ERangeSelect range, BYTE sendClientNum) :
		Packet(COMP_OP::OP_SELECTWEAPONINFO),
		PickedCharacter(c),
		PickedMeleeWeapon(meele),
		PickedRangeWeapon(range),
		ClientNum(sendClientNum)
	{
		PacketSize = sizeof(PPlayerSelectInfo);
	}

	PPlayerSelectInfo() : Packet(COMP_OP::OP_SELECTWEAPONINFO),
		PickedCharacter(ECharacterSelect::ECS_Null),
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
	float SecondsUntilActivation;	// ex) ĳ���� ���� â�� ���ѽð� (40s)
	PSetTimer() :Packet(COMP_OP::OP_SETTIMER), TimerType(ETimer::DefaultTimer), SecondsUntilActivation(0.f) { PacketSize = sizeof(PSetTimer); }
	PSetTimer(ETimer type, float secondTime) : Packet(COMP_OP::OP_SETTIMER), TimerType(type), SecondsUntilActivation(secondTime) { PacketSize = sizeof(PSetTimer); }
};

// USTRUCT()
struct PSpawnItem : Packet, PTransform
{
	// GENERATED_BODY()

	int RoomNum;

	PSpawnItem() : Packet(COMP_OP::OP_SPAWNITEM), PTransform(), RoomNum(-1) { PacketSize = sizeof(PSpawnItem); }
	PSpawnItem(PVector Location, PVector Rotate, int Roomnum)
		: Packet(COMP_OP::OP_SPAWNITEM),
		PTransform(Location.X, Location.Y, Location.Z, Rotate.X, Rotate.Y, Rotate.Z), RoomNum(Roomnum)
	{
		PacketSize = sizeof(PSpawnItem);
	}
};

// USTRUCT()
struct PChangeAnimMontage : Packet
{
	// GENERATED_BODY()

	ECharacterAnimMontage eAnimMontage;
	BYTE ChangedPlayerSerial;

	PChangeAnimMontage() : Packet(COMP_OP::OP_CHANGEANIMMONTAGE), eAnimMontage(ECharacterAnimMontage::ECAM_Default), ChangedPlayerSerial(-1)
	{
		PacketSize = sizeof(PChangeAnimMontage);
	}
};

#pragma pack(pop)