// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enemy_AIController.generated.h"

struct FActorPerceptionBlueprintInfo;

UENUM(BlueprintType)

enum AIState
{
	Holding, Attacking, Recovery
};

UCLASS()
class BOMBER_MAN_API AEnemy_AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemy_AIController();

	virtual void BeginPlay() override;
	UFUNCTION()
		void OnPlayerDetected(const TArray<AActor*>& DetectedPawn);

	void OnSight(FActorPerceptionBlueprintInfo* Stimuli);

	void SetAIAttackState();

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class  UAISenseConfig_Sight* Sight_Sense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float AISightRadius = 3000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float AISightAge = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float AILoseSightRadius = AISightRadius + 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float AIFieldofView = 180.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	    AActor* Player;


	FTimerHandle TimerHandler;

};
