// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AnimalHUD.generated.h"

// Forward Declarations
class UMainMenu;
class UAnimalSelectionMenu;
class UInteractionWidget;
class UStaticWidgetBase;
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

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UStaticWidgetBase> OutOfBoundsWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UStaticWidgetBase> CrosshairClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UStaticWidgetBase> NewUnlocksWidgetClass;

	bool bIsMainMenuVisible;

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

	UFUNCTION()
	void DisplayOutOfBoundsWidget() const;
	UFUNCTION()
	void HideOutOfBoundsWidget() const;

	UFUNCTION()
	void DisplayCrosshair() const;
	UFUNCTION()
	void HideCrosshair() const;

	UFUNCTION()
	void DisplayNewUnlocksWidget() const;
	UFUNCTION()
	void HideNewUnlocksWidget() const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<UMainMenu> MainMenuWidget;

	UPROPERTY()
	TObjectPtr<UAnimalSelectionMenu> AnimalSelectionMenuWidget;

	UPROPERTY()
	TObjectPtr<UInteractionWidget> InteractionWidget;

	UPROPERTY()
	TObjectPtr<UStaticWidgetBase> OutOfBoundsWidget;

	UPROPERTY()
	TObjectPtr<UStaticWidgetBase> Crosshair;

	UPROPERTY()
	TObjectPtr<UStaticWidgetBase> NewUnlocksWidget;
	
};
