#pragma once

UENUM(BlueprintType)
enum class ECharacterAnimMontage : uint8
{
	ECAM_Default = 0,
	ECAM_DaggerAttack,
	ECAM_KatanaAttack,
	ECAM_GreatSwordAttack,
	ECAM_SMG,
	ECAM_Rifle,
	ECAM_RPG,
	ECAM_Stun, ECAM_Down,
	ECAM_Death,
	ECAM_Boost,
	ECAM_Interaction,

	// 2019180016
	ECAM_CommonSkill,
	ECAM_SpecialSkill,
	// ==========
};