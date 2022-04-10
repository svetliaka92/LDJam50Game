// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "BaseShade.h"
#include "ShadePatrolRoute.h"


UBTTask_ChooseNextWaypoint::UBTTask_ChooseNextWaypoint()
{
	NodeName = TEXT("Choose next waypoint");
}


EBTNodeResult::Type UBTTask_ChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	UShadePatrolRoute* PatrolRoute = ControlledPawn->FindComponentByClass<UShadePatrolRoute>();

	if (!IsValid(PatrolRoute))
	{
		return EBTNodeResult::Failed;
	}

	TArray<AActor*> PatrolPoints = PatrolRoute->GetPatrolPath();
	if (PatrolPoints.Num() == 0)
	{
		return EBTNodeResult::Failed;
	}

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	int32 Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

	// cycle index
	int32 NextIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	return EBTNodeResult::Succeeded;
}
