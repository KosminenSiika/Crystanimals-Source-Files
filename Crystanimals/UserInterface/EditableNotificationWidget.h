// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EditableNotificationWidget.generated.h"

// Forward Declarations
class UTextBlock;

/**
 * 
 */
UCLASS()
class CRYSTANIMALS_API UEditableNotificationWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UFUNCTION()
	void UpdateNotificationText(FString TextToDisplay);

private:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> NotificationText = nullptr;
};
