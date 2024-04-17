// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/MainMenu.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Button.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (ResetButton)
	{
		ResetButton->OnClicked.AddDynamic(this, &UMainMenu::ResetGameProgress);
	}

	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UMainMenu::ExitGame);
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

