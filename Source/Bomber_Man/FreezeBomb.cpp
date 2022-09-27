// Fill out your copyright notice in the Description page of Project Settings.


#include "FreezeBomb.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementReplication.h"
#include "GameFramework/Character.h"
#include "Bomber_ManCharacter.h"
#include "Components/SphereComponent.h"

// Sets default values
AFreezeBomb::AFreezeBomb()
{
	BombMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = BombMesh;
	BombMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	BombMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereCollision->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	SphereCollision->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	SphereCollision->SetupAttachment(BombMesh, NAME_None);
	
}

// Called when the game starts or when spawned
void AFreezeBomb::BeginPlay()
{
	Super::BeginPlay();

	
	GetWorld()->GetTimerManager().SetTimer(timeHandle, this, &AFreezeBomb::ExplodeBomb, 5.0f);


	

	

}

void AFreezeBomb::enable_Input(ABomber_ManCharacter * charc)
{
	
	UE_LOG(LogTemp, Warning, TEXT("Enable Input "));
	charc->GetMesh()->bPauseAnims = false;
	
}

void AFreezeBomb::Hello()
{
	UE_LOG(LogTemp, Warning, TEXT("Hello Function "));

	
	
}

void AFreezeBomb::Hey()
{
	UE_LOG(LogTemp, Warning, TEXT("Hey Function "));
}

void AFreezeBomb::ExplodeBomb()
{

	UGameplayStatics::PlaySound2D(GetWorld(), ExplodeSound, 1.0f, 1.0f, 0.0f);
    
	isInvertControls = true;
	
	
	
	
	

}






