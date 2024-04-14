// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AnimalHUD.generated.h"

// Forward Declarations
class UMainMenu;
class UAnimalSelectionMenu;
class UInteractionWidget;
struct FInteractableData;

/**
 * 
 */
UCLASS()
class CRYSTANIMALS_API AAnimalHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UMainMenu> MainMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UAnimalSelectionMenu> AnimalSelectionMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UInteractionWidget> InteractionWidgetClass;

	bool bIsMainMenuVisible;
	bool bIsAnimalSelectionMenuVisible;

	AAnimalHUD();

	UFUNCTION()
	void DisplayMainMenu();
	UFUNCTION()
	void HideMainMenu();

	UFUNCTION()
	void DisplayAnimalSelectionMenu();
	UFUNCTION()
	void HideAnimalSelectionMenu();

	UFUNCTION()
	void DisplayInteractionWidget() const;
	UFUNCTION()
	void HideInteractionWidget() const;
	UFUNCTION()
	void UpdateInteractionWidget(const FInteractableData InteractableData) const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<UMainMenu> MainMenuWidget;

	UPROPERTY()
	TObjectPtr<UAnimalSelectionMenu> AnimalSelectionMenuWidget;

	UPROPERTY()
	TObjectPtr<UInteractionWidget> InteractionWidget;
	
};
