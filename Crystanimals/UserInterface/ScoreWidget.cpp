// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/ScoreWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Core/TreasureGameInstance.h"
#include "Player/AnimalCharacter.h"

void UScoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameInstance = GetGameInstance<UTreasureGameInstance>();
	checkf(GameInstance, TEXT("ScoreWidget unable to get reference to GameInstance"));

	UpdateScoreText();

	GameInstance->OnScoreUpdated.AddDynamic(this, &UScoreWidget::UpdateScoreText);
	GameInstance->OnAnimalSwitched.AddDynamic(this, &UScoreWidget::UpdateAnimalIcon);
}

void UScoreWidget::UpdateScoreText()
{
	if (ScoreText)
	{
		ScoreText->SetText(FText::FromString(FString::FromInt(GameInstance->Score)));
	}
}

void UScoreWidget::UpdateAnimalIcon()
{
	if (CurrentAnimalIcon)
	{
		switch (GameInstance->CurrentAnimal)
		{
			case EAnimal::Cat:
				if (CatImage)
				{
					CurrentAnimalIcon->SetBrushFromTexture(CatImage);
				}
				break;

			case EAnimal::Otter:
				if (OtterImage)
				{
					CurrentAnimalIcon->SetBrushFromTexture(OtterImage);
				}
				break;

			case EAnimal::FlyingSquirrel:
				if (FlyingSquirrelImage)
				{
					CurrentAnimalIcon->SetBrushFromTexture(FlyingSquirrelImage);
				}
				break;

			case EAnimal::Jerboa:
				if (JerboaImage)
				{
					CurrentAnimalIcon->SetBrushFromTexture(JerboaImage);
				}
				break;

			case EAnimal::Bird:
				if (BirdImage)
				{
					CurrentAnimalIcon->SetBrushFromTexture(BirdImage);
				}
				break;

			default:
				if (DogImage)
				{
					CurrentAnimalIcon->SetBrushFromTexture(DogImage);
				}
				break;
		}
	}
}