// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"

#include "EngineUtils.h"
#include "ShooterAIController.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);
	
	TObjectPtr<APlayerController> PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController)
	{
		EndGame(false);
	}

	// For Loop Over ShooterAI In World
		// Is Not Dead?
			// Return
	for(AShooterAIController* AIController : TActorRange<AShooterAIController>(GetWorld()))
	{
		if (!AIController->IsDead())
			return;
	}
	//All AI Die
		//End Game
	EndGame(true);

}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
	for(AController* Controller : TActorRange<AController>(GetWorld()))
	{
		/*bool bIsPlayerController = Controller->IsPlayerController();
		if(bIsPlayerWinner)
		{
			Controller->GameHasEnded(nullptr, bIsPlayerController);
		}
		else
		{
			Controller->GameHasEnded(nullptr, !bIsPlayerController);
		}*/
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}
