// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/MainMenu.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Player/AnimalPlayerController.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerController = Cast<AAnimalPlayerController>(GetWorld()->GetFirstPlayerController());
	checkf(PlayerController, TEXT("MainMenu could not get reference to the PlayerController"));

	if (ResetButton)
	{
		ResetButton->OnClicked.AddDynamic(this, &UMainMenu::ResetGameProgress);
	}

	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UMainMenu::ExitGame);
	}

	if (MouseSensBox)
	{
		MouseSensBox->OnTextCommitted.AddDynamic(this, &UMainMenu::ChangeMouseSens);
	}
}


void UMainMenu::ResetGameProgress()
{
	// REPLACE WITH FUNCTIONALITY TO RESET GAME PROGRESS
	UE_LOG(LogTemp, Warning, TEXT("Clicked on Reset Button"));
}

void UMainMenu::ExitGame()
{
	// ADD AN "ARE YOU SURE?" QUERY BEFORE EXITING
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}

void UMainMenu::ChangeMouseSens(const FText& NewText, ETextCommit::Type TextType)
{
	if (MouseSensBox->GetText().ToString().IsNumeric())
	{
		PlayerController->MouseSens = FCString::Atof(*(MouseSensBox->GetText().ToString()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Inputted text wasn't numeric"));
	}
	
}

