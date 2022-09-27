// Fill out your copyright notice in the Description page of Project Settings.


#include "MedKit.h"
#include "Engine/Engine.h"

// Sets default values
AMedKit::AMedKit()
{
	Meds = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	Meds->SetupAttachment(RootComponent);
	Meds->SetWorldScale3D(FVector(5.0f, 5.0f, 5.0f));
	Meds->SetRelativeScale3D(FVector(5.0f, 5.0f, 5.0f));

	Meds->OnComponentBeginOverlap.AddDynamic(this, &AMedKit::OnBeginOverlap);
	

}

// Called when the game starts or when spawned
void AMedKit::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMedKit::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
// 	if (OtherActor && (OtherActor != this)&& OtherComp)
// 	{
// 		IncrementHealth();
// 		UE_LOG(LogTemp, Warning, TEXT("We Began"));
// 		Meds->DestroyComponent(true);
// 		
// 		
// 		
// 	}
}

void AMedKit::IncrementHealth(UYTHealthComponent* HealthComp)
{
	//HealthComp = Cast <UYTHealthComponent>(UActorComponent::GetOwner());
// 	if (HealthComp->GetHealth())
// 	{
// 
// 	}

// 	PlayerHealth = HealthComp->GetHealth(PlayerHealth);
// 	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), PlayerHealth);
// 	if (PlayerHealth <100)
// 	{
// 		PlayerHealth+= 25.0f;
// 		if (PlayerHealth >100)
// 		{
// 			PlayerHealth = 100;
// 		}
// 	}
// 	else
// 	{
// 	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), PlayerHealth);
// 	GEngine->AddOnScreenDebugMessage(-1, 5.5f, FColor::Yellow, TEXT("Calling Function"));
// 	}
}




