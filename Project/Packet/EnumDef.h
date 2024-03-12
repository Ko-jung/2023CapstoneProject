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

	OP_SS_SENDPLAYERSOCKETS,
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