// Fill out your copyright notice in the Description page of Project Settings.


#include "FindRandomLocations.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "Collector_AI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/Navigation/NavigationTypes.h"

UFindRandomLocations::UFindRandomLocations()
{
	NodeName = TEXT("Find Random Location Task");
}

EBTNodeResult::Type UFindRandomLocations::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	FNavLocation RandomLocations;

	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	IsRandomLocation = NavSys->GetRandomPointInNavigableRadius(AICharacter->GetActorLocation(), 1500.0f, RandomLocations, NULL, NULL);
	
	if (IsRandomLocation)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), RandomLocations.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
