// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TreasureSaveGame.generated.h"

// Forward Declarations
enum class EAnimal : uint8;

/**
 * 
 */
UCLASS()
class CRYSTANIMALS_API UTreasureSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString SaveSlotName;

	UPROPERTY()
	uint32 UserIndex;


	UPROPERTY()
	TArray<FString> ExistingCrystals;

	UPROPERTY()
	int Score;

	UPROPERTY()
	EAnimal CurrentAnimal;

	UPROPERTY()
	FName CurrentRealm;

	UPROPERTY()
	bool bHasHeatResistance;

	UPROPERTY()
	bool bHasColdResistance;

	UPROPERTY()
	bool bNewUnlocksNotClaimed;

	UPROPERTY()
	bool bHasKey;

	UPROPERTY()
	bool bIsTrapdoorOpen;

	UPROPERTY()
	float MouseSens;


	UTreasureSaveGame();
	
};
