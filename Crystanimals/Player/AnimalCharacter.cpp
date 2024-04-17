// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimalCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "UserInterface/AnimalHUD.h"

// Sets default values
AAnimalCharacter::AAnimalCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractionCheckFrequency = 0.1f;
	InteractionCheckDistance = 100.0f;

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

	HUD = Cast<AAnimalHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	checkf(HUD, TEXT("Unable to get reference to HUD"));

	SwitchAnimal(EAnimal::Dog);
	
}

// Called every frame
void AAnimalCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// No need to call PerformInteractionCheck every frame, InteractionCheckFrequency set in constructor
	if (GetWorld()->TimeSince(InteractionData.LastInteractionCheckTime) > InteractionCheckFrequency)
	{
		PerformInteractionCheck();
	}

}

// Called to bind functionality to input
void AAnimalCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Check if the Character is looking at an interactable actor
void AAnimalCharacter::PerformInteractionCheck()
{
	InteractionData.LastInteractionCheckTime = GetWorld()->GetTimeSeconds();

	FVector TraceStart = FirstPersonCamera->GetComponentLocation();
	FVector TraceEnd = TraceStart + (GetViewRotation().Vector() * InteractionCheckDistance);

	// DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.0f, 0, 1.0f);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	FHitResult TraceHit;

	// Shoot out a trace in the direction the Character is looking
	if (GetWorld()->LineTraceSingleByChannel(TraceHit, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
	{
		// Check if hit actor implements InteractionInterface
		if (TraceHit.GetActor()->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
		{
			if (TraceHit.GetActor() != InteractionData.CurrentInteractable)
			{
				InteractionData.CurrentInteractable = TraceHit.GetActor();
				TargetInteractable = TraceHit.GetActor();
				
				HUD->UpdateInteractionWidget(TargetInteractable->InteractableData);
			}
			return;
		}
	}
	HUD->HideInteractionWidget();

	InteractionData.CurrentInteractable = nullptr;
	TargetInteractable = nullptr;
}

void AAnimalCharacter::Interact()
{
	if (IsValid(TargetInteractable.GetObject()))
	{
		TargetInteractable->Interact();
	}
}

// Return value tells the AnimalPlayerController whether or not 
// it should show the mouse cursor and enable click events
bool AAnimalCharacter::OpenCloseMainMenu()
{
	if (HUD->bIsMainMenuVisible)
	{
		HUD->HideMainMenu();
		return false;
	}
	else
	{
		HUD->DisplayMainMenu();
		return true;
	}
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

		HUD->DisplayNotEnoughSpaceWidget();
	}
	return false;
}

void AAnimalCharacter::SetStatsByAnimalSize(float AnimalSize)
{
	// Set the basic stats for the animal based on the size of the animal, magic numbers found by trial and error
	WalkSpeed = 80.0f + (3 * AnimalSize);
	SwimSpeed = 50.0f + (0.5f * AnimalSize);
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->MaxSwimSpeed = SwimSpeed;
	GetCharacterMovement()->JumpZVelocity = 300.0f + (2 * AnimalSize);
	// CanGlide = false;
	// CanFly = false;
	// BreathHoldTime = 10;

	// Change interaction distance based on the size of the animal
	InteractionCheckDistance = 65.0f + AnimalSize;

	// Teleport the Hitbox (root component) up, so the player doesn't get stuck in the ground after animal switch
	// Add the height difference of the current and upcoming Hitbox to the Hitbox's world location to get the new location
	FVector NewCapsuleLocation = Hitbox->GetComponentLocation() + FVector(0, 0, (AnimalSize / 2) - Hitbox->GetScaledCapsuleHalfHeight());
	Hitbox->SetWorldLocation(NewCapsuleLocation);

	// Set the size of the Hitbox (root component) to the size of the animal
	// All animal sizes are their height in cm, for ease of use in the UE5 editor, hence the magic numbers
	Hitbox->SetCapsuleSize(AnimalSize / 2, AnimalSize / 2, true);

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

