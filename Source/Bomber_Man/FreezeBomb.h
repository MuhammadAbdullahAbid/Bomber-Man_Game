// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Bomber_ManCharacter.h"
#include "GameFramework/CharacterMovementReplication.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "FreezeBomb.generated.h"

UCLASS()
class BOMBER_MAN_API AFreezeBomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFreezeBomb();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* BombMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
		class USoundBase* ExplodeSound;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
		//class UNiagaraComponent* ExplodeFX;

	UPROPERTY(EditAnywhere, Category = "Variables")
		float Radius = 500.0f;

	UPROPERTY(VisibleAnywhere)
		class UCharacterMovementComponent* CharacterMovement;

	UPROPERTY(VisibleAnywhere)
		class APlayerController* PC;

	class ABomber_ManCharacter* Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		bool isInvertControls;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle timeHandle;

public:	
	
	
		void ExplodeBomb();

	
		void enable_Input(ABomber_ManCharacter* charc);

		void Hello();
		void Hey();
	

};
