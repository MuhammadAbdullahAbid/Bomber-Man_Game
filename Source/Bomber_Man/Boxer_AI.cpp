// Fill out your copyright notice in the Description page of Project Settings.

#include "Boxer_AI.h"
#include "Bomber_ManCharacter.h"
#include "Engine/Engine.h"
#include "Navigation/PathFollowingComponent.h"
#include "Tasks/AITask.h"


// Sets default values
ABoxer_AI::ABoxer_AI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AnimSpeed = 2.0f;

}

// Called when the game starts or when spawned
void ABoxer_AI::BeginPlay()
{
	Super::BeginPlay();
	

}

void ABoxer_AI::Punching()
{
	if (Montage)
	{
		PlayAnimMontage(Montage, AnimSpeed);
	}
}




void ABoxer_AI::MoveToPlayer()
{
	ThirdPersonChar = Cast<ABomber_ManCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (ThirdPersonChar != nullptr)
	{
		
		//AITask->AIMoveTo(AIController,FVector(0.0f,0.0f,0.0f),ThirdPersonChar,50.0f,false);
	}
}

// Called to bind functionality to input
void ABoxer_AI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

