// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimalCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AAnimalCharacter::AAnimalCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAnimalCharacter::BeginPlay()
{
	Super::BeginPlay();

	SelectAnimal(ECurrentAnimal::Dog);
	
}

// Called every frame
void AAnimalCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAnimalCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAnimalCharacter::SetRunning(bool IsRunning)
{
	bIsRunning = IsRunning;

	GetCharacterMovement()->MaxWalkSpeed = bIsRunning ? SprintSpeedModifier*WalkSpeed : WalkSpeed;
}

void AAnimalCharacter::SelectAnimal(ECurrentAnimal SelectedAnimal)
{
	switch (SelectedAnimal)
	{
		case ECurrentAnimal::Cat:
			WalkSpeed = CatWalkSpeed;
			GetCharacterMovement()->MaxWalkSpeed = CatWalkSpeed;
			GetCharacterMovement()->MaxSwimSpeed = CatSwimSpeed;
			GetCharacterMovement()->JumpZVelocity = CatJumpHeight;
			// CanGlide
			// CanFly
			GetCapsuleComponent()->SetCapsuleSize(CatCharacterSize, CatCharacterSize, 1);
			// BreathHoldTime
			break;

		case ECurrentAnimal::Otter:
			WalkSpeed = OtterWalkSpeed;
			GetCharacterMovement()->MaxWalkSpeed = OtterWalkSpeed;
			GetCharacterMovement()->MaxSwimSpeed = OtterSwimSpeed;
			GetCharacterMovement()->JumpZVelocity = OtterJumpHeight;
			// CanGlide
			// CanFly
			GetCapsuleComponent()->SetCapsuleSize(OtterCharacterSize, OtterCharacterSize, 1);
			// BreathHoldTime
			break;

		case ECurrentAnimal::FlyingSquirrel:
			WalkSpeed = FlyingSquirrelWalkSpeed;
			GetCharacterMovement()->MaxWalkSpeed = FlyingSquirrelWalkSpeed;
			GetCharacterMovement()->MaxSwimSpeed = FlyingSquirrelSwimSpeed;
			GetCharacterMovement()->JumpZVelocity = FlyingSquirrelJumpHeight;
			// CanGlide
			// CanFly
			GetCapsuleComponent()->SetCapsuleSize(FlyingSquirrelCharacterSize, FlyingSquirrelCharacterSize, 1);
			// BreathHoldTime
			break;

		case ECurrentAnimal::Jerboa:
			WalkSpeed = JerboaWalkSpeed;
			GetCharacterMovement()->MaxWalkSpeed = JerboaWalkSpeed;
			GetCharacterMovement()->MaxSwimSpeed = JerboaSwimSpeed;
			GetCharacterMovement()->JumpZVelocity = JerboaJumpHeight;
			// CanGlide
			// CanFly
			GetCapsuleComponent()->SetCapsuleSize(JerboaCharacterSize, JerboaCharacterSize, 1);
			// BreathHoldTime
			break;

		case ECurrentAnimal::Bird:
			WalkSpeed = BirdWalkSpeed;
			GetCharacterMovement()->MaxWalkSpeed = BirdWalkSpeed;
			GetCharacterMovement()->MaxSwimSpeed = BirdSwimSpeed;
			GetCharacterMovement()->JumpZVelocity = BirdJumpHeight;
			// CanGlide
			// CanFly
			GetCapsuleComponent()->SetCapsuleSize(BirdCharacterSize, BirdCharacterSize, 1);
			// BreathHoldTime
			break;

		default:
			WalkSpeed = DogWalkSpeed;
			GetCharacterMovement()->MaxWalkSpeed = DogWalkSpeed;
			GetCharacterMovement()->MaxSwimSpeed = DogSwimSpeed;
			GetCharacterMovement()->JumpZVelocity = DogJumpHeight;
			// CanGlide
			// CanFly
			GetCapsuleComponent()->SetCapsuleSize(DogCharacterSize, DogCharacterSize, 1);
			// BreathHoldTime
			break;
	}
}

