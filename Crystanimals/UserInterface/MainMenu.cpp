// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/MainMenu.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Core/TreasureGameInstance.h"
#include "UserInterface/AnimalHUD.h"
#include "Kismet/GameplayStatics.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	GameInstance = GetGameInstance<UTreasureGameInstance>();
	checkf(GameInstance, TEXT("MainMenu unable to get reference to GameInstance"));

	HUD = GetWorld()->GetFirstPlayerController()->GetHUD<AAnimalHUD>();
	checkf(HUD, TEXT("MainMenu unable to get reference to HUD"));

	if (HowToPlayButton)
	{
		HowToPlayButton->OnClicked.AddDynamic(this, &UMainMenu::OpenHowToPlayPage);
	}

	if (CreditsButton)
	{
		CreditsButton->OnClicked.AddDynamic(this, &UMainMenu::OpenCreditsPage);
	}

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


void UMainMenu::OpenHowToPlayPage()
{
	UGameplayStatics::PlaySound2D(GetWorld(), ButtonClickSound);
	HUD->DisplayHowToPlayPage();
}

void UMainMenu::OpenCreditsPage()
{
	UGameplayStatics::PlaySound2D(GetWorld(), ButtonClickSound);
	HUD->DisplayCreditsPage();
}

void UMainMenu::ResetGameProgress()
{
	UGameplayStatics::PlaySound2D(GetWorld(), ButtonClickSound);
	HUD->DisplayConfirmationWidget("reset the whole game");
}

void UMainMenu::ExitGame()
{
	UGameplayStatics::PlaySound2D(GetWorld(), ButtonClickSound);
	HUD->DisplayConfirmationWidget("exit the game");
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

