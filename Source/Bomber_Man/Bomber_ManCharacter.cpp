// Copyright Epic Games, Inc. All Rights Reserved.

#include "Bomber_ManCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "BasicTimeBomb.h"
#include "FreezeBomb.h"
#include "YTHealthComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// ABomber_ManCharacter

ABomber_ManCharacter::ABomber_ManCharacter()
{
	// Set this actor to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = false;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)


	Sprinter = 2.0f;

	capsule_height = 10.0f;
	
	capsule_radius = 20.0f;
	
	BasicTimeBomb = 0;

	FreezeBomb = 0;

	Force = 1500.0f;

	health = 100.0f;

	
	

	
	Scene = CreateDefaultSubobject < USceneComponent>(TEXT("Scene Component"));
	
	

}



//////////////////////////////////////////////////////////////////////////
// Input

void ABomber_ManCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABomber_ManCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABomber_ManCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ABomber_ManCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABomber_ManCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ABomber_ManCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ABomber_ManCharacter::TouchStopped);

	


	// Player Sprint Functionality
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ABomber_ManCharacter::sprinting);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ABomber_ManCharacter::sprinting_stop);

	PlayerInputComponent->BindAction("Punch", IE_Released, this, &ABomber_ManCharacter::OnAttack);

	//Bomb Grab and Throw
	PlayerInputComponent->BindAction("Grab and Throw Bomb", IE_Pressed, this, &ABomber_ManCharacter::GrabAndThrow);
}



/*void ABomber_ManCharacter::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));
	}
}

void ABomber_ManCharacter::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap End"));
	}
}*/




void ABomber_ManCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void ABomber_ManCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void ABomber_ManCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABomber_ManCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}




void ABomber_ManCharacter::MoveForward(float Value)
{
	if (isControlsInverted)
	{
		Value *= -1.0f;
		if ((Controller != nullptr) && (Value != 0.0f))
		{
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
		}
	}
	else
	{
		if ((Controller != nullptr) && (Value != 0.0f))
		{
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
		}

	}
	
}

void ABomber_ManCharacter::MoveRight(float Value)
{
	
	if (isControlsInverted)
	{
		Value *= -1.0f;
		if ((Controller != nullptr) && (Value != 0.0f))
		{
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			AddMovementInput(Direction, Value);
		}
	}
	else
	{
		if ((Controller != nullptr) && (Value != 0.0f))
		{
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			AddMovementInput(Direction, Value);
		}

	}

}

void ABomber_ManCharacter::sprinting()
{
	GetCharacterMovement()->MaxWalkSpeed *= Sprinter;
	if (!GetWorld()->IsServer())
	{
		SprintMulti();
	}
}
bool ABomber_ManCharacter::SprintMulti_Validate()
{
	return true;
}

void ABomber_ManCharacter::SprintMulti_Implementation()
{
	sprinting();
}

void ABomber_ManCharacter::sprinting_stop()
{
	GetCharacterMovement()->MaxWalkSpeed /= Sprinter;
	if (!GetWorld()->IsServer())
	{
		NoSprintMulti();
	}
}

bool ABomber_ManCharacter::NoSprintMulti_Validate()
{
	return true;
}

void ABomber_ManCharacter::NoSprintMulti_Implementation()
{
	sprinting_stop();
}

void ABomber_ManCharacter::GrabAndThrow()
{

	const FVector location = Scene->GetRelativeLocation();
	const FRotator rotation = Scene->GetRelativeRotation();
	const FVector ForwardVector = UKismetMathLibrary::GetForwardVector(GetControlRotation());


	if (BasicTimeBomb > 0)
 	{
		if (isBoxPackage)
		{
			BasicTimeBomb++;
			isBoxPackage = false;
		}
		if (!isAttached)
		{

			spawn = GetWorld()->SpawnActor<AActor>(Timebomb, location, rotation);

			//UE_LOG(LogTemp, Warning, TEXT("Spawn: %s"), *spawn->GetName());

			if (spawn != nullptr)
			{
				if (GetMesh())
				{
					spawn->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("BombAttachment"));
					isAttached = true;
					isBombAttached = true;
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("MESH ERROR"));
				}

			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Nothing Spawn"));
			}
			// 			LandMine = 0;
			// 			InstantBomb = 0;
			// 			StickyBomb = 0;
			// 			BasicTimeBomb = 0;
			// 			InvertBomb = 0;
		}
		else if (isAttached)
		{


			spawn->K2_DetachFromActor(EDetachmentRule::KeepRelative, EDetachmentRule::KeepRelative, EDetachmentRule::KeepRelative);
			isAttached = false;
			if (UPrimitiveComponent* PrimComponent = Cast<UPrimitiveComponent>(spawn->GetComponentByClass(UPrimitiveComponent::StaticClass())))
			{

				PrimComponent->SetCollisionEnabled((ECollisionEnabled::QueryAndPhysics));
				PrimComponent->SetSimulatePhysics(true);
				PrimComponent->SetAllPhysicsLinearVelocity(ForwardVector*Force, false);

				isBombAttached = false;

				UE_LOG(LogTemp, Warning, TEXT(" Primitive"));

			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Not Primitive"));
			}

			UE_LOG(LogTemp, Warning, TEXT("Detached"));

			spawn = nullptr;

			if (BasicTimeBomb != 0)
			{
				BasicTimeBomb--;
			}



		}

 	}

	else if (FreezeBomb > 0)
	{
		if (isBoxPackage)
		{
			FreezeBomb++;
			isBoxPackage = false;
		}
		if (!isAttached)
		{

			spawn = GetWorld()->SpawnActor<AActor>(Frezebomb, location, rotation);

			//UE_LOG(LogTemp, Warning, TEXT("Spawn: %s"), *spawn->GetName());

			if(spawn!=nullptr)
			{
				if (GetMesh())
				{
					spawn->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("BombAttachment"));
					isAttached = true;
					isBombAttached = true;
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("MESH ERROR"));
				}

			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Nothing Spawn"));
			}
