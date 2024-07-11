// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimalCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PhysicsVolume.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "Player/AnimalPlayerController.h"
#include "Core/TreasureGameInstance.h"
#include "UserInterface/AnimalHUD.h"
#include "World/MapBoundaries.h"
#include "World/BlueIce.h"
#include "World/Trapdoor.h"

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

	// Create CollisionVolume used for checking breathing underwater and attact it to the camera
	CameraCollisionVolume = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CameraCollisionVolume"));
	CameraCollisionVolume->SetupAttachment(FirstPersonCamera);
	CameraCollisionVolume->SetCapsuleSize(0.1f, 0.1f);
	CameraCollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &AAnimalCharacter::StartHoldingBreath);
	CameraCollisionVolume->OnComponentEndOverlap.AddDynamic(this, &AAnimalCharacter::StopHoldingBreath);
}

// Called when the game starts or when spawned
void AAnimalCharacter::BeginPlay()
{
	Super::BeginPlay();

	HUD = GetWorld()->GetFirstPlayerController()->GetHUD<AAnimalHUD>();
	checkf(HUD, TEXT("AnimalCharacter unable to get reference to HUD"));

	PlayerController = GetController<AAnimalPlayerController>();
	checkf(PlayerController, TEXT("AnimalCharacter unable to get reference to PlayerController"));

	GameInstance = GetGameInstance<UTreasureGameInstance>();
	checkf(GameInstance, TEXT("AnimalCharacter unable to get reference to GameInstance"));

	GameInstance->OnUnlocksClaimed.AddDynamic(this, &AAnimalCharacter::UpdateUnlocks);

	DefaultGravityScale = GetCharacterMovement()->GravityScale;
	DefaultAirControl = GetCharacterMovement()->AirControl;
	GetCharacterMovement()->BrakingDecelerationFalling = AnimalBrakingDecelerationFalling;

	SwitchAnimal(GameInstance->CurrentAnimal);
}

// Called every frame
void AAnimalCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->TimeSince(LastFloorCheckTime) > 0.1f)
	{
		PerformFloorCheck();
	}

	// No need to call PerformInteractionCheck every frame, InteractionCheckFrequency set in constructor
	if (GetWorld()->TimeSince(InteractionData.LastInteractionCheckTime) > InteractionCheckFrequency && !HUD->bIsAnimalSelectionMenuVisible)
	{
		PerformInteractionCheck();
	}

	// Forces forward movement when gliding
	if (bIsGliding)
	{
		AddMovementInput(GetActorForwardVector(), 1);
	}

}

// Called to bind functionality to input
void AAnimalCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAnimalCharacter::SetRunning(bool ShouldRun)
{
	bIsRunning = ShouldRun;

	GetCharacterMovement()->MaxWalkSpeed = bIsRunning ? SprintSpeedModifier * WalkSpeed : WalkSpeed;
	GetCharacterMovement()->MaxSwimSpeed = bIsRunning ? SprintSpeedModifier * SwimSpeed : SwimSpeed;
}

bool AAnimalCharacter::IsRunning()
{
	return bIsRunning;
}

void AAnimalCharacter::SetGliding(bool ShouldGlide)
{
	bIsGliding = ShouldGlide;

	if (ShouldGlide)
	{
		GetCharacterMovement()->MaxWalkSpeed = GlideSpeedModifier * WalkSpeed;
		GetCharacterMovement()->GravityScale = GlidingGravityScale;
		GetCharacterMovement()->AirControl = GlidingAirControl;
		// Smooths out the transition from falling to gliding
		GetCharacterMovement()->Velocity.Z = FMath::FInterpTo<float>(GetCharacterMovement()->Velocity.Z, -GlideDescentRate, 0.1f, 0.2f);
	}
	else
	{
		GetCharacterMovement()->GravityScale = DefaultGravityScale;
		GetCharacterMovement()->AirControl = DefaultAirControl;
	}
}

void AAnimalCharacter::StartHoldingBreath(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass() == APhysicsVolume::StaticClass())
	{
		HUD->UpdateOxygenBarWidget(BreathHoldMaxDuration, BreathHoldMaxDuration);

		GetWorldTimerManager().SetTimer(BreathHoldTimer,
			this,
			&AAnimalCharacter::BreathHoldTimerUpdate,
			0.05f,
			true);

		BreathHoldStartTime = GetWorld()->GetTimeSeconds();
	}
}

void AAnimalCharacter::StopHoldingBreath(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->GetClass() == APhysicsVolume::StaticClass())
	{
		HUD->HideOxygenBarWidget();
		GetWorldTimerManager().ClearTimer(BreathHoldTimer);
	}
}

void AAnimalCharacter::BreathHoldTimerUpdate()
{
	float ElapsedTime = GetWorld()->TimeSince(BreathHoldStartTime);

	if (ElapsedTime >= BreathHoldMaxDuration)
	{
		HUD->UpdateOxygenBarWidget(0.0f, BreathHoldMaxDuration);
		GetWorldTimerManager().ClearTimer(BreathHoldTimer);

		Perish();
	}
	else
	{
		HUD->UpdateOxygenBarWidget(BreathHoldMaxDuration - ElapsedTime, BreathHoldMaxDuration);
	}
}

