// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/ScoreWidget.h"
#include "Components/TextBlock.h"
#include "Core/TreasureGameInstance.h"

void UScoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameInstance = GetGameInstance<UTreasureGameInstance>();
	checkf(GameInstance, TEXT("ScoreWidget unable to get reference to GameInstance"));

	UpdateScoreText();

	GameInstance->OnScoreUpdated.AddDynamic(this, &UScoreWidget::UpdateScoreText);
}

void UScoreWidget::UpdateScoreText()
{
	if (ScoreText)
	{
		ScoreText->SetText(FText::FromString(FString::FromInt(GameInstance->Score)));
	}
}


