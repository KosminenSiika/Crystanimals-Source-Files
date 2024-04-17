// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AnimalSelectionMenu.generated.h"

// Forward Declarations
class UButton;
class AAnimalCharacter;

/**
 * 
 */
UCLASS()
class CRYSTANIMALS_API UAnimalSelectionMenu : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	TObjectPtr<AAnimalCharacter> PlayerCharacter;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> DogButton;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> CatButton;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> OtterButton;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> FlyingSquirrelButton;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> JerboaButton;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> BirdButton;

	UFUNCTION()
	void SwitchToDog();
	UFUNCTION()
	void SwitchToCat();
	UFUNCTION()
	void SwitchToOtter();
	UFUNCTION()
	void SwitchToFlyingSquirrel();
	UFUNCTION()
	void SwitchToJerboa();
	UFUNCTION()
	void SwitchToBird();

	virtual void NativeConstruct() override;
};
