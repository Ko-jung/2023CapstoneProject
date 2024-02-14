#pragma once

enum class COMP_OP
{
	OP_RECV,
	OP_SEND,
	OP_ACCEPT,

	OP_POSITION,
	OP_OBJECTSPAWN,
	OP_PLAYERJOIN,
};

enum class EObject : unsigned char
{
	BP_Cube,
};