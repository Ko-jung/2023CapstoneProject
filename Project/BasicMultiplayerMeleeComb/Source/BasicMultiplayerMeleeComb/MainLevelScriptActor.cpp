// Fill out your copyright notice in the Description page of Project Settings.


#include "MainLevelScriptActor.h"

void AMainLevelScriptActor::CollapseAll()
{
	if (GetWorld()->GetFirstPlayerController()->WasInputKeyJustPressed(EKeys::O))
	{
		UE_LOG(LogTemp, Warning, TEXT("된다!"));
	}
}
