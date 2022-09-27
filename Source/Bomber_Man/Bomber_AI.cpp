// Fill out your copyright notice in the Description page of Project Settings.
#include "Bomber_AI.h"
#include "Components/SceneComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/ArrowComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABomber_AI::ABomber_AI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	

	
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	Scene->SetupAttachment(RootComponent);

	
	Force = 1000.0f;
	
	

	

}

// Called when the game starts or when spawned
void ABomber_AI::BeginPlay()
{
	Super::BeginPlay();
	
}



void ABomber_AI::SpawnBomb()
{
	
	

	ActorToSpawn = GetWorld()->SpawnActor<AActor>(Timebomb, Scene->GetRelativeLocation() , Scene->GetRelativeRotation());

	if (ActorToSpawn != nullptr)
	{
		ActorToSpawn->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("BombAttachment"));
// 
// 		LaunchProjectile->SetVelocityInLocalSpace(ForwardVector*Force);
// 		LaunchProjectile->Activate();
   
	}

}

void ABomber_AI::ThrowBomb()
{
	const FVector ForwardVector = UKismetMathLibrary::GetForwardVector(GetControlRotation());
	if (ActorToSpawn!=nullptr)
	{
		ActorToSpawn->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);

		UPrimitiveComponent* PrimComponent = Cast < UPrimitiveComponent>(ActorToSpawn->GetComponentByClass(UPrimitiveComponent::StaticClass()));

		if (PrimComponent != nullptr)
		{
			PrimComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			PrimComponent->SetSimulatePhysics(true);
			PrimComponent->SetAllPhysicsLinearVelocity(ForwardVector*Force, false);
		}
	}
}

// Called to bind functionality to input
void ABomber_AI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

