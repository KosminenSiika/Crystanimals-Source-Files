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
	// Create temporary CollisionTestVolume to test if character would overlap with other actors after animal switch
	TObjectPtr<UCapsuleComponent> CollisionTestVolume = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionTestVolume"));
	CollisionTestVolume->SetupAttachment(Hitbox);
	CollisionTestVolume->SetCapsuleSize(AnimalSize / 2, AnimalSize / 2, 1);

	// Add the height difference of the CollisionTestVolume and Hitbox to the Hitbox's world location to get CollisionTestVolume's required location
	FVector CollisionTestWorldLocation = Hitbox->GetComponentLocation() + (FVector(0, 0, (AnimalSize / 2) - Hitbox->GetScaledCapsuleHalfHeight()));
	CollisionTestVolume->SetWorldLocation(CollisionTestWorldLocation);

	TArray OverlappingActors = TArray<AActor*>();
	CollisionTestVolume->GetOverlappingActors(OverlappingActors);

	if (OverlappingActors.IsEmpty())
	{
		CollisionTestVolume->DestroyComponent();
		return true;
	}

	CollisionTestVolume->DestroyComponent();
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
	// TELEPORT CAPSULE UP TO NOT CLIP IN THE GROUND

	// Set the size of the capsule component (root component of the character) to the size of the animal
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
			SetStatsByAnimalSize(CatSize);
			GetCharacterMovement()->JumpZVelocity = CatJumpHeight;
			break;

		case EAnimal::Otter:
			SetStatsByAnimalSize(OtterSize);
			SwimSpeed = OtterSwimSpeed;
			GetCharacterMovement()->MaxSwimSpeed = OtterSwimSpeed;
			GetCharacterMovement()->JumpZVelocity = OtterJumpHeight;
			// BreathHoldTime = OtterBreathHoldTime;
			break;

		case EAnimal::FlyingSquirrel:
			SetStatsByAnimalSize(FlyingSquirrelSize);
			// CanGlide = true;
			break;

		case EAnimal::Jerboa:
			SetStatsByAnimalSize(JerboaSize);
			break;

		case EAnimal::Bird:
			SetStatsByAnimalSize(BirdSize);
			GetCharacterMovement()->MaxSwimSpeed = BirdSwimSpeed;
			GetCharacterMovement()->JumpZVelocity = BirdJumpHeight;
			// CanGlide = true;
			// CanFly = true;
			break;

		default:
			// CHECK IF THERE IS ENOUGH CLEARANCE TO BE ABLE TO SWITCH ANIMAL
			SetStatsByAnimalSize(DogSize);
			break;
	}
}

