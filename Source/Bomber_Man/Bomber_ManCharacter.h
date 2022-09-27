// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include"Components/ArrowComponent.h"
#include"Components/PrimitiveComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SceneComponent.h"
#include "YTHealthComponent.h"
#include "GameFramework/Character.h"
#include "Bomber_ManCharacter.generated.h"


UCLASS(/*config=Game*/)
class ABomber_ManCharacter : public ACharacter 
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:

	ABomber_ManCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;
//
//	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;
//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterMovement:Walking")
		float Sprinter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		float Force;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		float health;
//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule Shape")
		float capsule_height;
//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule Shape")
		float capsule_radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		int BasicTimeBomb;
//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		int InstantBomb;
//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		int FreezeBomb;
//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		int StickyBomb;
//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		int InvertBomb;
//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		int LandMine;
//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		bool isAttached;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		bool isBombAttached;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		bool isControlsInverted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		bool isBoxPackage;
	


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class USceneComponent* Scene;
		
	

	
	UFUNCTION(Server, Reliable, WithValidation)
		void PunchMontage();
	bool PunchMontage_Validate();
	virtual void PunchMontage_Implementation();


	UFUNCTION(Server, Reliable, WithValidation)
		void GrabAndThrowMulti();
	bool GrabAndThrowMulti_Validate();
	virtual void GrabAndThrowMulti_Implementation();

	UFUNCTION(Server, Reliable, WithValidation)
		void SprintMulti();
	bool SprintMulti_Validate();
	virtual void SprintMulti_Implementation();

	UFUNCTION(Server, Reliable, WithValidation)
		void NoSprintMulti();
	bool NoSprintMulti_Validate();
	virtual void NoSprintMulti_Implementation();


	
//	
//	 
protected:
//	
//
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AActor>Timebomb;
//
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AActor>Frezebomb;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AActor>Instbomb;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AActor>Stckybomb;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AActor>Landminebomb;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AActor>Invrtbomb;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
        AActor* spawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		UAnimMontage* Montage;

	
public:
	/** Called for forwards/backward input */
	void MoveForward(float Value);
//
//	/** Called for side to side input */
	void MoveRight(float Value);
//
//	/** 
//	 * Called via input to turn at a given rate. 
//	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
//	 */
	void TurnAtRate(float Rate);
//
//	/**
//	 * Called via input to turn look up/down at a given rate. 
//	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
//	 */
	void LookUpAtRate(float Rate);
//
//	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);
//
//	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);
//
	UFUNCTION(BlueprintCallable)
	void sprinting();

	UFUNCTION(BlueprintCallable)
	void sprinting_stop();
//
	void GrabAndThrow(); 

	void OnAttack();

	void CheckPlayerHealth();

	float GetHealth() {
		return health;
	}
//
protected:
//	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
//	// End of APawn interface
//
public:
//	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
//	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	
};

