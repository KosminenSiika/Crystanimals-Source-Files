// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimalPlayerController.h"
#include "AnimalCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Core/TreasureGameInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "UserInterface/AnimalHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

void AAnimalPlayerController::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = GetGameInstance<UTreasureGameInstance>();
	checkf(GameInstance, TEXT("AnimalPlayerController unable to get reference to GameInstance"));

	HUD = GetHUD<AAnimalHUD>();
	checkf(HUD, TEXT("Unable to get reference to HUD"));

	SetInputMode(FInputModeGameOnly());

	PlayerCameraManager->SetManualCameraFade(1.0f, FLinearColor::Black, false);

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle,
		this,
		&AAnimalPlayerController::FadeOutOfBlack,
		1.0f,
		false);
}

void AAnimalPlayerController::Tick(float DeltaTime)
{
	if (PlayerCharacter)
	{
		if (PlayerCharacter->GetCharacterMovement()->IsMovingOnGround())
		{
			if (PlayerCharacter->GetVelocity().Length() > 0.0f && GetWorld()->TimeSince(LastSurfaceCheckTime) >= (PlayerCharacter->IsRunning() ? 0.25f : 0.5f))
			{
				CheckSurfaceAndPlayFootstepSound();
			}

			if (ViewBobShakeClass)
			{
				ViewBobShakeInstance = PlayerCameraManager->StartCameraShake(ViewBobShakeClass, PlayerCharacter->GetVelocity().Length() / 275.0f);
			}
		}
		else
		{
			if (ViewBobShakeInstance)
			{
				PlayerCameraManager->StopCameraShake(ViewBobShakeInstance, false);
			}
		}
	}	
}

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

	if (ActionHoldSprintGlide)
	{
		EnhancedInputComponent->BindAction(ActionHoldSprintGlide, ETriggerEvent::Triggered, this, &AAnimalPlayerController::HandleHoldSprintGlide);
		EnhancedInputComponent->BindAction(ActionHoldSprintGlide, ETriggerEvent::Completed, this, &AAnimalPlayerController::HandleStopHoldingSprintGlide);
	}

	if (ActionInteract)
	{
		EnhancedInputComponent->BindAction(ActionInteract, ETriggerEvent::Started, this, &AAnimalPlayerController::HandleInteract);
	}

	if (ActionOpenCloseMainMenu)
	{
		EnhancedInputComponent->BindAction(ActionOpenCloseMainMenu, ETriggerEvent::Started, this, &AAnimalPlayerController::HandleOpenCloseMainMenu);
	}

	if (ActionOpenCloseAnimalSelectionMenu)
	{
		EnhancedInputComponent->BindAction(ActionOpenCloseAnimalSelectionMenu, ETriggerEvent::Started, this, &AAnimalPlayerController::HandleOpenAnimalSelectionMenu);
		EnhancedInputComponent->BindAction(ActionOpenCloseAnimalSelectionMenu, ETriggerEvent::Completed, this, &AAnimalPlayerController::HandleCloseAnimalSelectionMenu);
	}

	if (ActionSwimUp)
	{
		EnhancedInputComponent->BindAction(ActionSwimUp, ETriggerEvent::Triggered, this, &AAnimalPlayerController::HandleSwimUp);
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
	AddYawInput(LookAxisVector.X * GameInstance->MouseSens);
	AddPitchInput(LookAxisVector.Y * GameInstance->MouseSens);
}

void AAnimalPlayerController::HandleMove(const FInputActionValue& InputActionValue)
{
	// Input is a Vector2D
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	// Add movement to the Player's Character Pawn.
	if (PlayerCharacter)
	{
		if (PlayerCharacter->GetCharacterMovement()->IsSwimming())
		{
			PlayerCharacter->AddMovementInput(PlayerCharacter->GetControlRotation().Vector(), MovementVector.Y);
			PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorRightVector(), MovementVector.X);
		}
		else
		{
			PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorForwardVector(), MovementVector.Y);
			PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorRightVector(), MovementVector.X);
		}
	}
}

void AAnimalPlayerController::HandleHoldSprintGlide()
{
	// Make the Player's Character Pawn start running
	if (PlayerCharacter)
	{
		if (PlayerCharacter->CanGlide && PlayerCharacter->GetCharacterMovement()->IsFalling())
		{
			PlayerCharacter->SetGliding(true);
			if (!GlideWindComponent)
			{
				GlideWindComponent = UGameplayStatics::SpawnSound2D(GetWorld(), GlideWind);
			}
		}
		else 
		{
			PlayerCharacter->SetRunning(true);

			if (GlideWindComponent)
			{
				GlideWindComponent->FadeOut(0.5f, 0.0f);
				GlideWindComponent = nullptr;
			}
		}
	}
}

