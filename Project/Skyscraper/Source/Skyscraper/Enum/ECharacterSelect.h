#pragma once
UENUM()
enum class ECharacterSelect : int8
{
	ECS_Null=-1,
	ECS_ShieldCharacter = 0, ECS_WindCharacter,
	ECS_ElectricCharacter, ECS_BoomerangCharacter,
	ECS_AssassinCharacter, ECS_DetectionCharacter
};