// 			LandMine = 0;
// 			InstantBomb = 0;
// 			StickyBomb = 0;
// 			BasicTimeBomb = 0;
// 			InvertBomb = 0;
		}
		else if (isAttached)
		{


			spawn->K2_DetachFromActor(EDetachmentRule::KeepRelative, EDetachmentRule::KeepRelative, EDetachmentRule::KeepRelative);
			isAttached = false;
			if (UPrimitiveComponent* PrimComponent = Cast<UPrimitiveComponent>(spawn->GetComponentByClass(UPrimitiveComponent::StaticClass())))
			{

				PrimComponent->SetCollisionEnabled((ECollisionEnabled::QueryAndPhysics));
				PrimComponent->SetSimulatePhysics(true);
				PrimComponent->SetAllPhysicsLinearVelocity(ForwardVector*Force, false);

				isBombAttached = false;

				UE_LOG(LogTemp, Warning, TEXT(" Primitive"));

			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Not Primitive"));
			}

			UE_LOG(LogTemp, Warning, TEXT("Detached"));

			spawn = nullptr;

			if (FreezeBomb!=0)
			{
				FreezeBomb--;
			}



		}
	}
	else if (InstantBomb > 0)
	{
	if (isBoxPackage)
	{
		InstantBomb++;
		isBoxPackage = false;
	}
		if (!isAttached)
		{

			spawn = GetWorld()->SpawnActor<AActor>(Instbomb, location, rotation);

			//UE_LOG(LogTemp, Warning, TEXT("Spawn: %s"), *spawn->GetName());
;
			if (spawn != nullptr)
			{
				if (GetMesh())
				{
					spawn->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("BombAttachment"));
					isAttached = true;
					isBombAttached = true;
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("MESH ERROR"));
				}

			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Nothing Spawn"));
			}

// 			LandMine = 0;
// 			StickyBomb = 0;
// 			FreezeBomb = 0;
// 			BasicTimeBomb = 0;
// 			InvertBomb = 0;
		}
		else if (isAttached)
		{
			spawn->K2_DetachFromActor(EDetachmentRule::KeepRelative, EDetachmentRule::KeepRelative, EDetachmentRule::KeepRelative);
			isAttached = false;
			if (UPrimitiveComponent* PrimComponent = Cast<UPrimitiveComponent>(spawn->GetComponentByClass(UPrimitiveComponent::StaticClass())))
			{

				PrimComponent->SetCollisionEnabled((ECollisionEnabled::QueryAndPhysics));
				PrimComponent->SetSimulatePhysics(true);
				PrimComponent->SetAllPhysicsLinearVelocity(ForwardVector*Force, false);

				isBombAttached = false;

				UE_LOG(LogTemp, Warning, TEXT(" Primitive"));

			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Not Primitive"));
			}

			UE_LOG(LogTemp, Warning, TEXT("Detached"));

			spawn = nullptr;

			if (InstantBomb!=0)
			{
				InstantBomb--;
			}

		}

	}
	else if (StickyBomb > 0)
	{
	if (isBoxPackage)
	{
		StickyBomb++;
		isBoxPackage = false;
	}
		if (!isAttached)
		{

			spawn = GetWorld()->SpawnActor<AActor>(Stckybomb, location, rotation);

			//UE_LOG(LogTemp, Warning, TEXT("Spawn: %s"), *spawn->GetName());

			
			if (spawn != nullptr)
			{
				if (GetMesh())
				{
					spawn->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("BombAttachment"));
					isAttached = true;
					isBombAttached = true;
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("MESH ERROR"));
				}

			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Nothing Spawn"));
			}
