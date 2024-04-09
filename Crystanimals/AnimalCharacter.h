// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AnimalCharacter.generated.h"

UENUM(BlueprintType)
enum class ECurrentAnimal :uint8
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
	void SelectAnimal(ECurrentAnimal SelectedAnimal);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	UPROPERTY()
	bool bIsRunning = false;

	UPROPERTY(EditDefaultsOnly, Category = "Player|General")
	float SprintSpeedModifier;

	UPROPERTY()
	float WalkSpeed;


	// Default Dog Stats - editable in UE5 editor
	UPROPERTY(EditDefaultsOnly, Category = "Player|Dog")
	float DogWalkSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Dog")
	float DogSwimSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Dog")
	float DogJumpHeight;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Dog")
	bool DogCanGlide;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Dog")
	bool DogCanFly;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Dog")
	float DogCharacterSize;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Dog")
	float DogBreathHoldTime;


	// Default Cat Stats - editable in UE5 editor
	UPROPERTY(EditDefaultsOnly, Category = "Player|Cat")
	float CatWalkSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Cat")
	float CatSwimSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Cat")
	float CatJumpHeight;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Cat")
	bool CatCanGlide;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Cat")
	bool CatCanFly;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Cat")
	float CatCharacterSize;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Cat")
	float CatBreathHoldTime;


	// Default Otter Stats - editable in UE5 editor
	UPROPERTY(EditDefaultsOnly, Category = "Player|Otter")
	float OtterWalkSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Otter")
	float OtterSwimSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Otter")
	float OtterJumpHeight;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Otter")
	bool OtterCanGlide;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Otter")
	bool OtterCanFly;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Otter")
	float OtterCharacterSize;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Otter")
	float OtterBreathHoldTime;


	// Default FlyingSquirrel Stats - editable in UE5 editor
	UPROPERTY(EditDefaultsOnly, Category = "Player|FlyingSquirrel")
	float FlyingSquirrelWalkSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Player|FlyingSquirrel")
	float FlyingSquirrelSwimSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Player|FlyingSquirrel")
	float FlyingSquirrelJumpHeight;

	UPROPERTY(EditDefaultsOnly, Category = "Player|FlyingSquirrel")
	bool FlyingSquirrelCanGlide;

	UPROPERTY(EditDefaultsOnly, Category = "Player|FlyingSquirrel")
	bool FlyingSquirrelCanFly;

	UPROPERTY(EditDefaultsOnly, Category = "Player|FlyingSquirrel")
	float FlyingSquirrelCharacterSize;

	UPROPERTY(EditDefaultsOnly, Category = "Player|FlyingSquirrel")
	float FlyingSquirrelBreathHoldTime;


	// Default Jerboa Stats - editable in UE5 editor
	UPROPERTY(EditDefaultsOnly, Category = "Player|Jerboa")
	float JerboaWalkSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Jerboa")
	float JerboaSwimSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Jerboa")
	float JerboaJumpHeight;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Jerboa")
	bool JerboaCanGlide;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Jerboa")
	bool JerboaCanFly;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Jerboa")
	float JerboaCharacterSize;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Jerboa")
	float JerboaBreathHoldTime;


	// Default Bird Stats - editable in UE5 editor
	UPROPERTY(EditDefaultsOnly, Category = "Player|Bird")
	float BirdWalkSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Bird")
	float BirdSwimSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Bird")
	float BirdJumpHeight;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Bird")
	bool BirdCanGlide;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Bird")
	bool BirdCanFly;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Bird")
	float BirdCharacterSize;

	UPROPERTY(EditDefaultsOnly, Category = "Player|Bird")
	float BirdBreathHoldTime;
};
