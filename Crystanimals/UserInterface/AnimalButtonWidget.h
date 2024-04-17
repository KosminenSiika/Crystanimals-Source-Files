// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AnimalButtonWidget.generated.h"

// Forward Declarations
class UButton;
class UBorder;
class UTextBlock;
class AAnimalCharacter;
class AAnimalPlayerController;

/**
 * 
 */
UCLASS()
class CRYSTANIMALS_API UAnimalButtonWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditInstanceOnly, Category = "Animal")
	FText DesiredAnimal;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> AnimalName;

	UFUNCTION()
	void SetGreyMaskVisibility(bool ShouldBeVisible);

private:
	UPROPERTY()
	TObjectPtr<AAnimalPlayerController> PlayerController;

	UPROPERTY()
	TObjectPtr<AAnimalCharacter> PlayerCharacter;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> AnimalButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UBorder> GreyMask;

	UFUNCTION()
	void SwitchToAnimal();


	

	virtual void NativeConstruct() override;
};