// 			LandMine = 0;
// 			InstantBomb = 0;
// 			FreezeBomb = 0;
// 			BasicTimeBomb = 0;
// 			InvertBomb = 0;

		}
		else if (isAttached)
		{
			spawn->K2_DetachFromActor(EDetachmentRule::KeepRelative, EDetachmentRule::KeepRelative, EDetachmentRule::KeepRelative);
			isAttached = false;
			if (UPrimitiveComponent* PrimComponent = Cast<UPrimitiveComponent>(spawn->GetComponentByClass(UPrimitiveComponent::StaticClass())))
			{

				PrimComponent->SetCollisionEnabled((ECollisionEnabled::QueryAndPhysics));
				PrimComponent->SetSimulatePhysics(true);
				PrimComponent->SetAllPhysicsLinearVelocity(ForwardVector*Force, false);

				isBombAttached = false;

				UE_LOG(LogTemp, Warning, TEXT(" Primitive"));

			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Not Primitive"));
			}

			UE_LOG(LogTemp, Warning, TEXT("Detached"));

			spawn = nullptr;

			if (StickyBomb!=0)
			{
				StickyBomb--;
			}

		}
	}
	else if (LandMine > 0)
	{
	if (isBoxPackage)
	{
		LandMine++;
		isBoxPackage = false;
	}
		if (!isAttached)
		{

			spawn = GetWorld()->SpawnActor<AActor>(Landminebomb, location, rotation);

			//UE_LOG(LogTemp, Warning, TEXT("Spawn: %s"), *spawn->GetName());


			if (spawn != nullptr)
			{
				if (GetMesh())
				{
					spawn->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("BombAttachment"));
					isAttached = true;
					isBombAttached = true;
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("MESH ERROR"));
				}

			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Nothing Spawn"));
			}
			
// 			StickyBomb = 0;
// 			InstantBomb = 0;
// 			FreezeBomb = 0;
// 			BasicTimeBomb = 0;
// 			InvertBomb = 0;
		}
		else if (isAttached)
		{
			spawn->K2_DetachFromActor(EDetachmentRule::KeepRelative, EDetachmentRule::KeepRelative, EDetachmentRule::KeepRelative);
			isAttached = false;
			if (UPrimitiveComponent* PrimComponent = Cast<UPrimitiveComponent>(spawn->GetComponentByClass(UPrimitiveComponent::StaticClass())))
			{

				PrimComponent->SetCollisionEnabled((ECollisionEnabled::QueryAndPhysics));
				PrimComponent->SetSimulatePhysics(true);
				PrimComponent->SetAllPhysicsLinearVelocity(ForwardVector*Force, false);

				isBombAttached = false;

				UE_LOG(LogTemp, Warning, TEXT(" Primitive"));

			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Not Primitive"));
			}

			UE_LOG(LogTemp, Warning, TEXT("Detached"));

			spawn = nullptr;

			if (LandMine!=0)
			{
				LandMine--;
			}

		}


	}
	else if (InvertBomb > 0)
	{
	if (isBoxPackage)
	{
		InvertBomb++;
		isBoxPackage = false;
	}
	if (!isAttached)
	{

		spawn = GetWorld()->SpawnActor<AActor>(Invrtbomb, location, rotation);

		//UE_LOG(LogTemp, Warning, TEXT("Spawn: %s"), *spawn->GetName());


		if (spawn != nullptr)
		{
			if (GetMesh())
			{
				spawn->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("BombAttachment"));
				isAttached = true;
				isBombAttached = true;
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("MESH ERROR"));
			}

		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Nothing Spawn"));
		}

// 		LandMine = 0;
// 		StickyBomb = 0;
// 		InstantBomb = 0;
// 		FreezeBomb = 0;
// 		BasicTimeBomb = 0;
	}
	else if (isAttached)
	{
		spawn->K2_DetachFromActor(EDetachmentRule::KeepRelative, EDetachmentRule::KeepRelative, EDetachmentRule::KeepRelative);
		isAttached = false;
		if (UPrimitiveComponent* PrimComponent = Cast<UPrimitiveComponent>(spawn->GetComponentByClass(UPrimitiveComponent::StaticClass())))
		{

			PrimComponent->SetCollisionEnabled((ECollisionEnabled::QueryAndPhysics));
			PrimComponent->SetSimulatePhysics(true);
			PrimComponent->SetAllPhysicsLinearVelocity(ForwardVector*Force, false);

			isBombAttached = false;

			UE_LOG(LogTemp, Warning, TEXT(" Primitive"));

		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Not Primitive"));
		}

		UE_LOG(LogTemp, Warning, TEXT("Detached"));

		spawn = nullptr;

		if (InvertBomb!=0)
		{
			InvertBomb--;
		}

	}
    }

	 if (!GetWorld()->IsServer())
	 {
		 GrabAndThrowMulti();
	 }

}


bool ABomber_ManCharacter::GrabAndThrowMulti_Validate()
{
	return true;
}

void ABomber_ManCharacter::GrabAndThrowMulti_Implementation()
{
	GrabAndThrow();
}

bool ABomber_ManCharacter::PunchMontage_Validate()
{
	return true;
}

void ABomber_ManCharacter::PunchMontage_Implementation()
{
	OnAttack();
}

void ABomber_ManCharacter::OnAttack()
{
	if (Montage)
	{
		if (!isBombAttached)
		{
			PlayAnimMontage(Montage, 2.0f);
		}
	}
	if (!GetWorld()->IsServer())
	{
		PunchMontage();
	}
}

void ABomber_ManCharacter::CheckPlayerHealth()
{
	GetMesh()->SetSimulatePhysics(true);
	GetCharacterMovement()->DisableMovement();
	
	
	UE_LOG(LogTemp, Warning, TEXT("Died"));
	
}




