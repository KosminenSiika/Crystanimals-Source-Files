// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AnimalPlayerController.generated.h"

// Forward Declarations
class UInputAction;
class UInputMappingContext;
class AAnimalCharacter;
class UEnhancedInputComponent;
struct FInputActionValue;

UCLASS()
class CRYSTANIMALS_API AAnimalPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// The Input Action to map to movement.
	UPROPERTY(EditDefaultsOnly, Category = "Player Input|Character Movement")
	TObjectPtr<UInputAction> ActionMove = nullptr;

	// The Input Action to map to looking around.
	UPROPERTY(EditDefaultsOnly, Category = "Player Input|Character Movement")
	TObjectPtr<UInputAction> ActionLook = nullptr;

	// The Input Action to map to jumping.
	UPROPERTY(EditDefaultsOnly, Category = "Player Input|Character Movement")
	TObjectPtr<UInputAction> ActionJump = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Player Input|Character Movement")
	TObjectPtr<UInputAction> ActionHoldSprint = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Player Input|Interaction")
	TObjectPtr<UInputAction> ActionInteract = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Player Input|Menu")
	TObjectPtr<UInputAction> ActionOpenCloseMainMenu = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Player Input|Menu")
	TObjectPtr<UInputAction> ActionOpenCloseAnimalSelectionMenu = nullptr;

	// The Input Mapping Context to use.
	UPROPERTY(EditDefaultsOnly, Category = "Player Input|Character Movement")
	TObjectPtr<UInputMappingContext> InputMappingContext = nullptr;

	void HandleCloseAnimalSelectionMenu();

protected:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

	void HandleLook(const FInputActionValue& InputActionValue);
	void HandleMove(const FInputActionValue& InputActionValue);
	void HandleHoldSprint();
	void HandleStopHoldingSprint();
	void HandleJump();
	void HandleInteract();
	void HandleOpenCloseMainMenu();
	void HandleOpenAnimalSelectionMenu();

private:
	// Used to store a reference to the InputComponent cast to an EnhancedInputComponent.
	UPROPERTY()
	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = nullptr;

	// Used to store a reference to the controlled pawn.
	UPROPERTY()
	TObjectPtr<AAnimalCharacter> PlayerCharacter = nullptr;
	
};
