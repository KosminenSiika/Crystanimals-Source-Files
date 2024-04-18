// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionWidget.generated.h"

// Forward Declarations
class AAnimalCharacter;
struct FInteractableData;
class UTextBlock;

/**
 * 
 */
UCLASS()
class CRYSTANIMALS_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateWidget(const FInteractableData InteractableData) const;

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> NameText = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> ActionText = nullptr;

};
