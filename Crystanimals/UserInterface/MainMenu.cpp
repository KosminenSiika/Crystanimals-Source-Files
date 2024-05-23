// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/MainMenu.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Core/TreasureGameInstance.h"
#include "UserInterface/AnimalHUD.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	GameInstance = GetGameInstance<UTreasureGameInstance>();
	checkf(GameInstance, TEXT("MainMenu unable to get reference to GameInstance"));

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
		MouseSensBox->SetText(FText::FromString(FString::SanitizeFloat(GameInstance->MouseSens)));
		MouseSensBox->OnTextCommitted.AddDynamic(this, &UMainMenu::ChangeMouseSens);
	}
}


void UMainMenu::ResetGameProgress()
{
	GameInstance->GetFirstLocalPlayerController()->GetHUD<AAnimalHUD>()->DisplayConfirmationWidget("reset the whole game");
}

void UMainMenu::ExitGame()
{
	GameInstance->GetFirstLocalPlayerController()->GetHUD<AAnimalHUD>()->DisplayConfirmationWidget("exit the game");
}

void UMainMenu::ChangeMouseSens(const FText& NewText, ETextCommit::Type TextType)
{
	if (MouseSensBox->GetText().ToString().IsNumeric())
	{
		GameInstance->MouseSens = FCString::Atof(*(MouseSensBox->GetText().ToString()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Inputted text wasn't numeric"));
	}
	
}

