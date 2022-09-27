// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageState.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"

UDamageState::UDamageState()
{
}

void UDamageState::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	bool bHit=false;
	FVector StartSocketLocation;
	FVector EndSocketLocation;

	TArray<AActor*>ActorTOIgnore;

// 	StartSocketLocation = MeshComp->GetSocketLocation(FName ("middle_01_r"));
// 	EndSocketLocation = MeshComp->GetSocketLocation(FName("middle_03_r"));
// 
// 	bHit = GetWorld()->SweepMultiByChannel(OutHits, StartSocketLocation, EndSocketLocation, FQuat::Identity, ECC_Camera, Shape);
// 
// 	DrawDebugSphere(GetWorld(), StartSocketLocation, TraceRadius, 30, FColor::Yellow, true, 5.0f, 0, 1.0f);

	//bHit = UKismetSystemLibrary::SphereTraceMulti(GetWorld(), StartSocketLocation, EndSocketLocation, TraceRadius, UEngineTypes::ConvertToTraceType(ECC_Camera), false, ActorTOIgnore, EDrawDebugTrace::ForDuration, OutHits, true, FLinearColor::Yellow, FLinearColor::Green, 5.0f);

	if (bHit)
	{
		for (FHitResult OutHit:OutHits)
		{
			UE_LOG(LogTemp, Warning, TEXT("DamageStateC++"));
			
			
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.5f, FColor::Yellow, TEXT("Not Found"));
	}

}
