// Fill out your copyright notice in the Description page of Project Settings.


#include "FocusPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"

#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"

UFocusPlayer::UFocusPlayer()
{
	NodeName = "Focus Player";
}

EBTNodeResult::Type UFocusPlayer::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	Player = Cast<AActor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	OwnerComp.GetAIOwner()->SetFocus(Player, EAIFocusPriority::Default);
	


	return EBTNodeResult::Succeeded;
}
