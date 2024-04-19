// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ConfirmationWidget.generated.h"

// Forward Declaration
class UTextBlock;
class UButton;
class UTreasureGameInstance;

/**
 * 
 */
UCLASS()
class CRYSTANIMALS_API UConfirmationWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> Action = nullptr;

	UFUNCTION()
	void SetAction(FString ActionToSet);
	
private:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> YesButton = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> NoButton = nullptr;

	UPROPERTY()
	TObjectPtr<UTreasureGameInstance> GameInstance = nullptr;

	UFUNCTION()
	void ConfirmAction();

	UFUNCTION()
	void CancelAction();

	virtual void NativeConstruct() override;
};
