// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicTimeBomb.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Bomber_ManCharacter.h"
#include "Engine/Engine.h"
#include "Components/SphereComponent.h"




// Sets default values
ABasicTimeBomb::ABasicTimeBomb(const FObjectInitializer& objectinitializer)
	:Super(objectinitializer)
{

	
	
	BombMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = BombMesh;
	BombMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	BombMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereCollision->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	SphereCollision->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	SphereCollision->SetupAttachment(BombMesh, NAME_None);

	ExplodeFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System"));
	ExplodeFX->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	ExplodeFX->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	ExplodeFX->SetupAttachment(BombMesh, NAME_None);

	

	DetonateTime = 0;
}

// Called when the game starts or when spawned
void ABasicTimeBomb::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle timeHandle;
	GetWorld()->GetTimerManager().SetTimer(timeHandle, this, &ABasicTimeBomb::Activation, DetonateTime);
	//ExplodeFX->OnComponentActivated.AddDynamic(this, &ABasicTimeBomb::OnComponentActivate);
	
	
}
void ABasicTimeBomb::OnComponentActivate( bool bReset)
{
	FVector ParticleLocation = ExplodeFX->GetComponentLocation();
	float Distance;
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ExplodeSound, ParticleLocation, FRotator::ZeroRotator);
	RadialForce->FireImpulse();

	Distance = GetDistanceTo(Main_Player);

	if (Distance <= 700.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Distance %f"), Distance);

		Main_Player->health = Main_Player->health - 20;
		BombMesh->DestroyComponent(true);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not in Range"));
		BombMesh->DestroyComponent(true);

	}
	
}

void ABasicTimeBomb::Activation()
{
	ExplodeFX->Activate(true);
}


