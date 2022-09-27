// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Collector_AI.h"
#include "FindRandomLocations.generated.h"

/**
 * 
 */
UCLASS()
class BOMBER_MAN_API UFindRandomLocations : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UFindRandomLocations();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	bool IsRandomLocation;

	class ACollector_AI* AICharacter;
	
};
