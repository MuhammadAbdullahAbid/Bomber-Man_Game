// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class BOMBER_MAN_API UMeleeAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
		UMeleeAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
};
