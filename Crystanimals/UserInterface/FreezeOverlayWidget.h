// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FreezeOverlayWidget.generated.h"

// Forward Declarations
class UImage;

/**
 * 
 */
UCLASS()
class CRYSTANIMALS_API UFreezeOverlayWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	UFUNCTION()
	void SetOverlayOpacity(float InOpacity);

	UFUNCTION()
	void FadeOpacityToZero(float InOpacity);

private:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UImage> OverlayImage = nullptr;

	UPROPERTY()
	FTimerHandle FadeTimer;

	UPROPERTY()
	float FadeStartTime;

	UPROPERTY()
	float MaxOpacity;

	UFUNCTION()
	void UpdateOpacity();
	

	virtual void NativeConstruct() override;
};