void AAnimalCharacter::StartExhaustionTimer()
{
	ExhaustionTimeLimit = GameInstance->bHasHeatResistance ? 240.0f : 30.0f;

	HUD->UpdateExhaustionBarWidget(0.0f, ExhaustionTimeLimit);

	GetWorldTimerManager().SetTimer(ExhaustionTimer,
		this,
		&AAnimalCharacter::ExhaustionTimerUpdate,
		0.05f,
		true);

	ExhaustionStartTime = GetWorld()->GetTimeSeconds();
}

void AAnimalCharacter::ExhaustionTimerUpdate()
{
	float ElapsedTime = GetWorld()->TimeSince(ExhaustionStartTime);

	if (ElapsedTime >= ExhaustionTimeLimit)
	{
		HUD->UpdateExhaustionBarWidget(ExhaustionTimeLimit, ExhaustionTimeLimit);
		GetWorldTimerManager().ClearTimer(ExhaustionTimer);

		Perish();
	}
	else
	{
		HUD->UpdateExhaustionBarWidget(ElapsedTime, ExhaustionTimeLimit);
	}
}

void AAnimalCharacter::StartFreezingTimer()
{
	FreezingTimeLimit = GameInstance->bHasColdResistance ? 10.0f : 2.5f;

	GetWorldTimerManager().SetTimer(FreezingTimer,
		this,
		&AAnimalCharacter::FreezingTimerUpdate,
		0.05f,
		true);

	FreezingStartTime = GetWorld()->GetTimeSeconds();
}

void AAnimalCharacter::FreezingTimerUpdate()
{
	float ElapsedTime = GetWorld()->TimeSince(FreezingStartTime);

	if (ElapsedTime >= FreezingTimeLimit)
	{
		GetWorldTimerManager().ClearTimer(FreezingTimer);
		Perish();
	}

	HUD->SetFreezeOverlayOpacity(ElapsedTime / FreezingTimeLimit);
}

void AAnimalCharacter::StopFreezingTimer()
{
	GetWorldTimerManager().ClearTimer(FreezingTimer);
	HUD->FadeFreezeOverlayOpacityToZero(GetWorld()->TimeSince(FreezingStartTime) / FreezingTimeLimit);
}

void AAnimalCharacter::FellOutOfWorld(const UDamageType& dmgType)
{
	Perish();
}

void AAnimalCharacter::Perish()
{
	PlayerController->FadeToBlack();

	FTimerHandle TempTimer;
	GetWorldTimerManager().SetTimer(TempTimer,
		this,
		&AAnimalCharacter::LoadLastSaveGame,
		1.1f,
		false);
}

void AAnimalCharacter::LoadLastSaveGame()
{
	GameInstance->LoadSaveGame();
	GameInstance->bShouldSaveAfterRealmChange = false;
	GameInstance->ChangeRealm(GameInstance->CurrentRealm);
}

void AAnimalCharacter::UpdateUnlocks()
{
	if (GameInstance->Score >= 20 && GameInstance->Score < 30)
	{
		if (!GameInstance->bHasKey)
		{
			HUD->DisplayNowUnlockedWidget("Mysterious Key");
			GameInstance->bHasKey = true;
		}
	}
	if (GameInstance->Score >= 40 && GameInstance->Score < 50)
	{
		if (!GameInstance->bHasHeatResistance)
		{
			HUD->DisplayNowUnlockedWidget("Heat Resistance");
			GameInstance->bHasHeatResistance = true;
		}
	}
	if (GameInstance->Score >= 70 && GameInstance->Score < 80)
	{
		if (!GameInstance->bHasColdResistance)
		{
			HUD->DisplayNowUnlockedWidget("Cold Resistance");
			GameInstance->bHasColdResistance = true;
		}
	}
}

void AAnimalCharacter::PerformFloorCheck()
{
	LastFloorCheckTime = GetWorld()->GetTimeSeconds();

	FVector TraceStart = Hitbox->GetComponentLocation();
	FVector TraceEnd = TraceStart - FVector(0, 0, Hitbox->GetScaledCapsuleHalfHeight() + 10.0f);

	// DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.0f, 0, 1.0f);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	FHitResult TraceHit;

	if (GetWorld()->LineTraceSingleByChannel(TraceHit, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
	{
		if (TraceHit.GetActor()->GetClass()->IsChildOf(ABlueIce::StaticClass()))
		{
			if (!bIsOnBlueIce)
			{
				StartFreezingTimer();
			}
			bIsOnBlueIce = true;
			return;
		}
	}

	if (bIsOnBlueIce)
	{
		StopFreezingTimer();
	}
	bIsOnBlueIce = false;
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
			if (TraceHit.GetActor() != InteractionData.CurrentInteractable || TraceHit.GetActor()->GetClass()->IsChildOf(ATrapdoor::StaticClass()))
			{
				InteractionData.CurrentInteractable = TraceHit.GetActor();
				TargetInteractable = TraceHit.GetActor();
				
				HUD->UpdateInteractionWidget(TargetInteractable->InteractableData);
			}
			return;
		}
	}
	StopInteracting();
}