void AAnimalPlayerController::HandleStopHoldingSprintGlide()
{
	// Make the Player's Character Pawn stop running
	if (PlayerCharacter)
	{
		PlayerCharacter->SetRunning(false);
		PlayerCharacter->SetGliding(false);

		if (GlideWindComponent)
		{
			GlideWindComponent->FadeOut(0.5f, 0.0f);
			GlideWindComponent = nullptr;
		}
	}
}

void AAnimalPlayerController::HandleJump()
{
	// Make the Player's Character Pawn jump
	if (PlayerCharacter)
	{
		if (!PlayerCharacter->bIsOnBlueIce)
		{
			PlayerCharacter->Jump();
		}
	}
}

void AAnimalPlayerController::HandleSwimUp()
{
	if (PlayerCharacter->GetCharacterMovement()->IsSwimming())
	{
		PlayerCharacter->AddMovementInput(FVector::UpVector, 1.0f);
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
	if (HUD)
	{
		if (!HUD->bIsMainMenuVisible)
		{
			bShowMouseCursor = true;
			bEnableClickEvents = true;
			SetInputMode(FInputModeGameAndUI());
			HUD->DisplayMainMenu();

			int x, y;
			GetViewportSize(x, y);
			SetMouseLocation(x / 2.0f, y / 2.0f);
		} 
		else
		{
			bShowMouseCursor = false;
			bEnableClickEvents = false;
			SetInputMode(FInputModeGameOnly());
			HUD->HideMainMenu();
		}
	}
}

void AAnimalPlayerController::HandleOpenAnimalSelectionMenu()
{
	if (HUD)
	{
		if (!HUD->bIsAnimalSelectionMenuVisible)
		{
			HUD->DisplayAnimalSelectionMenu();
			bShowMouseCursor = true;
			bEnableClickEvents = true;
			SetInputMode(FInputModeGameAndUI());

			int x, y;
			GetViewportSize(x, y);
			SetMouseLocation(x / 2.0f, y / 1.4f);
		}
	}
}

void AAnimalPlayerController::HandleCloseAnimalSelectionMenu()
{
	if (HUD)
	{
		if (HUD->bIsAnimalSelectionMenuVisible)
		{
			bShowMouseCursor = false;
			bEnableClickEvents = false;
			SetInputMode(FInputModeGameOnly());
			HUD->HideAnimalSelectionMenu();
		}
	}
}

void AAnimalPlayerController::FadeToBlack()
{
	PlayerCameraManager->StartCameraFade(0.0f, 1.0f, 1.0f, FLinearColor::Black, true, true);

	DisableInput(this);

	HUD->HideScoreWidget();
	HUD->HideInteractionWidget();
	HUD->HideNewUnlocksWidget();
	HUD->HideCrosshair();
}

void AAnimalPlayerController::FadeOutOfBlack()
{
	PlayerCameraManager->StartCameraFade(1.0f, 0.0f, 2.0f, FLinearColor::Black);

	if (GameInstance->bShouldSaveAfterRealmChange)
	{
		GameInstance->SaveGame();
	}

	if (GameInstance->CurrentRealm == "DesertRealm")
	{
		PlayerCharacter->StartExhaustionTimer();
	}

	HUD->DisplayScoreWidget();
	HUD->DisplayCrosshair();

	if (GameInstance->bNewUnlocksNotClaimed)
	{
		HUD->DisplayNewUnlocksWidget();
	}
}

void AAnimalPlayerController::CheckSurfaceAndPlayFootstepSound()
{
	LastSurfaceCheckTime = GetWorld()->GetTimeSeconds();

	FVector TraceStart = PlayerCharacter->GetActorLocation();
	FVector TraceEnd = TraceStart - FVector(0, 0, 100.0f);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.bReturnPhysicalMaterial = true;

	FHitResult TraceHit;

	if (GetWorld()->LineTraceSingleByChannel(TraceHit, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
	{
		if (TraceHit.PhysMaterial.IsValid())
		{
			switch (TraceHit.PhysMaterial->SurfaceType)
			{
			case SurfaceType1:
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), GrassFootstep, TraceHit.Location);
				break;
			case SurfaceType2:
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), StoneFootstep, TraceHit.Location);
				break;
			case SurfaceType3:
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), SandFootstep, TraceHit.Location);
				break;
			case SurfaceType4:
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), WoodFootstep, TraceHit.Location);
				break;
			case SurfaceType5:
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), SnowFootstep, TraceHit.Location);
				break;
			case SurfaceType6:
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), IceFootstep, TraceHit.Location);
				break;
			default:
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), StoneFootstep, TraceHit.Location);
				break;
			}
		}
	}
}
