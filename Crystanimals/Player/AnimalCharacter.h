// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/InteractionInterface.h"
#include "AnimalCharacter.generated.h"

// Forward Declarations
class UCameraComponent;
class AAnimalHUD;
class UTreasureGameInstance;

UENUM()
enum class EAnimal :uint8
{
	Dog,
	Cat,
	Otter,
	FlyingSquirrel,
	Jerboa,
	Bird
};

USTRUCT()
struct FInteractionData
{
	GENERATED_USTRUCT_BODY()

	FInteractionData() : CurrentInteractable(nullptr), LastInteractionCheckTime(0.0f) {};

	UPROPERTY()
	TObjectPtr<AActor> CurrentInteractable;

	UPROPERTY()
	float LastInteractionCheckTime;
};

UCLASS()
class CRYSTANIMALS_API AAnimalCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY()
	bool CanGlide;

	UPROPERTY()
	bool bIsGliding = false;

	// Sets default values for this character's properties
	AAnimalCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void StartExhaustionTimer();

	UFUNCTION()
	void Interact();

	UFUNCTION()
	bool OpenCloseMainMenu();

	UFUNCTION()
	bool OpenCloseAnimalSelectionMenu();

	UFUNCTION()
	void SetRunning(bool ShouldRun);

	UFUNCTION()
	void SetGliding(bool ShouldGlide);

	// Tries to switch the character to the desired animal
	UFUNCTION()
	void SwitchAnimal(EAnimal SelectedAnimal);

	// Function is overridden to be able to use KillZVolume
	virtual void FellOutOfWorld(const class UDamageType& dmgType) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	UPROPERTY(VisibleAnywhere, Category = "Player|Camera")
	TObjectPtr<UCameraComponent> FirstPersonCamera = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Player|Camera")
	TObjectPtr<UCapsuleComponent> CameraCollisionVolume = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Player|Collision")
	TObjectPtr<UCapsuleComponent> Hitbox = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Player|Collision")
	TObjectPtr<UCapsuleComponent> CollisionTestVolume = nullptr;

	UPROPERTY()
	TObjectPtr<UTreasureGameInstance> GameInstance = nullptr;

	UPROPERTY()
	TObjectPtr<AAnimalHUD> HUD = nullptr;

	// Timers
	UPROPERTY()
	FTimerHandle BreathHoldTimer;

	UPROPERTY()
	float BreathHoldMaxDuration;

	UPROPERTY()
	float BreathHoldStartTime;

	UPROPERTY()
	FTimerHandle ExhaustionTimer;

	UPROPERTY()
	float ExhaustionTimeLimit;

	UPROPERTY()
	float ExhaustionStartTime;

	// Interaction
	UPROPERTY(VisibleAnywhere, Category = "Player|Interaction")
	TScriptInterface<IInteractionInterface> TargetInteractable = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Player|Interaction")
	float InteractionCheckFrequency;

	UPROPERTY(VisibleAnywhere, Category = "Player|Interaction")
	float InteractionCheckDistance;

	UPROPERTY(VisibleAnywhere, Category = "Player|Interaction")
	FInteractionData InteractionData;

	// Movement
	UPROPERTY()
	bool bIsRunning = false;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Movement")
	float SprintSpeedModifier;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Movement")
	float GlideSpeedModifier;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Movement")
	float GlideDescentRate;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Movement")
	float AnimalBrakingDecelerationFalling;
	
	UPROPERTY()
	float WalkSpeed;

	UPROPERTY()
	float SwimSpeed;

	UPROPERTY()
	float DefaultGravityScale;

	UPROPERTY()
	float DefaultAirControl;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Gliding")
	float GlidingGravityScale;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Gliding")
	float GlidingAirControl;


	// Dog Specific Stats - editable in UE5 editor
	UPROPERTY(EditDefaultsOnly, Category = "Player|Dog")
	float DogSize;


	// Cat Specific Stats - editable in UE5 editor
	UPROPERTY(EditDefaultsOnly, Category = "Player|Cat")
	float CatSize;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Cat")
	float CatJumpHeight;

	
	// Otter Specific Stats - editable in UE5 editor
	UPROPERTY(EditDefaultsOnly, Category = "Player|Otter")
	float OtterSize;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Otter")
	float OtterSwimSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Otter")
	float OtterJumpHeight;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Otter")
	float OtterBreathHoldMaxDuration;


	// FlyingSquirrel Specific Stats - editable in UE5 editor
	UPROPERTY(EditDefaultsOnly, Category = "Player|FlyingSquirrel")
	float FlyingSquirrelSize;


	// Jerboa Specific Stats - editable in UE5 editor
	UPROPERTY(EditDefaultsOnly, Category = "Player|Jerboa")
	float JerboaSize;


	// Bird Specific Stats - editable in UE5 editor
	UPROPERTY(EditDefaultsOnly, Category = "Player|Bird")
	float BirdSize;
	
	UPROPERTY(EditDefaultsOnly, Category = "Player|Bird")
	float BirdSwimSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Bird")
	float BirdJumpHeight;

	// Updates Resistances (stored in GameInstance) when new unlocks are claimed
	UFUNCTION()
	void UpdateResistances();

	// Sets the characters stats and hitbox to that of the desired animal
	UFUNCTION()
	void SetStatsByAnimalSize(float AnimalSize);

	// Checks if there is room to switch to desired animal
	// Returns true if switching is possible, otherwise returns false
	UFUNCTION()
	bool CheckEnoughSpaceForAnimalSwitch(float AnimalSize);

	UFUNCTION()
	void PerformInteractionCheck();

	UFUNCTION()
	void StartHoldingBreath(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void StopHoldingBreath(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	UFUNCTION()
	void BreathHoldTimerUpdate();

	UFUNCTION()
	void ExhaustionTimerUpdate();

	UFUNCTION()
	void Perish();

	UFUNCTION()
	void LoadLastSaveGame();
};
