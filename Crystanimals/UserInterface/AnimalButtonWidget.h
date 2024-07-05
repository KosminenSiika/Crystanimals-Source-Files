// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AnimalButtonWidget.generated.h"

// Forward Declarations
class UButton;
class UBorder;
class UTextBlock;
class AAnimalPlayerController;
enum class EAnimal : uint8;

/**
 * 
 */
UCLASS()
class CRYSTANIMALS_API UAnimalButtonWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditInstanceOnly, Category = "Animal")
	EAnimal DesiredAnimal;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> AnimalName = nullptr;

	UFUNCTION()
	void SetGreyMaskVisibility(bool ShouldBeVisible);

private:
	UPROPERTY()
	TObjectPtr<AAnimalPlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> AnimalButton = nullptr;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UBorder> GreyMask = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TObjectPtr<USoundBase> ButtonClickSound = nullptr;

	UFUNCTION()
	void SwitchToAnimal();

	virtual void NativeConstruct() override;
};
