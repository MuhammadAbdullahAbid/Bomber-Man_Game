// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/Character.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/Actor.h"
#include "BasicTimeBomb.generated.h"



UCLASS()
class BOMBER_MAN_API ABasicTimeBomb : public AActor 
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicTimeBomb(const FObjectInitializer& objectinitializer);


	//Declarations

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* BombMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class URadialForceComponent* RadialForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
		class UParticleSystemComponent* ExplodeFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
		class USoundBase* ExplodeSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		float DetonateTime;

	UPROPERTY(EditAnywhere)
	class ABomber_ManCharacter* Main_Player;

	



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



	

public:	
	
	    UFUNCTION()
		void OnComponentActivate(bool bReset);
		
		void Activation();

	

};
