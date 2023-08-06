// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	if(AIBehaviorTree)
	{
		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		RunBehaviorTree(AIBehaviorTree);
		GetBlackboardComponent()->SetValueAsVector(FName("StartLocation"), GetPawn()->GetActorLocation());
	}
	
}

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	//if (LineOfSightTo(PlayerPawn))
	//{
	//	//Setting PlayerLocation
	//	GetBlackboardComponent()->SetValueAsVector(FName("PlayerLocation"), UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation());
	//	//Setting LastKnownPlayerLocation
	//	//GetBlackboardComponent()->SetValueAsVector(FName("LastKnownPlayerLocation"), UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation());
	//}
	//else
	//{
	//	//Clear PlayerLocation
	//	GetBlackboardComponent()->ClearValue(FName("PlayerLocation"));
	//}

}
