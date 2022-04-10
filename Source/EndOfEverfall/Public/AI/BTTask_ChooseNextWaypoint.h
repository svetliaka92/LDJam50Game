// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ChooseNextWaypoint.generated.h"

/**
 * 
 */
UCLASS()
class ENDOFEVERFALL_API UBTTask_ChooseNextWaypoint : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_ChooseNextWaypoint();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector IndexKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector WaypointKey;
};
