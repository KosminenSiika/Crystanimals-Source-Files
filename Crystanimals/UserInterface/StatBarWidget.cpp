// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/StatBarWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UStatBarWidget::UpdateStatBar(float CurrentValue, float MaxValue)
{
	CurrentValueText->SetText(FText::FromString(FString::FromInt(ceil(CurrentValue))));

	MaxValueText->SetText(FText::FromString(FString::FromInt(ceil(MaxValue))));

	StatBar->SetPercent(CurrentValue / MaxValue);
}
