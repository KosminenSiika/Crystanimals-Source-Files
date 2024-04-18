// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/AnimalButtonWidget.h"
#include "Components/Button.h"
#include "Components/Border.h"
#include "Player/AnimalCharacter.h"
#include "Player/AnimalPlayerController.h"

void UAnimalButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerController = Cast<AAnimalPlayerController>(GetWorld()->GetFirstPlayerController());
	checkf(PlayerController, TEXT("AnimalSelectionMenu could not get a reference to the PlayerController"));
	PlayerCharacter = Cast<AAnimalCharacter>(PlayerController->GetPawn());
	checkf(PlayerCharacter, TEXT("AnimalSelectionMenu could not get a reference to the PlayerCharacter"));

	if (AnimalButton)
	{
		AnimalButton->OnClicked.AddDynamic(this, &UAnimalButtonWidget::SwitchToAnimal);
	}
}

void UAnimalButtonWidget::SwitchToAnimal()
{
	if (PlayerCharacter)
	{
		if (DesiredAnimal.ToString() == FString("Dog"))
		{
			PlayerController->HandleOpenCloseAnimalSelectionMenu();
			PlayerCharacter->SwitchAnimal(EAnimal::Dog);
			return;
		}

		if (DesiredAnimal.ToString() == FString("Cat"))
		{
			PlayerController->HandleOpenCloseAnimalSelectionMenu();
			PlayerCharacter->SwitchAnimal(EAnimal::Cat);
			return;
		}

		if (DesiredAnimal.ToString() == FString("Otter"))
		{
			PlayerController->HandleOpenCloseAnimalSelectionMenu();
			PlayerCharacter->SwitchAnimal(EAnimal::Otter);
			return;
		}

		if (DesiredAnimal.ToString() == FString("FlyingSquirrel"))
		{
			PlayerController->HandleOpenCloseAnimalSelectionMenu();
			PlayerCharacter->SwitchAnimal(EAnimal::FlyingSquirrel);
			return;
		}

		if (DesiredAnimal.ToString() == FString("Jerboa"))
		{
			PlayerController->HandleOpenCloseAnimalSelectionMenu();
			PlayerCharacter->SwitchAnimal(EAnimal::Jerboa);
			return;
		}

		if (DesiredAnimal.ToString() == FString("Bird"))
		{
			PlayerController->HandleOpenCloseAnimalSelectionMenu();
			PlayerCharacter->SwitchAnimal(EAnimal::Bird);
			return;
		}

		UE_LOG(LogTemp, Warning, TEXT("AnimalButton didn't switch to any animal, check DesiredAnimal spellings"))
	}
}

void UAnimalButtonWidget::SetGreyMaskVisibility(bool ShouldBeVisible)
{
	if (ShouldBeVisible)
	{
		GreyMask->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		GreyMask->SetVisibility(ESlateVisibility::Collapsed);
	}
}

