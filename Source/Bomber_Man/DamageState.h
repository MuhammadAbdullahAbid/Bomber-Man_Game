// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "DamageState.generated.h"

/**
 * 
 */
UCLASS()
class BOMBER_MAN_API UDamageState : public UAnimNotifyState
{
	GENERATED_BODY()

		UDamageState();
public:

	virtual void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)override;

	float TraceRadius = 10;

	TArray<FHitResult>OutHits;

	FCollisionShape Shape = FCollisionShape::MakeSphere(TraceRadius);
	
};
