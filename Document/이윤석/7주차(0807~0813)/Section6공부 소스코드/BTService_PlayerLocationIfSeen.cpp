

// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "kismet/GameplayStatics.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
	NodeName = TEXT("Update Player Location If Seen");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return;

	APawn* PlayerCharacter = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!PlayerCharacter) return;

	if(AIController->LineOfSightTo(PlayerCharacter))
	{
		AIController->GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerCharacter);
	}
	else
	{
		AIController->GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
	
}

