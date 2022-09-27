// Fill out your copyright notice in the Description page of Project Settings.

#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "YTHealthComponent.h"

// Sets default values for this component's properties
UYTHealthComponent::UYTHealthComponent()
{
	DefaultHealth = 100.0f;
	Health = DefaultHealth;
}


// Called when the game starts
void UYTHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();

	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UYTHealthComponent::OnTakeDamage);
	}
	
}

void UYTHealthComponent::OnTakeDamage(AActor *DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	if (Damage<=0)
	{
		return;
	}
	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);

}

float UYTHealthComponent::GetHealth()
{
	return Health;
}





