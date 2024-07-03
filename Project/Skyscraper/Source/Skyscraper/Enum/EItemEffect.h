#pragma once

UENUM()
enum class EItemEffect : uint8
{
	EIE_NONE = 0,
	EIE_Single_BoostBulletInfinity,
	EIE_Single_GodMode,
	EIE_Team_PlusHealth,
	EIE_Team_Power,
	EIE_Team_Speed,
	EIE_Gravity_Up,
	EIE_Gravity_Down,
	EIE_Tile_Break,
	EIE_COUNT
};