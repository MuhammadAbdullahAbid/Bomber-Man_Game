// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"

#include "FocusPlayer.generated.h"

/**
 * 
 */
UCLASS()
class BOMBER_MAN_API UFocusPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

		UFocusPlayer();
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Player;
	
	
};
