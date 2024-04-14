#pragma once

UENUM()
enum class ECharacterAnimMontage
{
	ECAM_Default = 0,
	ECAM_DaggerAttack1, ECAM_DaggerAttack2, ECAM_DaggerAttack3, ECAM_DaggerAttack4, ECAM_DaggerAttack5,
	ECAM_KatanaAttack1, ECAM_KatanaAttack2, ECAM_KatanaAttack3, ECAM_KatanaAttack4,
	ECAM_GreatSwordAttack1, ECAM_GreatSwordAttack2, ECAM_GreatSwordAttack3,
	ECAM_SMGReadyFire, ECAM_SMGFire, ECAM_SMGReload,
	ECAM_RifleReadyFire, ECAM_RifleFire, ECAM_RifleReload,
	ECAM_RPGReadyFire, ECAM_RPGFire, ECAM_RPGReload, 
	ECAM_Stiffness, ECAM_Down,

};