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

	// The editor absolutely did not let me set values in the graphical widget interface, 
	// so they just have to be set here...
	DogButton->AnimalName->SetText(FText::FromString("Dog"));
	DogButton->SetToolTipText(FText::FromString("Just a cute dog, the fastest runner"));
	CatButton->AnimalName->SetText(FText::FromString("Cat"));
	CatButton->SetToolTipText(FText::FromString("Jumps really high"));
	OtterButton->AnimalName->SetText(FText::FromString("Otter"));
	OtterButton->SetToolTipText(FText::FromString("Can hold breath for longer and swim a lot faster"));
	FlyingSquirrelButton->AnimalName->SetText(FText::FromString("Flying Squirrel"));
	FlyingSquirrelButton->SetToolTipText(FText::FromString("Can glide long distances"));
	JerboaButton->AnimalName->SetText(FText::FromString("Jerboa"));
	JerboaButton->SetToolTipText(FText::FromString("Is tiny, fits in very small places"));
	BirdButton->AnimalName->SetText(FText::FromString("Bird"));
	BirdButton->SetToolTipText(FText::FromString("Can FLY! The sky is the limit (spacebar to flap wings)"));


	bClaimingUnlocks = false;
	UpdateButtons();
	bClaimingUnlocks = true;

	GameInstance->OnUnlocksClaimed.AddDynamic(this, &UAnimalSelectionMenu::UpdateButtons);
}

void UAnimalSelectionMenu::UpdateButtons()
{
	DogButton->ToggleHittable(true);

	CatButton->ToggleHittable(false);
	OtterButton->ToggleHittable(false);
	FlyingSquirrelButton->ToggleHittable(false);
	JerboaButton->ToggleHittable(false);

	BirdButton->SetVisibility(ESlateVisibility::Collapsed);

	if (GameInstance->bNewUnlocksNotClaimed)
	{
		// This block is executed when there are new unlocks that have not been claimed
		if (GameInstance->Score >= 10+10)
		{
			CatButton->ToggleHittable(true);
		}
		if (GameInstance->Score >= 30+10)
		{
			OtterButton->ToggleHittable(true);
		}
		if (GameInstance->Score >= 50+10)
		{
			FlyingSquirrelButton->ToggleHittable(true);
		}
		if (GameInstance->Score >= 60+10)
		{
			JerboaButton->ToggleHittable(true);
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

			CatButton->ToggleHittable(true);
		}
		if (GameInstance->Score >= 30)
		{
			if (bClaimingUnlocks && GameInstance->Score < 40)
			{
				GetOwningPlayer()->GetHUD<AAnimalHUD>()->DisplayNowUnlockedWidget("Otter");
			}

			OtterButton->ToggleHittable(true);
		}
		if (GameInstance->Score >= 50)
		{
			if (bClaimingUnlocks && GameInstance->Score < 60)
			{
				GetOwningPlayer()->GetHUD<AAnimalHUD>()->DisplayNowUnlockedWidget("Flying Squirrel");
			}

			FlyingSquirrelButton->ToggleHittable(true);
		}
		if (GameInstance->Score >= 60)
		{
			if (bClaimingUnlocks && GameInstance->Score < 70)
			{
				GetOwningPlayer()->GetHUD<AAnimalHUD>()->DisplayNowUnlockedWidget("Jerboa");
			}

			JerboaButton->ToggleHittable(true);
		}
		if (GameInstance->Score >= 80)
		{
			if (bClaimingUnlocks)
			{
				GetOwningPlayer()->GetHUD<AAnimalHUD>()->DisplayNowUnlockedWidget("Secret Animal - Bird");
			}

			BirdButton->SetVisibility(ESlateVisibility::Visible);
			BirdButton->ToggleHittable(true);
		}
	}
}