void AAnimalCharacter::StopInteracting()
{
	HUD->HideInteractionWidget();

	InteractionData.CurrentInteractable = nullptr;
	TargetInteractable = nullptr;
}

void AAnimalCharacter::Interact()
{
	if (IsValid(TargetInteractable.GetObject()))
	{
		if (HUD->InteractionWidgetIsVisible())
		{
			TargetInteractable->Interact();
		}
	}
}

bool AAnimalCharacter::CheckEnoughSpaceForAnimalSwitch(float AnimalSize)
{
	if (CollisionTestVolume)
	{
		// 0.9428 comes from the Pythagorean theorem: sqrt( 1^2 - (1/3)^2 ) = 0.9428...
		// It is the radius of the capsule at 2/3 of the way up from the ground
		CollisionTestVolume->SetCapsuleSize(0.9428 * AnimalSize / 2, AnimalSize / 3, 1);

		// Set the location of the CollisionTestVolume 2/3 of the upcoming animal size up from the ground
		// (Relative location's height - current halfheight = ground level, then add 2/3 of upcoming animal size to that)
		CollisionTestVolume->SetRelativeLocation(FVector(0, 0, (2 * AnimalSize / 3) - Hitbox->GetScaledCapsuleHalfHeight()));

		// Check if the CollisionTestVolume is colliding with any actors other than the AnimalCharacter itself, MapBoundaries or PhysicsVolumes (water)
		TArray OverlappingActors = TArray<AActor*>();
		CollisionTestVolume->GetOverlappingActors(OverlappingActors);
		OverlappingActors.Remove(this);
		OverlappingActors.Remove(UGameplayStatics::GetActorOfClass(GetWorld(), AMapBoundaries::StaticClass()));
		OverlappingActors.Remove(UGameplayStatics::GetActorOfClass(GetWorld(), APhysicsVolume::StaticClass()));
		

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
	CanGlide = false;
	// Flying is implemented as being able to jump "many" (100) times in a row
	JumpMaxCount = 1;
	BreathHoldMaxDuration = 10.0f;

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

bool AAnimalCharacter::SwitchAnimal(EAnimal SelectedAnimal)
{
	if (!GetCharacterMovement()->IsFalling())
	{
		switch (SelectedAnimal)
		{
		case EAnimal::Cat:
			if (CheckEnoughSpaceForAnimalSwitch(CatSize))
			{
				SetStatsByAnimalSize(CatSize);
				GetCharacterMovement()->JumpZVelocity = CatJumpHeight;
				GameInstance->CurrentAnimal = SelectedAnimal;
				GameInstance->OnAnimalSwitched.Broadcast();
				return true;
			}
			break;

		case EAnimal::Otter:
			if (CheckEnoughSpaceForAnimalSwitch(OtterSize))
			{
				SetStatsByAnimalSize(OtterSize);
				SwimSpeed = OtterSwimSpeed;
				GetCharacterMovement()->MaxSwimSpeed = OtterSwimSpeed;
				GetCharacterMovement()->JumpZVelocity = OtterJumpHeight;
				BreathHoldMaxDuration = OtterBreathHoldMaxDuration;
				GameInstance->CurrentAnimal = SelectedAnimal;
				GameInstance->OnAnimalSwitched.Broadcast();
				return true;
			}
			break;

		case EAnimal::FlyingSquirrel:
			if (CheckEnoughSpaceForAnimalSwitch(FlyingSquirrelSize))
			{
				SetStatsByAnimalSize(FlyingSquirrelSize);
				CanGlide = true;
				GameInstance->CurrentAnimal = SelectedAnimal;
				GameInstance->OnAnimalSwitched.Broadcast();
				return true;
			}
			break;

		case EAnimal::Jerboa:
			if (CheckEnoughSpaceForAnimalSwitch(JerboaSize))
			{
				SetStatsByAnimalSize(JerboaSize);
				GameInstance->CurrentAnimal = SelectedAnimal;
				GameInstance->OnAnimalSwitched.Broadcast();
				return true;
			}
			break;

		case EAnimal::Bird:
			if (CheckEnoughSpaceForAnimalSwitch(BirdSize))
			{
				SetStatsByAnimalSize(BirdSize);
				GetCharacterMovement()->MaxSwimSpeed = BirdSwimSpeed;
				GetCharacterMovement()->JumpZVelocity = BirdJumpHeight;
				CanGlide = true;
				// Flying is implemented as being able to jump "many" (100) times in a row
				JumpMaxCount = 100;
				GameInstance->CurrentAnimal = SelectedAnimal;
				GameInstance->OnAnimalSwitched.Broadcast();
				return true;
			}
			break;

		default:
			if (CheckEnoughSpaceForAnimalSwitch(DogSize))
			{
				SetStatsByAnimalSize(DogSize);
				GameInstance->CurrentAnimal = SelectedAnimal;
				GameInstance->OnAnimalSwitched.Broadcast();
				return true;
			}
			break;
		}
		return false;
	} 
	else
	{
		HUD->DisplayCannotChangeWhileFallingWidget();
		return false;
	}
}

