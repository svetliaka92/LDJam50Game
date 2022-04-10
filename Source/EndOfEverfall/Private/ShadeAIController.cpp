// Fill out your copyright notice in the Description page of Project Settings.


#include "ShadeAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


void AShadeAIController::BeginPlay()
{
	if (AIBehavior)
	{
		RunBehaviorTree(AIBehavior);
	}
}
