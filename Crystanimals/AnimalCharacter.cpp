// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimalCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AAnimalCharacter::AAnimalCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SetActorTickInterval(0.5f);
	SetActorTickEnabled(true);

	// Create First Person Camera and attach it to the characters CapsuleComponent (hitbox)
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
	FirstPersonCamera->bUsePawnControlRotation = true;
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
			GetCapsuleComponent()->SetCapsuleSize(CatCharacterSize/4, CatCharacterSize/2, 1);
			// BreathHoldTime
			break;

		case ECurrentAnimal::Otter:
			WalkSpeed = OtterWalkSpeed;
			GetCharacterMovement()->MaxWalkSpeed = OtterWalkSpeed;
			GetCharacterMovement()->MaxSwimSpeed = OtterSwimSpeed;
			GetCharacterMovement()->JumpZVelocity = OtterJumpHeight;
			// CanGlide
			// CanFly
			GetCapsuleComponent()->SetCapsuleSize(OtterCharacterSize/4, OtterCharacterSize/2, 1);
			// BreathHoldTime
			break;

		case ECurrentAnimal::FlyingSquirrel:
			WalkSpeed = FlyingSquirrelWalkSpeed;
			GetCharacterMovement()->MaxWalkSpeed = FlyingSquirrelWalkSpeed;
			GetCharacterMovement()->MaxSwimSpeed = FlyingSquirrelSwimSpeed;
			GetCharacterMovement()->JumpZVelocity = FlyingSquirrelJumpHeight;
			// CanGlide
			// CanFly
			GetCapsuleComponent()->SetCapsuleSize(FlyingSquirrelCharacterSize/4, FlyingSquirrelCharacterSize/2, 1);
			// BreathHoldTime
			break;

		case ECurrentAnimal::Jerboa:
			WalkSpeed = JerboaWalkSpeed;
			GetCharacterMovement()->MaxWalkSpeed = JerboaWalkSpeed;
			GetCharacterMovement()->MaxSwimSpeed = JerboaSwimSpeed;
			GetCharacterMovement()->JumpZVelocity = JerboaJumpHeight;
			// CanGlide
			// CanFly
			GetCapsuleComponent()->SetCapsuleSize(JerboaCharacterSize/4, JerboaCharacterSize/2, 1);
			// BreathHoldTime
			break;

		case ECurrentAnimal::Bird:
			WalkSpeed = BirdWalkSpeed;
			GetCharacterMovement()->MaxWalkSpeed = BirdWalkSpeed;
			GetCharacterMovement()->MaxSwimSpeed = BirdSwimSpeed;
			GetCharacterMovement()->JumpZVelocity = BirdJumpHeight;
			// CanGlide
			// CanFly
			GetCapsuleComponent()->SetCapsuleSize(BirdCharacterSize/4, BirdCharacterSize/2, 1);
			// BreathHoldTime
			break;

		default:
			// CHECK IF THERE IS ENOUGH CLEARANCE TO BE ABLE TO SWITCH ANIMAL
			WalkSpeed = DogWalkSpeed;
			GetCharacterMovement()->MaxWalkSpeed = DogWalkSpeed;
			GetCharacterMovement()->MaxSwimSpeed = DogSwimSpeed;
			GetCharacterMovement()->JumpZVelocity = DogJumpHeight;
			// CanGlide
			// CanFly
			GetCapsuleComponent()->SetCapsuleSize(DogCharacterSize/2, DogCharacterSize/2, 1);
			FirstPersonCamera->AddRelativeLocation(FVector(0, 0, DogCharacterSize/4));
			// TELEPORT THE PLAYER A LITTLE UP TO NOT GET STUCK IN THE FLOOR
			// BreathHoldTime
			break;
	}
}

