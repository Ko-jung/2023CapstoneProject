#pragma once

enum class COMP_OP
{
	OP_RECV,
	OP_SEND,
	OP_ACCEPT,

	OP_POSITION,
	OP_PLAYERPOSITION,
	OP_OBJECTSPAWN,
	OP_PLAYERJOIN,
	OP_DISCONNECT,
	OP_STARTMATCHING,
	OP_CANCLEMATCHING,
	OP_STARTGAME,
	OP_TILEDROP,
	OP_PICKCHARACTER,

	OP_SS_SENDPLAYERSOCKETS,
	OP_SS_CONNECTTOGAMESERVER,
};

enum class EObject : unsigned char
{
	BP_Cube,
	BP_Player,
};

enum class EPlayerState : unsigned char
{
	Stay,
	Walk,
	Run,
	Jump,
};

enum class ECharacter : unsigned char
{
	Assassin,
	Boomerang,
	Detecter,
	Elect,
	Shield,
	Wind,
	NullCharacter,
};

enum class EWeapon
{
	// 근거리
	Melee,

	//원거리
	Range,
};