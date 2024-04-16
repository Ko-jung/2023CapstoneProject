#pragma once

UENUM()
enum class ECharacterAnimMontage
{
	ECAM_Default = 0,
	ECAM_DaggerAttack,
	ECAM_KatanaAttack,
	ECAM_GreatSwordAttack,
	ECAM_SMGReadyFire, ECAM_SMGFire, ECAM_SMGReload,
	ECAM_RifleReadyFire, ECAM_RifleFire, ECAM_RifleReload,
	ECAM_RPGReadyFire, ECAM_RPGFire, ECAM_RPGReload, 
	ECAM_Stiffness, ECAM_Down,
	ECAM_Stiffness_Bwd, ECAM_Down_Bwd

};