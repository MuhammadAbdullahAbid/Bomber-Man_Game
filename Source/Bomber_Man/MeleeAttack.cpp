// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeAttack.h"
#include "AIController.h"


UMeleeAttack::UMeleeAttack()
{
	NodeName = "MeleeDamage";
}

EBTNodeResult::Type UMeleeAttack::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	

	return EBTNodeResult::Type();
}
