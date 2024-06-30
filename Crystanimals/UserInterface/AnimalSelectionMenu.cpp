// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/AnimalSelectionMenu.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "UserInterface/AnimalHUD.h"
#include "UserInterface/AnimalButtonWidget.h"
#include "Core/TreasureGameInstance.h"


void UAnimalSelectionMenu::NativeConstruct()
{
	Super::NativeConstruct();

	GameInstance = GetGameInstance<UTreasureGameInstance>();
	checkf(GameInstance, TEXT("AnimalSelectionMenu unable to get reference to GameInstance"));

	bClaimingUnlocks = false;
	UpdateButtons();
	bClaimingUnlocks = true;

	GameInstance->OnUnlocksClaimed.AddDynamic(this, &UAnimalSelectionMenu::UpdateButtons);

	// The editor absolutely did not let me set values in the graphical widget interface, 
	// so they just have to be set here...
	DogButton->AnimalName->SetText(FText::FromString("Dog"));
	DogButton->SetToolTipText(FText::FromString("Just a cute dog, the fastest runner"));
	CatButton->AnimalName->SetText(FText::FromString("Cat"));
	CatButton->SetToolTipText(FText::FromString("Jumps really high"));
	OtterButton->AnimalName->SetText(FText::FromString("Otter"));
	OtterButton->SetToolTipText(FText::FromString("Can hold breath for longer and swim a lot faster"));
	FlyingSquirrelButton->AnimalName->SetText(FText::FromString("Flying Squirrel"));
	FlyingSquirrelButton->SetToolTipText(FText::FromString("Can gently glide long distances"));
	JerboaButton->AnimalName->SetText(FText::FromString("Jerboa"));
	JerboaButton->SetToolTipText(FText::FromString("Is tiny, fits in very small places"));
	BirdButton->AnimalName->SetText(FText::FromString("Bird"));
	BirdButton->SetToolTipText(FText::FromString("Can FLY! The sky is the limit (spacebar to flap wings)"));
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

void UAnimalSelectionMenu::UpdateButtons()
{
	DogButton->SetGreyMaskVisibility(false);

	ToggleButtonHittable(CatButton, false);
	ToggleButtonHittable(OtterButton, false);
	ToggleButtonHittable(FlyingSquirrelButton, false);
	ToggleButtonHittable(JerboaButton, false);

	BirdButton->SetVisibility(ESlateVisibility::Collapsed);

	if (GameInstance->bNewUnlocksNotClaimed)
	{
		// This block is executed when there are new unlocks that have not been claimed
		if (GameInstance->Score >= 10+10)
		{
			ToggleButtonHittable(CatButton, true);
		}
		if (GameInstance->Score >= 30+10)
		{
			ToggleButtonHittable(OtterButton, true);
		}
		if (GameInstance->Score >= 50+10)
		{
			ToggleButtonHittable(FlyingSquirrelButton, true);
		}
		if (GameInstance->Score >= 60+10)
		{
			ToggleButtonHittable(JerboaButton, true);
		}
	}
	else
	{
		// This block is executed when there are no new unlocks AND when claiming new unlocks
		if (GameInstance->Score >= 10)
		{
			if (bClaimingUnlocks && GameInstance->Score < 20)
			{
				GetOwningPlayer()->GetHUD<AAnimalHUD>()->DisplayNowUnlockedWidget("Cat");
			}

			ToggleButtonHittable(CatButton, true);
		}
		if (GameInstance->Score >= 30)
		{
			if (bClaimingUnlocks && GameInstance->Score < 40)
			{
				GetOwningPlayer()->GetHUD<AAnimalHUD>()->DisplayNowUnlockedWidget("Otter");
			}

			ToggleButtonHittable(OtterButton, true);
		}
		if (GameInstance->Score >= 50)
		{
			if (bClaimingUnlocks && GameInstance->Score < 60)
			{
				GetOwningPlayer()->GetHUD<AAnimalHUD>()->DisplayNowUnlockedWidget("Flying Squirrel");
			}

			ToggleButtonHittable(FlyingSquirrelButton, true);
		}
		if (GameInstance->Score >= 60)
		{
			if (bClaimingUnlocks && GameInstance->Score < 70)
			{
				GetOwningPlayer()->GetHUD<AAnimalHUD>()->DisplayNowUnlockedWidget("Jerboa");
			}

			ToggleButtonHittable(JerboaButton, true);
		}
		if (GameInstance->Score >= 80)
		{
			if (bClaimingUnlocks)
			{
				GetOwningPlayer()->GetHUD<AAnimalHUD>()->DisplayNowUnlockedWidget("Secret Animal - Bird");
			}

			ToggleButtonHittable(BirdButton, true);
		}
	}
}
