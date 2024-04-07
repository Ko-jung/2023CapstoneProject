// Fill out your copyright notice in the Description page of Project Settings.


#include "DoubleTab_InputTrigger.h"

#include "EnhancedPlayerInput.h"		// PlayerInput

ETriggerState UDoubleTab_InputTrigger::UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime)
{
	Super::UpdateState_Implementation(PlayerInput, ModifiedValue, DeltaTime);
	if (IsActuated(ModifiedValue)  && !IsActuated(LastValue))
	{
		// Get Current Time
		const float CurrentTime = PlayerInput->GetWorld()->GetTimeSeconds();

		// If input again in limit time, Return Triggered
		if (CurrentTime - LastInputTime < TimeLimit)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Direction - %f %f"), ModifiedValue.Get<FVector2D>().X, ModifiedValue.Get<FVector2D>().Y);
			LastInputTime = 0.0f;
			return ETriggerState::Triggered;
		}

		LastInputTime = CurrentTime;

	}

	return ETriggerState::None;
}

