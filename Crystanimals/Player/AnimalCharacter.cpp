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

	Hitbox = GetCapsuleComponent();

	// Create CollisionTestVolume used to test if character would overlap with other actors after animal switch
	CollisionTestVolume = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionTestVolume"));
	CollisionTestVolume->SetupAttachment(Hitbox);

	// Create First Person Camera and attach it to the characters CapsuleComponent (hitbox)
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(Hitbox);
	FirstPersonCamera->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AAnimalCharacter::BeginPlay()
{
	Super::BeginPlay();

	SwitchAnimal(EAnimal::Dog);
	
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

	GetCharacterMovement()->MaxWalkSpeed = bIsRunning ? SprintSpeedModifier * WalkSpeed : WalkSpeed;
	GetCharacterMovement()->MaxSwimSpeed = bIsRunning ? SprintSpeedModifier * SwimSpeed : SwimSpeed;
}

bool AAnimalCharacter::CheckEnoughSpaceForAnimalSwitch(float AnimalSize)
{
	if (CollisionTestVolume)
	{
		CollisionTestVolume->SetCapsuleSize(AnimalSize / 2, AnimalSize / 2, 1);

		// Set the relative location of the CollisionTestVolume to the height difference of the upcoming and current Hitbox
		// Meaning the relative location will be set where the Hitbox will be after the animal switch
		CollisionTestVolume->SetRelativeLocation(FVector(0, 0, (AnimalSize / 2) - Hitbox->GetScaledCapsuleHalfHeight()));

		// Check if the CollisionTestVolume is colliding with any actors other than the AnimalCharacter itself
		TArray OverlappingActors = TArray<AActor*>();
		CollisionTestVolume->GetOverlappingActors(OverlappingActors);
		OverlappingActors.Remove(this);

		if (OverlappingActors.IsEmpty())
		{
			return true;
		}
	}

	if (GEngine) 
	{
		// TODO: REPLACE THIS WITH A HUD MESSAGE
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString(TEXT("Collision check failed :(")));
	}

	return false;
}

void AAnimalCharacter::SetStatsByAnimalSize(float AnimalSize)
{
	// Set the basic stats for the animal based on the size of the animal, magic numbers found by trial and error
	WalkSpeed = 80 + (3 * AnimalSize);
	SwimSpeed = 50 + (0.5 * AnimalSize);
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->MaxSwimSpeed = SwimSpeed;
	GetCharacterMovement()->JumpZVelocity = 300 + (2 * AnimalSize);
	// CanGlide = false;
	// CanFly = false;
	// BreathHoldTime = 10;

	// Teleport the Hitbox (root component) up, so the player doesn't get stuck in the ground after animal switch
	// Add the height difference of the current and upcoming Hitbox to the Hitbox's world location to get the new location
	FVector NewCapsuleLocation = Hitbox->GetComponentLocation() + FVector(0, 0, (AnimalSize / 2) - Hitbox->GetScaledCapsuleHalfHeight());
	Hitbox->SetWorldLocation(NewCapsuleLocation);

	// Set the size of the Hitbox (root component) to the size of the animal
	// All animal sizes are their height in cm, for ease of use in the UE5 editor, hence the magic numbers
	Hitbox->SetCapsuleSize(AnimalSize / 2, AnimalSize / 2, 1);

	// Raise the camera to "eye height" from the centre of the capsule
	FirstPersonCamera->SetRelativeLocation(FVector(0, 0, AnimalSize / 4));
}

void AAnimalCharacter::SwitchAnimal(EAnimal SelectedAnimal)
{
	switch (SelectedAnimal)
	{
		case EAnimal::Cat:
			if (CheckEnoughSpaceForAnimalSwitch(CatSize))
			{
				SetStatsByAnimalSize(CatSize);
				GetCharacterMovement()->JumpZVelocity = CatJumpHeight;
			}
			break;

		case EAnimal::Otter:
			if (CheckEnoughSpaceForAnimalSwitch(OtterSize))
			{
				SetStatsByAnimalSize(OtterSize);
				SwimSpeed = OtterSwimSpeed;
				GetCharacterMovement()->MaxSwimSpeed = OtterSwimSpeed;
				GetCharacterMovement()->JumpZVelocity = OtterJumpHeight;
				// BreathHoldTime = OtterBreathHoldTime;
			}
			break;

		case EAnimal::FlyingSquirrel:
			if (CheckEnoughSpaceForAnimalSwitch(FlyingSquirrelSize))
			{
				SetStatsByAnimalSize(FlyingSquirrelSize);
				// CanGlide = true;
			}
			break;

		case EAnimal::Jerboa:
			if (CheckEnoughSpaceForAnimalSwitch(JerboaSize))
			{
				SetStatsByAnimalSize(JerboaSize);
			}
			break;

		case EAnimal::Bird:
			if (CheckEnoughSpaceForAnimalSwitch(BirdSize))
			{
				SetStatsByAnimalSize(BirdSize);
				GetCharacterMovement()->MaxSwimSpeed = BirdSwimSpeed;
				GetCharacterMovement()->JumpZVelocity = BirdJumpHeight;
				// CanGlide = true;
				// CanFly = true;
			}
			break;

		default:
			if (CheckEnoughSpaceForAnimalSwitch(DogSize))
			{
				SetStatsByAnimalSize(DogSize);
			}
			break;
	}
}

