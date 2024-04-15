// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimalPlayerController.h"
#include "AnimalCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void AAnimalPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	// Store a reference to the Player's Pawn.
	PlayerCharacter = Cast<AAnimalCharacter>(aPawn);
	checkf(PlayerCharacter, TEXT("AAnimalController derived classes should only possess AAnimalCharacter derived pawns"));

	// Store a reference to the EnhancedInputComponent.
	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(EnhancedInputComponent, TEXT("Unable to get reference to the EnhancedInputComponent."));

	// Get the local player subsystem.
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSubsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(InputSubsystem, TEXT("Unable to get reference to the EnhancedInputLocalPlayerSubsystem."));

	// Wipe existing mappings, and add our mapping.
	checkf(InputMappingContext, TEXT("InputMappingContext was not specified"));
	InputSubsystem->ClearAllMappings();
	InputSubsystem->AddMappingContext(InputMappingContext, 0);

	// Bind the input actions.
	// Only attempt to bind if a valid value was provided.
	if (ActionMove)
	{
		EnhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Triggered, this, &AAnimalPlayerController::HandleMove);
	}

	if (ActionLook)
	{
		EnhancedInputComponent->BindAction(ActionLook, ETriggerEvent::Triggered, this, &AAnimalPlayerController::HandleLook);
	}

	if (ActionJump)
	{
		EnhancedInputComponent->BindAction(ActionJump, ETriggerEvent::Started, this, &AAnimalPlayerController::HandleJump);
	}

	if (ActionHoldSprint)
	{
		EnhancedInputComponent->BindAction(ActionHoldSprint, ETriggerEvent::Triggered, this, &AAnimalPlayerController::HandleHoldSprint);
		EnhancedInputComponent->BindAction(ActionHoldSprint, ETriggerEvent::Completed, this, &AAnimalPlayerController::HandleStopHoldingSprint);
	}

	if (ActionInteract)
	{
		EnhancedInputComponent->BindAction(ActionInteract, ETriggerEvent::Started, this, &AAnimalPlayerController::HandleInteract);
	}

	if (ActionOpenCloseMainMenu)
	{
		EnhancedInputComponent->BindAction(ActionOpenCloseMainMenu, ETriggerEvent::Started, this, &AAnimalPlayerController::HandleOpenCloseMainMenu);
	}
}

void AAnimalPlayerController::OnUnPossess()
{
	// Unbind things here...
	EnhancedInputComponent->ClearActionBindings();

	Super::OnUnPossess();
}

void AAnimalPlayerController::HandleLook(const FInputActionValue& InputActionValue)
{
	// Input is a Vector2D
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	// Add yaw and pitch input to controller
	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

void AAnimalPlayerController::HandleMove(const FInputActionValue& InputActionValue)
{
	// Input is a Vector2D
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	// Add movement to the Player's Character Pawn.
	if (PlayerCharacter)
	{
		PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorForwardVector(), MovementVector.Y);
		PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorRightVector(), MovementVector.X);
	}
}

void AAnimalPlayerController::HandleHoldSprint()
{
	// Make the Player's Character Pawn start running
	if (PlayerCharacter)
	{
		PlayerCharacter->SetRunning(true);
	}
}

void AAnimalPlayerController::HandleStopHoldingSprint()
{
	// Make the Player's Character Pawn stop running
	if (PlayerCharacter)
	{
		PlayerCharacter->SetRunning(false);
	}
}

void AAnimalPlayerController::HandleJump()
{
	// Make the Player's Character Pawn jump
	if (PlayerCharacter)
	{
		PlayerCharacter->Jump();
	}
}

void AAnimalPlayerController::HandleInteract()
{
	// Make the Player's Character Pawn interact with what they are looking at
	if (PlayerCharacter)
	{
		PlayerCharacter->Interact();
	}
}

void AAnimalPlayerController::HandleOpenCloseMainMenu()
{
	if (PlayerCharacter)
	{
		if (PlayerCharacter->OpenCloseMainMenu())
		{
			bShowMouseCursor = true;
			bEnableClickEvents = true;
		} 
		else
		{
			bShowMouseCursor = false;
			bEnableClickEvents = false;
		}
	}
}
