// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MainLevelScriptActor.generated.h"

/**
 메인 Level에 대한 Level Blueprint 기능을 LevelScriptActor가 해줌.
 */
UCLASS()
class BASICMULTIPLAYERMELEECOMB_API AMainLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

		void CollapseAll();
};
