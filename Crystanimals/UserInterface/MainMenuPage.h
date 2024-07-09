// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuPage.generated.h"

// Forward Declarations
class UButton;

/**
 * 
 */
UCLASS()
class CRYSTANIMALS_API UMainMenuPage : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> OkButton = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TObjectPtr<USoundBase> ButtonClickSound = nullptr;


	UFUNCTION()
	void ClosePage();

	virtual void NativeConstruct() override;
};
