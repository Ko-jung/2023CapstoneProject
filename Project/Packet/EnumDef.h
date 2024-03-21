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
	OP_CONNECTTOGAMESERVER,

	//OP_SS_SENDPLAYERSOCKETS,
	OP_SS_EMPTYROOMNUM,
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

	// Express '?' on UI
	NullCharacter,
};

// 근거리
enum class EMeleeWeapon : unsigned char
{
	Dagger,		// 단검
	Katana,		// 카타나
	Greatsword,	// 대검

	// Express '?' on UI
	NullWeapon,
}; 

//원거리
enum class ERangeWeapon : unsigned char
{
	SubmachineGun,			// 기관단총
	AssaultRifle,			// 돌격소총
	GrenadeLauncher,		// 유탄발사기
	
	// Express '?' on UI
	NullWeapon,
};