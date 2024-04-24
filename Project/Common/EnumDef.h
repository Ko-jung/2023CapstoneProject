#pragma once

enum class COMP_OP : unsigned char
{
	// Default
	OP_RECV,
	OP_SEND,
	OP_ACCEPT,

	// Lobby
	OP_STARTMATCHING,
	OP_CANCLEMATCHING,
	OP_CONNECTTOGAMESERVER,

	// Select
	OP_STARTGAME,
	OP_SELECTWEAPONINFO,
	OP_SETTIMER,

	//Main
	OP_POSITION,
	OP_PLAYERPOSITION,
	OP_DAMAGEDPLAYER,
	OP_CHANGEDPLAYERHP,
	OP_CHANGEDPLAYERSTATE,
	OP_SPAWNOBJECT,
	OP_PLAYERJOIN,
	OP_DISCONNECT,
	OP_TILEDROP,
	OP_SPAWNITEM,
	OP_CHANGEANIMMONTAGE,

	// Server to Server
	OP_SS_EMPTYROOMNUM,

	//OP_SERVERCLOSE,
};

enum class EObject : unsigned char
{
	BP_NULL,
	BP_BoomerangGrab,
	BP_BoomerangCenter,
	BP_DetectorMine,
	BP_Shield,
	BP_ShieldSphere,
	BP_ShieldSphereThrow,
	BP_WindTornado,
	BP_ElectSphereBoom,
	BP_ElectTrap,
};

enum class ECharacter : char
{
	// Express '?' on UI
	NullCharacter = -1,

	Shield = 0,
	Wind,
	Elect,
	Boomerang,
	Assassin,
	Detector,
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
	RPG,		// 유탄발사기

	// Express '?' on UI
	NullWeapon,
};

// 타이머 이벤트 종류 정의
enum class ETimer : BYTE
{
	DefaultTimer,
	SelectTimer,
};

enum class ECharacterState : BYTE
{
	LIVING,
	DYING,
	DEAD
};

enum class EAnimMontage : BYTE
{
	Default,

	DaggerAttack,
	KatanaAttack,
	GreatSwordAttack,
	SMG,
	Rifle,
	RPG,

	Stun,
	Down,
	Death
};