// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/InteractionInterface.h"
#include "AnimalCharacter.generated.h"

// Forward Declarations
class UCameraComponent;
class AAnimalHUD;

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
	// Sets default values for this character's properties
	AAnimalCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Interact();

	UFUNCTION()
	bool OpenCloseMainMenu();

	UFUNCTION()
	void OpenCloseAnimalSelectionMenu(bool ShouldOpen);

	UFUNCTION()
	void SetRunning(bool IsRunning);

	// Tries to switch the character to the desired animal
	UFUNCTION()
	void SwitchAnimal(EAnimal SelectedAnimal);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	UPROPERTY(VisibleAnywhere, Category="Player|Camera")
	TObjectPtr<UCameraComponent> FirstPersonCamera;

	UPROPERTY(VisibleAnywhere, Category = "Player|Collision")
	TObjectPtr<UCapsuleComponent> Hitbox;

	UPROPERTY(VisibleAnywhere, Category = "Player|Collision")
	TObjectPtr<UCapsuleComponent> CollisionTestVolume;

	UPROPERTY()
	TObjectPtr<AAnimalHUD> HUD;

	// Interaction
	UPROPERTY(VisibleAnywhere, Category="Player|Interaction")
	TScriptInterface<IInteractionInterface> TargetInteractable;

	UPROPERTY(VisibleAnywhere, Category = "Player|Interaction")
	float InteractionCheckFrequency;

	UPROPERTY(VisibleAnywhere, Category = "Player|Interaction")
	float InteractionCheckDistance;

	UPROPERTY(VisibleAnywhere, Category = "Player|Interaction")
	FInteractionData InteractionData;

	// Movement
	UPROPERTY()
	bool bIsRunning = false;

	UPROPERTY(EditDefaultsOnly, Category = "Player|General")
	float SprintSpeedModifier;
	
	UPROPERTY()
	float WalkSpeed;

	UPROPERTY()
	float SwimSpeed;


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
	float OtterBreathHoldTime;


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

	// Sets the characters stats and hitbox to that of the desired animal
	UFUNCTION()
	void SetStatsByAnimalSize(float AnimalSize);

	// Checks if there is room to switch to desired animal
	// Returns true if switching is possible, otherwise returns false
	UFUNCTION()
	bool CheckEnoughSpaceForAnimalSwitch(float AnimalSize);

	UFUNCTION()
	void PerformInteractionCheck();
};
