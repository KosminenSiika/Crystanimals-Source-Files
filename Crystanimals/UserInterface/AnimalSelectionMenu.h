// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AnimalSelectionMenu.generated.h"

// Forward Declarations
class UAnimalButtonWidget;
class UTreasureGameInstance;

/**
 * 
 */
UCLASS()
class CRYSTANIMALS_API UAnimalSelectionMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void UpdateButtons();

private:
	UPROPERTY()
	bool bClaimingUnlocks;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UAnimalButtonWidget> DogButton = nullptr;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UAnimalButtonWidget> CatButton = nullptr;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UAnimalButtonWidget> OtterButton = nullptr;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UAnimalButtonWidget> FlyingSquirrelButton = nullptr;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UAnimalButtonWidget> JerboaButton = nullptr;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UAnimalButtonWidget> BirdButton = nullptr;

	UPROPERTY()
	TObjectPtr<UTreasureGameInstance> GameInstance = nullptr;

	void ToggleButtonHittable(UAnimalButtonWidget* Button, bool IsHittable);

	virtual void NativeConstruct() override;
};
