// Fill out your copyright notice in the Description page of Project Settings.


#include "ChasePlayer.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AITypes.h"

UChasePlayer::UChasePlayer()
{
	NodeName = TEXT("Chase Player Task");
}
EBTNodeResult::Type UChasePlayer::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp,NodeMemory);

	FVector TargetedLocation;
	 OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(),TargetedLocation);

	FAIMoveRequest AIMoveReq;
	AIMoveReq.SetGoalLocation(TargetedLocation);
	OwnerComp.GetAIOwner()->MoveTo(TargetedLocation);

	return EBTNodeResult::Succeeded;
}
