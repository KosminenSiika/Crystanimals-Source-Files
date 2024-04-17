// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AnimalSelectionMenu.generated.h"

// Forward Declarations
class UAnimalButtonWidget;

/**
 * 
 */
UCLASS()
class CRYSTANIMALS_API UAnimalSelectionMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void UpdateButtons(int Score);

private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UAnimalButtonWidget> DogButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UAnimalButtonWidget> CatButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UAnimalButtonWidget> OtterButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UAnimalButtonWidget> FlyingSquirrelButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UAnimalButtonWidget> JerboaButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UAnimalButtonWidget> BirdButton;

	void ToggleButtonHittable(UAnimalButtonWidget* Button, bool IsHittable);

	virtual void NativeConstruct() override;
};
