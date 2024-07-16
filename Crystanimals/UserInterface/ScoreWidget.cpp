// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/ScoreWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/HorizontalBox.h"
#include "Core/TreasureGameInstance.h"
#include "Player/AnimalCharacter.h"

void UScoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameInstance = GetGameInstance<UTreasureGameInstance>();
	checkf(GameInstance, TEXT("ScoreWidget unable to get reference to GameInstance"));

	UpdateScoreTexts();

	GameInstance->OnScoreUpdated.AddDynamic(this, &UScoreWidget::UpdateScoreTexts);
	GameInstance->OnAnimalSwitched.AddDynamic(this, &UScoreWidget::UpdateAnimalIcon);

	if (GameInstance->CurrentRealm == "HubRealm")
	{
		RealmScoreBox->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UScoreWidget::UpdateScoreTexts()
{
	if (ScoreText && RealmScoreText)
	{
		int RealmScore = 0;
		int Counter = 1;
		int CounterMax = 0;

		if (GameInstance->CurrentRealm == "OutbackRealm")
		{
			Counter = 1;
			CounterMax = 20;
		}
		else if (GameInstance->CurrentRealm == "CaribbeanRealm")
		{
			Counter = 21;
			CounterMax = 40;
		}
		else if (GameInstance->CurrentRealm == "DesertRealm")
		{
			Counter = 41;
			CounterMax = 60;
		}
		else if (GameInstance->CurrentRealm == "ArcticRealm")
		{
			Counter = 61;
			CounterMax = 80;
		}

		for (; Counter <= CounterMax; Counter++)
		{
			if (!GameInstance->ExistingCrystals.Contains(FString::FromInt(Counter)))
			{
				RealmScore++;
			}
		}

		ScoreText->SetText(FText::FromString(FString::FromInt(GameInstance->Score)));
		RealmScoreText->SetText(FText::FromString(FString::FromInt(RealmScore)));
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