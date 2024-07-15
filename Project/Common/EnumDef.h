#pragma once

enum class COMP_OP : BYTE
{
	// Default
	OP_RECV,
	OP_SEND,
	OP_ACCEPT,

	// Lobby
	OP_STARTMATCHING,
	OP_CANCLEMATCHING,
	OP_CONNECTTOGAMESERVER,
	OP_TRYLOGIN,			// Using with REGISTER
	OP_LOGINRESULT,

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
	OP_STUNDOWNSTATE,
	OP_SPAWNOBJECT,
	OP_PLAYERJOIN,
	OP_DISCONNECT,
	OP_TILEDROP,
	OP_SPAWNITEM,
	OP_USEITEM,
	OP_GETITEM,
	OP_CHANGEANIMMONTAGE,
	OP_SWAPWEAPON,
	OP_BUILDINGINFO,
	OP_REQUESTPACKET,
	OP_FINISHGAME,
	OP_BREAKOBJECT,
	OP_REMOVEOBJECT,	// 30
	OP_SKILLINTERACT,

	// Skill Sync
	OP_JOINPLAYERINSKILLTEST,

	// Server to Server
	OP_SS_EMPTYROOMNUM,

	//OP_SERVERCLOSE,
};

enum class ESkillActor : BYTE
{
	BP_NULL,
	BP_BoomerangGrab,
	BP_BoomerangCenter,
	BP_DetectorMine,
	BP_DetectorEMP,
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
enum class EMeleeWeapon : BYTE
{
	Dagger,		// 단검
	Katana,		// 카타나
	Greatsword,	// 대검

	// Express '?' on UI
	NullWeapon,
}; 

//원거리
enum class ERangeWeapon : BYTE
{
	SubmachineGun,			// 기관단총
	AssaultRifle,			// 돌격소총
	RPG,		// 유탄발사기

	// Express '?' on UI
	NullWeapon,
};

// 무기교체
enum class ESwapWeapon : BYTE
{
	NullWeapon,	// 맨손
	MeleeWeapon,
	RangeWeapon,
};

// 타이머 이벤트 종류 정의
enum class ETimer : BYTE
{
	DefaultTimer,
	SelectTimer,
	TileDropTimer,
};

enum class ECharacterState : BYTE
{
	LIVING,
	DYING,
	DEAD,
	INVINCIBILITY, // GODMODE
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

enum class EItemEffect : BYTE
{
	NONE = 0,
	Single_BoostBulletInfinity,
	Single_GodMode,
	Team_PlusHealth,
	Team_Power,
	Team_Speed,
	COUNT
};

enum class EItemRareLevel : BYTE
{
	NONE = 0,
	Normal,
	Rare,
	Legend,
	COUNT
};

enum class EObjectType : BYTE
{
	Window,

	SkillActor,
};

enum class ELoginResult : char
{
	Success = 0,
	DatabaseError = -1,
	IDError = 1,
	PasswordError = 2,
};