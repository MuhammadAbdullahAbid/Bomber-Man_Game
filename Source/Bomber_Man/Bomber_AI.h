// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Bomber_AI.generated.h"

UCLASS()
class BOMBER_MAN_API ABomber_AI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABomber_AI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class USceneComponent* Scene;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		float Force;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AActor>Timebomb;

	UPROPERTY(VisibleAnywhere)
		AActor* ActorToSpawn;


	UFUNCTION(BlueprintCallable)
		void SpawnBomb();

	UFUNCTION(BlueprintCallable)
		void ThrowBomb();


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
