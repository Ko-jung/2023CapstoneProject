// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "ESkillActor.generated.h"

UENUM(BlueprintType)
enum class ESkillActor : uint8
{
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

/**
 * 
 */
//UCLASS()
//class SKYSCRAPER_API UESkillActor : public UUserDefinedEnum
//{
//	GENERATED_BODY()
//	
//};
