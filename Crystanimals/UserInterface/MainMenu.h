// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class CRYSTANIMALS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> ResetButton;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> ExitButton;

	UFUNCTION()
	void ResetGameProgress();
	UFUNCTION()
	void ExitGame();
	
	virtual void NativeConstruct() override;
};
