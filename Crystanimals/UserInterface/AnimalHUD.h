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
class UScoreWidget;
class UConfirmationWidget;
struct FInteractableData;

/**
 * 
 */
UCLASS()
class CRYSTANIMALS_API AAnimalHUD : public AHUD
{
	GENERATED_BODY()

public:

	// These are defined in the editor as WidgetBlueprints with actual graphics
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UMainMenu> MainMenuClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UAnimalSelectionMenu> AnimalSelectionMenuClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UInteractionWidget> InteractionWidgetClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UStaticWidgetBase> OutOfBoundsWidgetClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UStaticWidgetBase> CrosshairClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UStaticWidgetBase> NewUnlocksWidgetClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UStaticWidgetBase> NotEnoughSpaceWidgetClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UScoreWidget> ScoreWidgetClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UConfirmationWidget> ConfirmationWidgetClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UStaticWidgetBase> GameSavedWidgetClass = nullptr;


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
	UFUNCTION()
	bool InteractionWidgetIsVisible();

	UFUNCTION()
	void DisplayOutOfBoundsWidget() const;
	UFUNCTION()
	void HideOutOfBoundsWidget() const;

	UFUNCTION()
	void DisplayCrosshair() const;
	UFUNCTION()
	void HideCrosshair() const;

	UFUNCTION()
	void DisplayNewUnlocksWidget();
	UFUNCTION()
	void HideNewUnlocksWidget();

	UFUNCTION()
	void DisplayNotEnoughSpaceWidget() const;

	UFUNCTION()
	void HideNotEnoughSpaceWidget() const;

	UFUNCTION()
	void DisplayConfirmationWidget(FString Action);

	UFUNCTION()
	void DisplayGameSavedWidget();

	UFUNCTION()
	void HideGameSavedWidget() const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<UMainMenu> MainMenuWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UAnimalSelectionMenu> AnimalSelectionMenuWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UInteractionWidget> InteractionWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UStaticWidgetBase> OutOfBoundsWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UStaticWidgetBase> Crosshair = nullptr;

	UPROPERTY()
	TObjectPtr<UStaticWidgetBase> NewUnlocksWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UStaticWidgetBase> NotEnoughSpaceWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UScoreWidget> ScoreWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UConfirmationWidget> ConfirmationWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UStaticWidgetBase> GameSavedWidget = nullptr;


	UPROPERTY()
	TObjectPtr<UTreasureGameInstance> GameInstance = nullptr;
	
};
