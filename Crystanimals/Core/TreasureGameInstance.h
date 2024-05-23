// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TreasureGameInstance.generated.h"

// Forward Declarations
enum class EAnimal : uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FScoreUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUnlocksClaimed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameSaved);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAnimalSwitched);

UCLASS()
class CRYSTANIMALS_API UTreasureGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
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
	bool bIsTrapdoorOpen;

	UPROPERTY()
	float MouseSens;

	UPROPERTY()
	bool bShouldSaveAfterRealmChange;

	UPROPERTY()
	FScoreUpdated OnScoreUpdated;

	UPROPERTY()
	FUnlocksClaimed OnUnlocksClaimed;

	UPROPERTY()
	FGameSaved OnGameSaved;

	UPROPERTY()
	FAnimalSwitched OnAnimalSwitched;

	UFUNCTION()
	void ChangeRealm(FName RealmName);

	UFUNCTION()
	void SaveGame();

	UFUNCTION()
	void LoadSaveGame();

	UFUNCTION()
	void ResetGame();

	UFUNCTION()
	void ExitGame();

private:
	UFUNCTION()
	void LoadDefaultDataValues();

	UFUNCTION()
	void NotifyGameSaved(const FString& SlotName, const int32 UserIndex, bool bSuccess);

	virtual void Init() override;
};
