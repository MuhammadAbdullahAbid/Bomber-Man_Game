// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Collector_AI.generated.h"

UCLASS()
class BOMBER_MAN_API ACollector_AI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACollector_AI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
