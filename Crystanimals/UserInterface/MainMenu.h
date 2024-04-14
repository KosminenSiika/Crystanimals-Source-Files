// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class CRYSTANIMALS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

private:
	UFUNCTION()
	void ResetGameProgress();
	void ExitGame();
	
};