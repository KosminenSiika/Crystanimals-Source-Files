// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TreasureGameInstance.generated.h"

// Forward Declarations
enum class EAnimal : uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FScoreUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUnlocksClaimed);

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
	bool bIsTrapdoorOpen;

	UPROPERTY()
	float MouseSens;

	UPROPERTY()
	FScoreUpdated OnScoreUpdated;

	UPROPERTY()
	FUnlocksClaimed OnUnlocksClaimed;

	UFUNCTION()
	void ChangeRealm(FName RealmName);

	UFUNCTION()
	void SaveGame();

	UFUNCTION()
	void ResetGameProgress();

private:
	UFUNCTION()
	void LoadDefaultDataValues();

	UFUNCTION()
	void NotifyGameSaved(const FString& SlotName, const int32 UserIndex, bool bSuccess);

	virtual void OnStart() override;
};
