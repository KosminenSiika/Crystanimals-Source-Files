// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/AnimalSelectionMenu.h"
#include "Components/Button.h"
#include "Player/AnimalCharacter.h"

void UAnimalSelectionMenu::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerCharacter = Cast<AAnimalCharacter>(GetOwningPlayerPawn());
	checkf(PlayerCharacter, TEXT("AnimalSelectionMenu could not get a reference to the PlayerCharacter"));

	if (DogButton)
	{
		DogButton->OnClicked.AddDynamic(this, &UAnimalSelectionMenu::SwitchToDog);
	}

	if (CatButton)
	{
		CatButton->OnClicked.AddDynamic(this, &UAnimalSelectionMenu::SwitchToCat);
	}

	if (OtterButton)
	{
		OtterButton->OnClicked.AddDynamic(this, &UAnimalSelectionMenu::SwitchToOtter);
	}

	if (FlyingSquirrelButton)
	{
		FlyingSquirrelButton->OnClicked.AddDynamic(this, &UAnimalSelectionMenu::SwitchToFlyingSquirrel);
	}

	if (JerboaButton)
	{
		JerboaButton->OnClicked.AddDynamic(this, &UAnimalSelectionMenu::SwitchToJerboa);
	}

	if (BirdButton)
	{
		BirdButton->OnClicked.AddDynamic(this, &UAnimalSelectionMenu::SwitchToBird);
	}

}

void UAnimalSelectionMenu::SwitchToDog()
{
	PlayerCharacter->SwitchAnimal(EAnimal::Dog);
}

void UAnimalSelectionMenu::SwitchToCat()
{
	PlayerCharacter->SwitchAnimal(EAnimal::Cat);
}

void UAnimalSelectionMenu::SwitchToOtter()
{
	PlayerCharacter->SwitchAnimal(EAnimal::Otter);
}

void UAnimalSelectionMenu::SwitchToFlyingSquirrel()
{
	PlayerCharacter->SwitchAnimal(EAnimal::FlyingSquirrel);
}

void UAnimalSelectionMenu::SwitchToJerboa()
{
	PlayerCharacter->SwitchAnimal(EAnimal::Jerboa);
}

void UAnimalSelectionMenu::SwitchToBird()
{
	PlayerCharacter->SwitchAnimal(EAnimal::Bird);
}


