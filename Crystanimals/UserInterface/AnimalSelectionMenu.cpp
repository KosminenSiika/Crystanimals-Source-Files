// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/AnimalSelectionMenu.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Player/AnimalCharacter.h"
#include "UserInterface/AnimalButtonWidget.h"


void UAnimalSelectionMenu::NativeConstruct()
{
	Super::NativeConstruct();

	// REPLACE WITH SCORE FROM GAMEINSTANCE WHEN ONSCOREUPDATED BROADCASTS
	UpdateButtons(80);

	// The editor absolutely did not let me set values in the graphical widget interface, 
	// so they just have to be set here...
	DogButton->AnimalName->SetText(FText::FromString("Dog"));
	DogButton->SetToolTipText(FText::FromString("Just a cute dog"));
	CatButton->AnimalName->SetText(FText::FromString("Cat"));
	CatButton->SetToolTipText(FText::FromString("Can jump really high"));
	OtterButton->AnimalName->SetText(FText::FromString("Otter"));
	OtterButton->SetToolTipText(FText::FromString("Can hold breath for longer and swim a lot faster"));
	FlyingSquirrelButton->AnimalName->SetText(FText::FromString("Flying Squirrel"));
	FlyingSquirrelButton->SetToolTipText(FText::FromString("Can glide down from high places"));
	JerboaButton->AnimalName->SetText(FText::FromString("Jerboa"));
	JerboaButton->SetToolTipText(FText::FromString("Is tiny, so can fit in places others cannot"));
	BirdButton->AnimalName->SetText(FText::FromString("Bird"));
	BirdButton->SetToolTipText(FText::FromString("Can FLY! The sky is the limit"));
}

void UAnimalSelectionMenu::ToggleButtonHittable(UAnimalButtonWidget* Button, bool IsHittable)
{
	if (IsHittable)
	{
		Button->SetGreyMaskVisibility(false);
		Button->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Button->SetGreyMaskVisibility(true);
		Button->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}

void UAnimalSelectionMenu::UpdateButtons(int Score)
{
	DogButton->SetGreyMaskVisibility(false);

	ToggleButtonHittable(CatButton, false);
	ToggleButtonHittable(OtterButton, false);
	ToggleButtonHittable(FlyingSquirrelButton, false);
	ToggleButtonHittable(JerboaButton, false);

	BirdButton->SetVisibility(ESlateVisibility::Collapsed);

	if (Score >= 10)
	{
		ToggleButtonHittable(CatButton, true);
	}
	if (Score >= 30)
	{
		ToggleButtonHittable(OtterButton, true);
	}
	if (Score >= 50)
	{
		ToggleButtonHittable(FlyingSquirrelButton, true);
	}
	if (Score >= 60)
	{
		ToggleButtonHittable(JerboaButton, true);
	}
	if (Score >= 80)
	{
		ToggleButtonHittable(BirdButton, true);
	}
}
