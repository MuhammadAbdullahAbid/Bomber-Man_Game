// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy_AIController.h"
#include "Bomber_ManCharacter.h"
#include "Tasks/AITask.h"
#include "Boxer_AI.generated.h"

UCLASS()
class BOMBER_MAN_API ABoxer_AI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABoxer_AI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* Montage;

	UFUNCTION(BlueprintCallable, Category = "Functions")
		void Punching();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		float AnimSpeed;

	class ABomber_ManCharacter* ThirdPersonChar;

	class AEnemy_AIController* AIController;

	class UAITask* AITask;
	
	
	void MoveToPlayer();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
