// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

// Forward Declarations
class UTextBlock;

/**
 * 
 */
UCLASS()
class CRYSTANIMALS_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> ScoreText = nullptr;

	UPROPERTY()
	TObjectPtr<UTreasureGameInstance> GameInstance = nullptr;

	UFUNCTION()
	void UpdateScoreText();

	virtual void NativeConstruct() override;
	
};
