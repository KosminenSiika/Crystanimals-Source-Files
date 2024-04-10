// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AnimalCharacter.generated.h"

// Forward Declarations
class UCameraComponent;

UENUM(BlueprintType)
enum class EAnimal :uint8
{
	Dog,
	Cat,
	Otter,
	FlyingSquirrel,
	Jerboa,
	Bird
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
	void SetRunning(bool IsRunning);

	UFUNCTION()
	void SelectAnimal(EAnimal SelectedAnimal);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	UPROPERTY(VisibleAnywhere, Category="Player|Camera")
	TObjectPtr<UCameraComponent> FirstPersonCamera;



	UPROPERTY()
	bool bIsRunning = false;

	UPROPERTY(EditDefaultsOnly, Category = "Player|General")
	float SprintSpeedModifier;

	
	UPROPERTY()
	float WalkSpeed;

	UPROPERTY()
	float SwimSpeed;

	
	// TODO: MAKE WALKSPEED, SWIMSPEED, JUMPHEIGHT, GLIDE, FLY AND BREATH DEFAULTS AND ONLY MAKE SPECIAL VARIABLES FOR THE ANIMALS THAT CHANGE THEM

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


	UFUNCTION()
	void SetStatsByAnimalSize(float AnimalSize);

};
