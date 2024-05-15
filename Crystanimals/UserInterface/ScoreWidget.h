// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

// Forward Declarations
class UTextBlock;
class UImage;

/**
 * 
 */
UCLASS()
class CRYSTANIMALS_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()
	

private:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> ScoreText = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UImage> CurrentAnimalIcon = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "AnimalImages")
	TObjectPtr<UTexture2D> DogImage = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "AnimalImages")
	TObjectPtr<UTexture2D> CatImage = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "AnimalImages")
	TObjectPtr<UTexture2D> OtterImage = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "AnimalImages")
	TObjectPtr<UTexture2D> FlyingSquirrelImage = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "AnimalImages")
	TObjectPtr<UTexture2D> JerboaImage = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "AnimalImages")
	TObjectPtr<UTexture2D> BirdImage = nullptr;


	UPROPERTY()
	TObjectPtr<UTreasureGameInstance> GameInstance = nullptr;

	UFUNCTION()
	void UpdateScoreText();

	UFUNCTION()
	void UpdateAnimalIcon();

	virtual void NativeConstruct() override;
	
};
