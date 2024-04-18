// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TreasureGameInstance.generated.h"

// Forward Declarations
enum class EAnimal : uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FScoreUpdated);

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

	UFUNCTION()
	void ChangeRealm(FName RealmName);

private:
	virtual void OnStart() override;
};
