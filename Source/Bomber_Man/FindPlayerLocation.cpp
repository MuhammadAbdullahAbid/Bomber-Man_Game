// Fill out your copyright notice in the Description page of Project Settings.


#include "FindPlayerLocation.h"
#include "Enemy_AIController.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/Navigation/NavigationTypes.h"

UFindPlayerLocation::UFindPlayerLocation()
{
	NodeName = TEXT("Find Player Location Task");

}
EBTNodeResult::Type UFindPlayerLocation::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	FNavLocation RandomLocation;

	UNavigationSystemV1* Navigation_Sys=UNavigationSystemV1::GetNavigationSystem(GetWorld());

	RandomPoint = Navigation_Sys->GetRandomPointInNavigableRadius(UGameplayStatics::GetPlayerPawn(GetWorld(),0)->GetActorLocation(),100.0f,RandomLocation,NULL,NULL);

	if (RandomPoint)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), RandomLocation.Location);
		return EBTNodeResult::Succeeded;
	}


	return EBTNodeResult::Failed;
}
