// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"
#include "TimerManager.h"
#include "Boxer_AI.h"

AEnemy_AIController::AEnemy_AIController()
{
	Sight_Sense = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Sense"));
	AIPerceptionComponent=CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	Sight_Sense->SightRadius = AISightRadius;
	Sight_Sense->LoseSightRadius = AILoseSightRadius;
	Sight_Sense->PeripheralVisionAngleDegrees = AIFieldofView;
	Sight_Sense->SetMaxAge(AISightAge);

	Sight_Sense->DetectionByAffiliation.bDetectEnemies = true;
	Sight_Sense->DetectionByAffiliation.bDetectFriendlies = true;
	Sight_Sense->DetectionByAffiliation.bDetectNeutrals = true;


	AIPerceptionComponent->ConfigureSense(*Sight_Sense);
	
	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AEnemy_AIController::OnPlayerDetected);
	AIPerceptionComponent->SetComponentTickInterval(0.05f);

	
}
void AEnemy_AIController::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<AActor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	GetBlackboardComponent()->SetValueAsEnum(FName("AIState"), AIState::Holding);
	GetWorldTimerManager().SetTimer(TimerHandler, this,&AEnemy_AIController::SetAIAttackState, FMath::FRandRange(1.0f, 3.0f));

	
}

void AEnemy_AIController::OnPlayerDetected(const TArray<AActor*>& DetectedPawn)
{
	for (int32 x = 0; x < DetectedPawn.Num(); x++)
	{
		if (UGameplayStatics::GetPlayerPawn(GetWorld(), 0) == DetectedPawn[x])
		{
			FActorPerceptionBlueprintInfo Stimuli;
			AIPerceptionComponent->GetActorsPerception(DetectedPawn[x], Stimuli);
			for (int32 y = 0; y < Stimuli.LastSensedStimuli.Num(); y++)
			{
					OnSight(&Stimuli);
			}
		}
	}
}

void AEnemy_AIController::OnSight(FActorPerceptionBlueprintInfo * Stimuli)
{
	if (Stimuli->LastSensedStimuli[0].WasSuccessfullySensed())
	{
		GetBlackboardComponent()->SetValueAsBool(FName("CanSeePlayer"), Stimuli->LastSensedStimuli[0].WasSuccessfullySensed());

		GetBlackboardComponent()->SetValueAsVector(FName("TargetLocation"), Stimuli->LastSensedStimuli[0].StimulusLocation);
	}
}

void AEnemy_AIController::SetAIAttackState()
{
	GetBlackboardComponent()->SetValueAsEnum(FName("AIState"), AIState::Attacking);
}



